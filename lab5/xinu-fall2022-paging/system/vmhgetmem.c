/* vmhgetmem.c */

#include <xinu.h>

/*------------------------------------------------------------------------
 * vmhgetmem  -  vmhgetmem() allocates the requested amount of memory albeit in page granularity (not bytes)
 *------------------------------------------------------------------------
 */
char* vmhgetmem(uint16 msize)
{
    intmask	mask;			/* Saved interrupt mask		*/
	struct	vmemblk *prev, *curr, *leftover;
    v32addr_t* addr;

	mask = disable();
	if (msize == 0) {
		restore(mask);
		return (char *)SYSERR;
	}

	prev = &vmemlist;
	curr = vmemlist.mnext;
	while (curr != NULL) {			/* Search free list	*/

		if (curr->npages == msize) {	/* Block is exact match	*/
            addr = curr->addr;
            /* Free linked list node */
            free_linkedlist_node(curr);
			prev->mnext = curr->mnext;
			vmemlist.npages -= msize;
			restore(mask);
			return (char *)(addr);

		} else if (curr->npages > msize) { /* Split big block	*/
            addr = curr->addr;
            curr->addr = (uint32)curr->addr + (msize * NBPG);
			curr->npages = curr->npages - msize;
			vmemlist.npages -= msize;
			restore(mask);
			return (char *)(addr);
		} else {			/* Move to next block	*/
			prev = curr;
			curr = curr->mnext;
		}
	}
	restore(mask);
	return (char *)SYSERR;

}