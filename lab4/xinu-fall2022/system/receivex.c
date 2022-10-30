/* receivex.c - receivex */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receivex  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */

syscall receivex(pid32 *pidptr, char *buf, uint16 len)
{
    intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *receiverptr;		/* Ptr to process's table entry	*/

	mask = disable();
	receiverptr = &proctab[currpid];

    // no message in receive buffer
	if (receiverptr->prrecvlen==0) {
		receiverptr->prstate = PR_RECV;
		resched();		/* Block until message arrives	*/
	}

    // if message in receive buffer
    // consume prrecvbuf and copy to user buffer
    copyBuffer(buf, receiverptr->prrecvbuf, len);
    // reset variables
    receiverptr->prsenderpid = 0;
    receiverptr->prrecvlen = 0;

    // some sender is blocked
    if(receiverptr->prblockedsender!=0)
    {
        pid32 senderPid = receiverptr->prblockedsender;
        struct procent *senderptr = &proctab[senderPid];

        int countBytes = copyBuffer(receiverptr->prrecvbuf, senderptr->prsndbuf, strlen(senderptr->prsndbuf));
        // set the len of receiver buffer
        receiverptr->prrecvlen = countBytes;
        // set the senderpid
        receiverptr->prsenderpid = senderPid;
        // reset variables
        receiverptr->prblockedsender=0;
        senderptr->prblockonreceiver=0;
        // ready the sender
        ready(senderPid);
    }
	restore(mask);
	return OK;
}
