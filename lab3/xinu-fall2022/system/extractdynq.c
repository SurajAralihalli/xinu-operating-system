/* extractdynq.c - extractdynq */

#include <xinu.h>


pid32 extractdynq(void)
{
    pid32 pid = SYSERR;
    int priority = 10;
    while(priority>=0)
    {
        // atleast one pid is in the queue
        if(dynqueue[priority].count>0)
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
	return pid;
}


void printHeads()
{
    int priority = 9;
    kprintf("\n@@@ printHeads @@@\n");
    while(priority>=0)
    {
        // atleast one pid is in the queue
        if(dynqueue[priority].count>0)
        {
            // fetch pid at head
            pid32 pid = dynqueue[priority].fifoqueue[dynqueue[priority].head];
            kprintf("(priority: %d, pid: %d, prname:%s, count: %d)  ", priority, pid, proctab[pid].prname, dynqueue[priority].count);
        }
        priority--;
    }
    kprintf("\n@@@ end @@@\n");
}