/* userret.c - userret */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  userret  -  Called when a process returns from the top-level function
 *------------------------------------------------------------------------
 */
void	userret(void)
{
	pid32 pid = getpid();
	// struct	procent	*prptr = &proctab[pid];
	// prptr->prterminationtime = fineclkcounter;
	// kprintf("\nuserret: kill %d %s\n",getpid(), prptr->prname);
	// kprintf("\n pID: %d, pName: %s, prcpuhungry: %d\n",getpid(), prptr->prname, prptr->prcpuhungry);
	kill(pid);			/* Force process to exit */
}
