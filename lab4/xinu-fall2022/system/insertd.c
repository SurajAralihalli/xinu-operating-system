/* insertd.c - insertd */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  insertd  -  Insert a process in delta list using delay as the key
 *------------------------------------------------------------------------
 */
status	insertd(			/* Assumes interrupts disabled	*/
	  pid32		pid,		/* ID of process to insert	*/
	  qid16		q,		/* ID of queue to use		*/
	  int32		key		/* Delay from "now" (in ms.)	*/
	)
{
	int32	next;			/* Runs through the delta list	*/
	int32	prev;			/* Follows next through the list*/

	if (isbadqid(q) || isbadpidalarm(pid)) {
		return SYSERR;
	}

	prev = queuehead(q);
	next = queuetab[queuehead(q)].qnext;
	while ((next != queuetail(q)) && (queuetab[next].qkey <= key)) {
		key -= queuetab[next].qkey;
		prev = next;
		next = queuetab[next].qnext;
	}

	/* Insert new node between prev and next nodes */

	queuetab[pid].qnext = next;
	queuetab[pid].qprev = prev;
	queuetab[pid].qkey = key;
	queuetab[prev].qnext = pid;
	queuetab[next].qprev = pid;
	if (next != queuetail(q)) {
		queuetab[next].qkey -= key;
	}

	// if(q == sleepq)
	// {
	// 	kprintf("\n Inserted in sleep queue, pid:%d \n",pid);
	// }
	

	return OK;
}


int isbadpidalarm(pid32 pidalarm)
{
	if(pidalarm<0 || pidalarm>=3*NPROC)
	{
		return 1;
	}

	pid32 pid;
	if(pidalarm >= 2*NPROC)
	{
		pid = pidalarm - 2*NPROC;
	}
	else if (pidalarm >= NPROC)	
	{
		pid = pidalarm - NPROC;
	}
	else
	{
		pid = pidalarm;
	}

	if(proctab[pid].prstate == PR_FREE)
	{
		return 1;
	}

	// return false
	return 0;
}
