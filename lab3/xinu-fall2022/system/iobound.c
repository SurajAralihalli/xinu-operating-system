/* iobound.c - iobound */

#include <xinu.h>

void iobound(void)
{
    while(1)
    {
        int i=0;
        uint32 start = vfineclkcounter;

        // callibrated 2ms 
        while(i<37608)
        {
            if(vfineclkcounter - start>=2)
            {
                break;
            }
            i++;
        }

        sleepms(80);

        if(vfineclkcounter >= STOPTIME)
        {
            break;
        }
    }

    struct	procent	*prptr = &proctab[currpid];

    kprintf("\niobound, pid:%d, cpu-usage:%d, user-cpu-usage:%d, average-response-time:%d, max-response-time:%d, number-context-switches:%d, preemption1-count:%d, preemption2-count:%d\n", currpid, prptr->prtotalcpu, prptr->prusercpu, resptime(currpid), prptr->prmaxresponse, prptr->prcurrcount, prptr->prpreemptcount1, prptr->prpreemptcount2);
}