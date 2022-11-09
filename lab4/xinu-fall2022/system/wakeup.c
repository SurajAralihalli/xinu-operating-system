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
			ready(pid);
		}
		// associated with alarmx()
		else
		{
			pid32 pidalarm = pid;
			
			if(pid >= 2*NPROC)
			{
				pid = pid - 2*NPROC;
			}
			else if(pid >= NPROC)
			{
				pid = pid - NPROC;
			}

			struct procent *prptr = &proctab[pid];
			// update lastpidalarm
    		prptr->lastpidalarmtriggered = pidalarm;
			// decrement alarms && set prmakedetour to 1
			prptr->prnumalarms--;
			prptr->prmakedetour=1;
		}
		
	}

	resched_cntl(DEFER_STOP);
	return;
}
