/* insertdynq.c - insertdynq */

#include <xinu.h>

short insertdynq(pri16 priority, pid32 pid)
{
    intmask	mask;			/* Saved interrupt mask		*/
	kprintf("\n######## insertdynq(), prname: %s, pid: %d, prprio: %d \n", proctab[pid].prname, pid, priority);

	mask = disable();
	if (isbadpid(pid) || priority<0 || priority>9 || pid==0) {
		restore(mask);
		return SYSERR;
	}

	// add pid at new tail
    dynqueue[priority].fifoqueue[dynqueue[priority].tail] = pid;
    // increment tail
    dynqueue[priority].tail = (dynqueue[priority].tail+1)%NPROC;
    // update count
	dynqueue[priority].count++;
	restore(mask);
	return dynqueue[priority].count;
}