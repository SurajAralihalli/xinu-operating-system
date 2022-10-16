/* insertdynq.c - insertdynq */

#include <xinu.h>

void preventstarvation(void)
{
    intmask	mask;			/* Saved interrupt mask		*/
	mask = disable();

    pri16 priority = 8;
    while(priority>=0)
    {
        // there is atleast one process
        if(dynqueue[priority].count>0)
        {
            pid32 pid = dynqueue[priority].head;
            if(pid==0) continue;
            struct	procent	*prptr = &proctab[pid];
            uint32 timeElapsedms = (uint32)(getticks() - prptr->prreadystart) / (double)(389 * 1000);
            if(timeElapsedms > STARVATIONTHRESHOLD)
            {
                // compute new priority
                pri16 newPri = priority + PRIOBOOST;
                prptr->prprio = MIN(9, newPri);

                // fresh quantum on changing priorities
		        prptr->quantumLeft = dyndisp[prptr->prprio].quantum;

                // remove from old queue
                dynqueue[priority].head = (dynqueue[priority].head+1)%NPROC;
                dynqueue[priority].count--;

                // insert in new queue - fail to add to queue
                if( insertdynq(prptr->prprio, pid) == -1 )
                {
                    continue;
                }

                kprintf("\nstarvation prevented: pname: %s, pid:%d, oldPri:%d, newPri:%d\n",prptr->prname, pid, priority, prptr->prprio);
            }
        }
        priority--;
    }

	restore(mask);
}