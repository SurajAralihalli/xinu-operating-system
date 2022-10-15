/* clkhandler.c - clkhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * clkhandler - high level clock interrupt handler
 *------------------------------------------------------------------------
 */
void	clkhandler()
{
	static	uint32	count1000 = 1000;	/* Count to 1000 ms	*/

	/* Decrement the ms counter, and see if a second has passed */

	if((--count1000) <= 0) {

		/* One second has passed, so increment seconds count */

		clktime++;

		/* Reset the local ms counter for the next second */

		count1000 = 1000;
	}

	// increment prusercpu of current process
	struct	procent	*prptr;
	prptr = &proctab[currpid];
	prptr->prusercpu++;

	/* Handle sleeping processes if any exist */

	if(!isempty(sleepq)) {

		/* Decrement the delay for the first process on the	*/
		/*   sleep queue, and awaken if the count reaches zero	*/

		if((--queuetab[firstid(sleepq)].qkey) <= 0) {
			// type 2 preemption i.e preempt!=0
			preemptionType = 2;
			// priority does not change - case 2
			wakeup();
			preemptionType = 0;
		}
	}

	/* Decrement the preemption counter, and reschedule when the */
	/*   remaining time reaches zero			     */

	preempt = currpid==0 ? 0xFFFFFFFF : preempt-1;
	
	prptr->quantumLeft = preempt;

	if(preempt <= 0) {

		preemptionType = 1;

		// demote the priority - case 1
		int old =  prptr->prprio;
		prptr->prprio = MAX(0, prptr->prprio-1);
		prptr->quantumLeft = dyndisp[prptr->prprio].quantum;
		kprintf("\ncurrpid:%d, priOld: %d, priNew: %d, quantum:%d\n", currpid, old, proctab[currpid].prprio, proctab[currpid].quantumLeft);
		resched();
		preemptionType = 0;
	}
}
