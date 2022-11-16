/* vmhgetmem.c */

#include <xinu.h>

/*------------------------------------------------------------------------
 * vmhgetmem  -  vmhgetmem() allocates the requested amount of memory albeit in page granularity (not bytes)
 *------------------------------------------------------------------------
 */
char* vmhgetmem(uint16 msize)
{
    intmask	mask;			/* Saved interrupt mask		*/
	struct	vmemblk *prev, *curr;
    v32addr_t addr;

	mask = disable();
	kprintf("entered vmhgetmem()\n");
	if (msize == 0) {
		restore(mask);
		return (char *)SYSERR;
	}

	struct	procent	*prptr =  &proctab[currpid];
	struct vmemblk* vmemlist_ptr = prptr->vmemlist_ptr;
	
	prev = vmemlist_ptr;
	curr = vmemlist_ptr->mnext;
	kprintf("starting search  free list: %x: %x\n", vmemlist_ptr, vmemlist_ptr->mnext);
	while (curr != NULL) {			/* Search free list	*/

		if (curr->npages == msize) {	/* Block is exact match	*/
            addr = curr->start_addr;
			prev->mnext = curr->mnext;

			/* Free linked list node */
			free_vmemblk_node(curr);

			vmemlist_ptr->npages -= msize;
			restore(mask);
			return (char *)(addr);

		} else if (curr->npages > msize) { /* Split big block	*/
			kprintf("curr->npages > msize\n");
            addr = curr->start_addr;
            curr->start_addr = curr->start_addr + (msize * NBPG);
			curr->npages = curr->npages - msize;
			kprintf("updated curr->npages\n");
			vmemlist_ptr->npages -= msize;
			restore(mask);
			return (char *)(addr);
		} else {			/* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	kprintf("exited vmhgetmem()\n");
	restore(mask);
	return (char *)SYSERR;

}