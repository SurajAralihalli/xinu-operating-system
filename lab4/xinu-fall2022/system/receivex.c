/* receivex.c - receivex */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  receivex  -  Wait for a message and return the message to the caller
 *------------------------------------------------------------------------
 */

syscall receivex(pid32 *pidptr, char *buf, uint16 len)
{
    struct	procent *receiverptr = &proctab[currpid];

    // wait on semaphore
    wait(receiverptr->pripc);

    // no message in receive buffer
	if (receiverptr->prrecvlen==0) {
		receiverptr->prstate = PR_RECV;

        // free the semaphore
        signal(receiverptr->pripc);
		resched();		/* Block until message arrives	*/
        // wait on semaphore
        wait(receiverptr->pripc);
	}

    // if message in receive buffer
    // consume prrecvbuf and copy to user buffer
    copyBuffer(buf, receiverptr->prrecvbuf, len);
    if(pidptr!=NULL)
    {
        // set the pidptr to sender's pid as discussed with prof
        *pidptr = receiverptr->prsenderpid;
    }
    // reset variables
    receiverptr->prsenderpid = 0;
    receiverptr->prrecvlen = 0;

    // some sender is blocked
    if(receiverptr->prblockedsender!=0)
    {
        pid32 senderPid = receiverptr->prblockedsender;
        struct procent *senderptr = &proctab[senderPid];

        int countBytes = copyBuffer(receiverptr->prrecvbuf, senderptr->prsndbuf, senderptr->prsendlen);
        // set the len of receiver buffer
        receiverptr->prrecvlen = countBytes;
        // set the senderpid
        receiverptr->prsenderpid = senderPid;
        // reset variables
        receiverptr->prblockedsender=0;
        senderptr->prblockonreceiver=0;
        senderptr->prsendlen = 0;
        // ready the sender
        ready(senderPid);
    }
    
	// free the semaphore
    signal(receiverptr->pripc);
	return OK;
}
