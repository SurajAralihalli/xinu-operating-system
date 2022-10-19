/* initialize.c - nulluser, sysinit */

/* Handle system initialization and become the null process */

#include <xinu.h>
#include <string.h>

extern	void	start(void);	/* Start of Xinu code			*/
extern	void	*_end;		/* End of Xinu code			*/

/* Function prototypes */

extern	void main(void);	/* Main is the first process created	*/
static	void sysinit(); 	/* Internal system initialization	*/
extern	void meminit(void);	/* Initializes the free memory list	*/
local	process startup(void);	/* Process to finish startup tasks	*/

/* Declarations of major kernel variables */

struct	procent	proctab[NPROC];	/* Process table			*/
struct	sentry	semtab[NSEM];	/* Semaphore table			*/
struct	memblk	memlist;	/* List of free memory blocks		*/

/* Active system status */

int	prcount;		/* Total number of live processes	*/
pid32	currpid;		/* ID of currently executing process	*/
uint64  currstart;
uint64  currstop;

int preemptionType;
struct tsx_disp dyndisp[11];
struct mfeedbqx dynqueue[11];

/* Control sequence to reset the console colors and cusor positiion	*/

#define	CONSOLE_RESET	" \033[0m\033[2J\033[;H"

/*------------------------------------------------------------------------
 * nulluser - initialize the system and become the null process
 *
 * Note: execution begins here after the C run-time environment has been
 * established.  Interrupts are initially DISABLED, and must eventually
 * be enabled explicitly.  The code turns itself into the null process
 * after initialization.  Because it must always remain ready to execute,
 * the null process cannot execute code that might cause it to be
 * suspended, wait for a semaphore, put to sleep, or exit.  In
 * particular, the code must not perform I/O except for polled versions
 * such as kprintf.
 *------------------------------------------------------------------------
 */

void	nulluser()
{	
	struct	memblk	*memptr;	/* Ptr to memory block		*/
	uint32	free_mem;		/* Total amount of free memory	*/
	
	/* Initialize the system */

	sysinit();

	/* Output Xinu memory layout */
	free_mem = 0;
	for (memptr = memlist.mnext; memptr != NULL;
						memptr = memptr->mnext) {
		free_mem += memptr->mlength;
	}
	kprintf("%10d bytes of free memory.  Free list:\n", free_mem);
	for (memptr=memlist.mnext; memptr!=NULL;memptr = memptr->mnext) {
	    kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)memptr, ((uint32)memptr) + memptr->mlength - 1);
	}

	kprintf("%10d bytes of Xinu code.\n",
		(uint32)&etext - (uint32)&text);
	kprintf("           [0x%08X to 0x%08X]\n",
		(uint32)&text, (uint32)&etext - 1);
	kprintf("%10d bytes of data.\n",
		(uint32)&ebss - (uint32)&data);
	kprintf("           [0x%08X to 0x%08X]\n\n",
		(uint32)&data, (uint32)&ebss - 1);

	/* Enable interrupts */

	enable();

        /* Limit network relevant calls for CS503 courses   */
	///* Initialize the network stack and start processes */

	//net_init();

	// set preemptionType 
	preemptionType =0;

	// Create myHello process
	resume(create((void *)myhello, INITSTK, 9,
					"myhello process", 0, NULL));

	/* Create a process to finish startup and start main */

	resume(create((void *)startup, INITSTK, 8,
					"Startup process", 0, NULL));

	/* Become the Null process (i.e., guarantee that the CPU has	*/
	/*  something to run when no other process is ready to execute)	*/
	
	// setup currstop
	currstop = (uint64)0;
	// setup currstart
	currstart = getticks();

	while (TRUE) {
		/* Do nothing */
	}

}


/*------------------------------------------------------------------------
 *
 * startup  -  Finish startup takss that cannot be run from the Null
 *		  process and then create and resumethe main process
 *
 *------------------------------------------------------------------------
 */
