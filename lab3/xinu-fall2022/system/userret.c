/* userret.c - userret */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  userret  -  Called when a process returns from the top-level function
 *------------------------------------------------------------------------
 */
void	userret(void)
{
	// kprintf("\nkilling process: %d, prname: %s\n", getpid(), proctab[getpid()].prname);
	kill(getpid());			/* Force process to exit */
}
