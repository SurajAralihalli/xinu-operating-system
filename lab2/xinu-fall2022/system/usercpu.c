/* usercpu.c - usercpu */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  usercpu - return user cpu time in ms
 *------------------------------------------------------------------------
 */
syscall	usercpu(
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
	timems = prptr->prusercpu;

	restore(mask);
	return (syscall)timems;
}