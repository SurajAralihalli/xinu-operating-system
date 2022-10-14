/* extractdynq.c - extractdynq */

#include <xinu.h>


pid32 extractdynq(void)
{
    intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();

    pid32 pid = SYSERR;
    int priority = 9;
    while(priority>=0)
    {
        // atleast one pid is in the queue
        if(dynqueue[priority].count>=1)
        {
            // fetch pid at head
            pid = dynqueue[priority].fifoqueue[dynqueue[priority].head];
            // increment head
            dynqueue[priority].head = (dynqueue[priority].head+1)%NPROC;
            // decrement count
            dynqueue[priority].count--;
            break;
        }
        priority--;
    }

	restore(mask);
	return pid;
}