local process	startup(void)
{
        /* Limit network relevant calls for CS503 courses   */
	//uint32	ipaddr;			/* Computer's IP address	*/
	//char	str[128];		/* String used to format output	*/


	///* Use DHCP to obtain an IP address and format it */

	//ipaddr = getlocalip();
	//if ((int32)ipaddr == SYSERR) {
	//	kprintf("Cannot obtain an IP address\n");
	//} else {
	//	/* Print the IP in dotted decimal and hex */
	//	ipaddr = NetData.ipucast;
	//	sprintf(str, "%d.%d.%d.%d",
	//		(ipaddr>>24)&0xff, (ipaddr>>16)&0xff,
	//		(ipaddr>>8)&0xff,        ipaddr&0xff);
	//
	//	kprintf("Obtained IP address  %s   (0x%08x)\n", str,
	//							ipaddr);
	//}

	/* Create a process to execute function main() */

	resume(create((void *)main, INITSTK, 10,
					"Main process", 0, NULL));

	/* Startup process exits at this point */

	return OK;
}


/*------------------------------------------------------------------------
 *
 * sysinit  -  Initialize all Xinu data structures and devices
 *
 *------------------------------------------------------------------------
 */
static	void	sysinit()
{
	int32	i;
	struct	procent	*prptr;		/* Ptr to process table entry	*/
	struct	sentry	*semptr;	/* Ptr to semaphore table entry	*/

	/* Platform Specific Initialization */

	platinit();

	/* Reset the console */

	kprintf(CONSOLE_RESET);
	kprintf("\n%s\n\n", VERSION);

	/* Initialize the interrupt vectors */

	initevec();
	
	/* Initialize free memory list */
	
	meminit();

	/* Initialize system variables */

	/* Count the Null process as the first process in the system */

	prcount = 1;

	/* Scheduling is not currently blocked */

	Defer.ndefers = 0;

	/* Initialize process table entries free */

	for (i = 0; i < NPROC; i++) {
		prptr = &proctab[i];
		prptr->prstate = PR_FREE;
		prptr->prname[0] = NULLCH;
		prptr->prstkbase = NULL;
		prptr->prprio = 0;
	}

	/* Initialize the Null process entry */	

	prptr = &proctab[NULLPROC];
	prptr->prstate = PR_CURR;
	prptr->prprio = -1;
	strncpy(prptr->prname, "prnull", 7);
	prptr->prstkbase = getstk(NULLSTK);
	prptr->prstklen = NULLSTK;
	prptr->prstkptr = 0;
	prptr->prusercpu = 0; /* initialized to 0 upon process creation */
	prptr->prtotalcpu = 0; /* initialized to 0 upon process creation */
	prptr->prcurrcount = 1; 
	prptr->prreadystart = getticks();
	prptr->prtotalresponse = 0; /* initialized to 0 upon process creation */
	prptr->prmaxresponse = 0;
	prptr->prpreemptcount1 = 0; /* initialized to 0 upon process creation */
	prptr->prpreemptcount2 = 0; /* initialized to 0 upon process creation */
	prptr->quantumLeft  = 0xFFFFFFFF;
	currpid = NULLPROC;
	
	/* Initialize semaphores */

	for (i = 0; i < NSEM; i++) {
		semptr = &semtab[i];
		semptr->sstate = S_FREE;
		semptr->scount = 0;
		semptr->squeue = newqueue();
	}

	/* Initialize buffer pools */

	bufinit();

	/* Create a ready list for processes */

	// readylist = newqueue();
	/* Initialize the  dyndisp table and Dynqueue */
	initializeDyndisp();
	initializeDynqueue();


	/* Initialize the real time clock */

	clkinit();

	for (i = 0; i < NDEVS; i++) {
		init(i);
	}
	return;
}

int32	stop(char *s)
{
	kprintf("%s\n", s);
	kprintf("looping... press reset\n");
	while(1)
		/* Empty */;
}

int32	delay(int n)
{
	DELAY(n);
	return OK;
}

void initializeDyndisp()
{
	int i=0;
	while(i!=10)
	{
		dyndisp[i].tqexp = MAX(0, i-1);
		dyndisp[i].slpret = MIN(9, i+1);
		dyndisp[i].quantum = 100 - 10*i;
		i++;
	}

	// i = 10
	dyndisp[10].tqexp = 10;
	dyndisp[10].slpret = 10;
	dyndisp[10].quantum = 25;


}

void initializeDynqueue()
{
	int i=0;
	while(i!=11)
	{
		dynqueue[i].count = 0;
		dynqueue[i].head = 0;
		dynqueue[i].tail = 0;
		i++;
	}
}
