/* cpubound.c - cpubound */

#include <xinu.h>

void cpubound(void)
{
    while(1)
    {
        if(vfineclkcounter >= STOPTIME)
        {
            break;
        }
    }
    
    struct	procent	*prptr = &proctab[currpid];

    intmask	mask;
    mask = disable();

    #ifdef XINUTEST
    kprintf("\ncpubound, pid:%d, cpu-usage:%d, user-cpu-usage:%d, average-response-time:%d, max-response-time:%d, number-context-switches:%d, preemption1-count:%d, preemption2-count:%d\n", currpid, totcpu(currpid), prptr->prusercpu, resptime(currpid), prptr->prmaxresponse, prptr->prcurrcount, prptr->prpreemptcount1, prptr->prpreemptcount2);
    #endif

    restore(mask);
}