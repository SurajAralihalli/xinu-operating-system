/* alarmx.c - wakeup */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  alarmx  -  Call to register an alarm
 *------------------------------------------------------------------------
 */

syscall alarmx(uint32 timeval, void (* ftn) (void))
{
    intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();
	if (isbadpid(currpid) || proctab[currpid].prnumalarms >=2 || timeval<=0) {
		restore(mask);
		return SYSERR;
	}

    struct procent *prptr = &proctab[currpid];
    pid32 pidalarm;

    // no previous alarms
    if(prptr->prnumalarms==0)
    {
        // initialize
        prptr->lastpidalarmtriggered = -1;
        pidalarm = NPROC + currpid;
    }
    // one previous alarm
    else
    {
        if(prptr->lastpidalarmtriggered == NPROC + currpid)
        {
            pidalarm =  NPROC + currpid;
        }
        else
        {
            pidalarm =  2*NPROC + currpid;
        }
        
    }

    //  add to sleepqueue
    if (insertd(pidalarm, sleepq, timeval) == SYSERR) {
        // kprintf("\n Insert failed \n");
		restore(mask);
		return SYSERR;
	}

    // register the callback function
    prptr->prcbftn = ftn;

    // icrement prnumalarms
    prptr->prnumalarms++;
    

	restore(mask);
	return 0;
}