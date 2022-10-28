/* alarmx.c - wakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  alarmx  -  Call to register an alarm
 *------------------------------------------------------------------------
 */

syscall alarmx(uint32 timeval, void (* ftn) (void))
{
    intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();
	if (isbadpid(currpid) || proctab[currpid].prnumalarms >=2 || timeval<=0) {
		restore(mask);
		return SYSERR;
	}

    struct procent *prptr = &proctab[currpid];
    pid32 pidalarm;

    // no previous alarms
    if(proctab[currpid].prnumalarms==0)
    {
        pidalarm = NPROC + currpid;
    }
    // one previous alarm
    else
    {
        pidalarm =  2*NPROC + currpid;
    }

    // register the callback function
    prptr->prcbftn = ftn;

    //  add to sleepqueue
    if (insertd(pidalarm, sleepq, timeval) == SYSERR) {
        kprintf("\n Insert failed \n");
		restore(mask);
		return SYSERR;
	}

    // icrement prnumalarms
    prptr->prnumalarms++;

	restore(mask);
	return 0;
}