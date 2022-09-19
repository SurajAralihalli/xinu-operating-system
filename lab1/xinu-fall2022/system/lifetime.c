/* lifetime.c - lifetime */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  lifetime  -  returns the lifetime of a process
 *------------------------------------------------------------------------
 */
syscall	lifetime(pid32 pid)
{

    intmask	mask;			/* Saved interrupt mask		*/
	int32	lived10ms;			/* lived time in unit of 10ms		*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}
	struct	procent	*prptr = &proctab[pid];
	lived10ms = fineclkcounter - prptr->prbirthday;

	restore(mask);
	return lived10ms;
}