/* resptime.c - resptime */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  resptime - return avg resptime time in ms
 *------------------------------------------------------------------------
 */
syscall	resptime(
	  pid32		pid		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	uint32	timems;			/* Priority to return		*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	
    // fetch pid's prusercpu
    struct	procent	*prptr;
	prptr = &proctab[pid];
	timems = prptr->prtotalresponse / (double)(389 * 1000);
    timems = timems / (double)(prptr->prcurrcount);

	restore(mask);
	return (syscall)timems;
}