/* insertdynq.c - insertdynq */

#include <xinu.h>

void preventstarvation(void)
{
    pri16 priority;

    for(priority = 8; priority>=0; priority--)
    {
        // there is atleast one process
        
        if(dynqueue[priority].count>0)
        {
            pid32 pid = dynqueue[priority].fifoqueue[dynqueue[priority].head];

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
                insertdynq(prptr->prprio, pid);

                // kprintf("\nstarvation prevented: pname: %s, pid:%d, oldPri:%d, newPri:%d, currcount:%d \n",prptr->prname, pid, priority, prptr->prprio, prptr->prcurrcount);
            }
        }
    }
}