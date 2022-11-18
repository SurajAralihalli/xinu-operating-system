/* kill.c - kill */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  kill  -  Kill a process and remove it from the system
 *------------------------------------------------------------------------
 */
syscall	kill(
	  pid32		pid		/* ID of process to kill	*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	procent *prptr;		/* Ptr to process' table entry	*/
	int32	i;			/* Index into descriptors	*/

	mask = disable();
	if (isbadpid(pid) || (pid == NULLPROC)
	    || ((prptr = &proctab[pid])->prstate) == PR_FREE) {
		restore(mask);
		return SYSERR;
	}

	if (--prcount <= 1) {		/* Last user process completes	*/
		xdone();
	}

	send(prptr->prparent, pid);
	for (i=0; i<3; i++) {
		close(prptr->prdesc[i]);
	}
	
	freestk(prptr->prstkbase, prptr->prstklen);

	/* Deallocate frames corresponding to current process in E1 */
	purge_frames_fHolderListE1(currpid);

	/* Deallocate frames corresponding to current process in D */
	purge_frames_fHolderListD(currpid);

	/* Purge memory associated vmemlist */
	purge_vmemlist();

	kprintf("---in kill----\n");
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1) {
            kprintf("Frame %d not free!\n", i);
        }
    }

    /* Only frames corresponding to page directory and page tables should be used */
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1) {
            kprintf("Frame %d not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
        }
    }

	switch (prptr->prstate) {
	case PR_CURR:
		prptr->prstate = PR_FREE;	/* Suicide */
		resched();

	case PR_SLEEP:
	case PR_RECTIM:
		unsleep(pid);
		prptr->prstate = PR_FREE;
		break;

	case PR_WAIT:
		semtab[prptr->prsem].scount++;
		/* Fall through */

	case PR_READY:
		getitem(pid);		/* Remove from queue */
		/* Fall through */

	default:
		prptr->prstate = PR_FREE;
	}

	restore(mask);
	return OK;
}
