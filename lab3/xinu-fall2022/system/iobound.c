/* iobound.c - iobound */

#include <xinu.h>

void iobound(void)
{
    while(1)
    {
        uint32 start = vfineclkcounter;
        int i=0;

        // callibrated 2ms 
        for(i=0; i<68043 ; i++) {
        }

        sleepms(80);

        if(vfineclkcounter >= STOPTIME)
        {
            break;
        }
    }

    struct	procent	*prptr = &proctab[currpid];

    intmask	mask;
    mask = disable();

    #ifdef XINUTEST
    // kprintf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    kprintf("\niobound, pid:%d, cpu-usage:%d, user-cpu-usage:%d, average-response-time:%d, max-response-time:%d, number-context-switches:%d, preemption1-count:%d, preemption2-count:%d\n", currpid, totcpu(currpid), prptr->prusercpu, resptime(currpid), prptr->prmaxresponse, prptr->prcurrcount, prptr->prpreemptcount1, prptr->prpreemptcount2);
    // kprintf("\n$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$\n");
    #endif

    restore(mask);
}