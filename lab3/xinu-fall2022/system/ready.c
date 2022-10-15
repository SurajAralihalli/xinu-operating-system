/* ready.c - ready */

#include <xinu.h>

qid16	readylist;			/* Index of ready list		*/

/*------------------------------------------------------------------------
 *  ready  -  Make a process eligible for CPU service
 *------------------------------------------------------------------------
 */
status	ready(
	  pid32		pid		/* ID of process to make ready	*/
	)
{
	register struct procent *prptr;

	if (isbadpid(pid)) {
		return SYSERR;
	}

	/* Set process state to indicate ready and add to ready list */

	prptr = &proctab[pid];
	prptr->prstate = PR_READY;

	// using default queue
	// insert(pid, readylist, prptr->prprio);

	// using multilevel feedback queue
	int h = insertdynq(prptr->prprio, pid);
	kprintf("\ninsertdynq(prptr->prprio, pid): %d, prname: %s, pid: %d, prprio: %d \n",h, prptr->prname, pid, prptr->prprio);

	// set prptr->prreadystart when process becomes ready
	prptr->prreadystart = getticks();
	resched();

	return OK;
}
