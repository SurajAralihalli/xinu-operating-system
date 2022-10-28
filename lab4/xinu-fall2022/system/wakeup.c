/* wakeup.c - wakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  wakeup  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */
void	wakeup(void)
{
	/* Awaken all processes that have no more time to sleep */

	resched_cntl(DEFER_START);
	while (nonempty(sleepq) && (firstkey(sleepq) <= 0)) {
		pid32 pid = dequeue(sleepq);
		
		// associated with sleep
		if(pid < NPROC)
		{
			ready(dequeue(sleepq));
		}
		// associated with alarmx()
		else
		{
			if(pid >= 2*NPROC)
			{
				pid = pid - 2*NPROC;
			}
			else if(pid >= NPROC)
			{
				pid = pid - NPROC;
			}
			
			struct procent *prptr = &proctab[pid];
			// decrement alarms && set prmakedetour to 1
			prptr->prnumalarms--;
			prptr->prmakedetour=1;
			kprintf("\n wake up and set prmakedetour for pid:%d\n", currpid);
		}
		
	}

	resched_cntl(DEFER_STOP);
	return;
}
