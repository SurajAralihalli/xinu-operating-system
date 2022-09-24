/* userret.c - userret */

#include <xinu.h>
int userCpuTime[NPROC];

/*------------------------------------------------------------------------
 *  userret  -  Called when a process returns from the top-level function
 *------------------------------------------------------------------------
 */
void	userret(void)
{
	// pid32 pid= getpid();
	// struct	procent *prptr = &proctab[pid];
	// kprintf("pid:%d pname:%s usercpu:%d vclk:%d iter:%d\n",pid, prptr->prname, usercpu(pid), vfineclkcounter, userCpuTime[pid]);
	kill(getpid());			/* Force process to exit */
}
