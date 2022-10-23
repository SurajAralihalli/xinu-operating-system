/* insertdynq.c - insertdynq */

#include <xinu.h>

short insertdynq(pri16 priority, pid32 pid)
{
	// kprintf("\n######## insertdynq(), prname: %s, pid: %d, prprio: %d \n", proctab[pid].prname, pid, priority);
	if (isbadpid(pid) || priority<0 || priority>10 || pid==0) {
		return SYSERR;
	}

	// add pid at new tail
    dynqueue[priority].fifoqueue[dynqueue[priority].tail] = pid;
    // increment tail
    dynqueue[priority].tail = (dynqueue[priority].tail+1)%NPROC;
    // update count
	dynqueue[priority].count++;
	return dynqueue[priority].count;
}