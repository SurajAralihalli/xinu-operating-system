/* totcpu.c - totcpu */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  totcpu - return totalcpu time in ms
 *------------------------------------------------------------------------
 */
syscall	totcpu(
	  pid32		pid		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	uint32	timeMilliSec;			/* Priority to return		*/
	uint32	timeMicroSec;

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	
    // fetch pid's prusercpu
    struct	procent	*prptr;
	prptr = &proctab[pid];

	timeMicroSec = prptr->prtotalcpu;

	// if the process has not context switched for a long time
	// here currstop was set by previous process
	if(currstop >= currstart)
	{
		kprintf("\ncurrstop:%d > currstart:%d \n",currstop,currstart);
	}
	else
	{
		kprintf("\n[BUG] currstart:%d > currstop:%d \n",currstart,currstop);
	}

	timeMicroSec += (getticks() - currstart) / (double)389;

	timeMilliSec = timeMicroSec / (double)1000;
	restore(mask);
	return (syscall)timeMilliSec;
}