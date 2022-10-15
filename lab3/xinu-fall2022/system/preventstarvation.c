/* insertdynq.c - insertdynq */

#include <xinu.h>

void preventstarvation(void)
{
    intmask	mask;			/* Saved interrupt mask		*/
	mask = disable();

    int priority = 8;
    while(priority>=0)
    {
        // there is atleast one process
        while(dynqueue[priority].count!=0)
        {
            pid32 pid = dynqueue[priority].head;
            struct	procent	*prptr = &proctab[pid];
            uint32 timeElapsedms = (uint32)(getticks() - prptr->prreadystart) / (double)(389 * 1000);
            if(timeElapsedms > STARVATIONTHRESHOLD)
            {
                // compute new priority
                pri16 newPri = prptr->prprio + PRIOBOOST;
                prptr->prprio = MIN(9, newPri);

                // fresh quantum on changing priorities
		        prptr->quantumLeft = dyndisp[prptr->prprio].quantum;

                // remove from old queue
                dynqueue[priority].head = (dynqueue[priority].head+1)%NPROC;
                dynqueue[priority].count--;

                // insert in new queue
                insertdynq(prptr->prprio, pid);

                kprintf("\nstarvation prevented: pid:%d, oldPri:%d, newPri:%d\n",pid, priority, newPri);
            }
        }
        priority--;
    }

	restore(mask);
}