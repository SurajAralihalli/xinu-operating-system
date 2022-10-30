/* send.c - send */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  send  -  Pass a message to a process and start recipient if waiting
 *------------------------------------------------------------------------
 */

syscall sendx(pid32 pid, char *buf, uint16 len)
{
    intmask mask;			/* Saved interrupt mask		*/

	mask = disable();
	if (isbadpid(pid)) {
		restore(mask);
		return SYSERR;
	}

    // initialize
    struct procent *receiverptr = &proctab[pid];

    // buffer is free
    if(receiverptr->prrecvlen==0)
    {
        // copy into receiver buffer
        int countBytes = copyBuffer(receiverptr->prrecvbuf, buf, len);
        if(countBytes == -1)
        {
            restore(mask);
            return SYSERR;
        }
        else
        {
            // set the len of receiver buffer
            receiverptr->prrecvlen = countBytes;
        }
        // set sender pid
        receiverptr->prsenderpid = currpid;

        if (receiverptr->prstate == PR_RECV) 
        {
		    ready(pid);
        } 
        else if (receiverptr->prstate == PR_RECTIM) {
            unsleep(pid);
            ready(pid);
        }
    }
    // buffer is not free && no sender is blocked
    else if(receiverptr->prblockedsender==0)
    {
        // update prblockedsender in receiver
        receiverptr->prblockedsender = currpid;

        // initialize
        struct procent *senderptr = &proctab[currpid];
        // copy to sender buffer
        int countBytes = copyBuffer(senderptr->prsndbuf, buf, len);
        if(countBytes == 0)
        {
            restore(mask);
            return SYSERR;
        }
        
        // block the sender
        senderptr->prblockonreceiver = pid;
        senderptr->prstate = PR_SENDBLOCK;
        // call resched
        resched();

    }
    // buffer is not free && some send is blocked
    else
    {
        restore(mask);
        return SYSERR;
    }

    restore(mask);
    return OK;
}