/* vmhalloc.c - vmhalloc */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  vmhalloc  -  Return the scheduling priority of a process
 *------------------------------------------------------------------------
 */
syscall	vmhalloc(
	  uint32		hsize		/* Process ID			*/
	)
{
	intmask	mask;			/* Saved interrupt mask		*/
    struct	procent	*prptr = &proctab[currpid];

    if(hsize<0 || hsize>=585727 || prptr->hsize!=-1) // assumption: hsize is fixed and cannot be changed
    {
        restore(mask);
        return SYSERR;
    }
    else
    {
        prptr->hsize = hsize;
        restore(mask);
	    return OK;
    }
}
