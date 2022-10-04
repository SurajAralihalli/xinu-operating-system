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

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	
    // fetch pid's prusercpu
    struct	procent	*prptr;
	prptr = &proctab[pid];

	// if the process has not context switched for a long time
	// here currstop was set by previous process so currstart>=currstop
	timeMilliSec = prptr->prtotalcpu / (double)1000;

	restore(mask);
	return (syscall)timeMilliSec;
}