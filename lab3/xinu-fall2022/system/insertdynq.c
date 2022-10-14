/* insertdynq.c - insertdynq */

#include <xinu.h>

short insertdynq(pri16 priority, pid32 pid)
{
    intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();
	if (isbadpid(pid) || priority<0 || priority>9) {
		restore(mask);
		return SYSERR;
	}

    // increment tail
    dynqueue[priority].tail = (dynqueue[priority].tail+1)%NPROC;
    // add pid at new tail
    dynqueue[priority].fifoqueue[dynqueue[priority].tail] = pid;
    // update count
	dynqueue[priority].count++;

	restore(mask);
	return dynqueue[priority].count;
}