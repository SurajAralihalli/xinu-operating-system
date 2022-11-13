/* vmhfreemem.c */

#include <xinu.h>

/*------------------------------------------------------------------------
 * vmhfreemem  -  vmhfreemem() is a counterpart of freemem() with corresponding arguments for private heap in virtual memory, 
                  albeit with the second argument in unit of pages (not bytes)
 *------------------------------------------------------------------------
 */


syscall vmhfreemem(char *blockaddr, uint16 msize)
{
	intmask	mask;			/* Saved interrupt mask		*/
	struct	vmemblk	*next, *prev, *block;
    v32addr_t* addr;
	uint32	top;

	mask = disable();
	if ((nbytes == 0) || ((uint32) blkaddr < (uint32) minheap)
			  || ((uint32) blkaddr > (uint32) maxheap)) {
		restore(mask);
		return SYSERR;
	}

	addr = (v32addr_t *)blockaddr;

	prev = &memlist;			/* Walk along free list	*/
	next = memlist.mnext;
	while ((next != NULL) && (next < block)) {
		prev = next;
		next = next->mnext;
	}

	if (prev == &memlist) {		/* Compute top of previous block*/
		top = (uint32) NULL;
	} else {
		top = (uint32) prev + prev->mlength;
	}

	/* Ensure new block does not overlap previous or next blocks	*/

	if (((prev != &memlist) && (uint32) block < top)
	    || ((next != NULL)	&& (uint32) block+nbytes>(uint32)next)) {
		restore(mask);
		return SYSERR;
	}

	memlist.mlength += nbytes;

	/* Either coalesce with previous block or add to free list */

	if (top == (uint32) block) { 	/* Coalesce with previous block	*/
		prev->mlength += nbytes;
		block = prev;
	} else {			/* Link into list as new node	*/
		block->mnext = next;
		block->mlength = nbytes;
		prev->mnext = block;
	}

	/* Coalesce with next block if adjacent */

	if (((uint32) block + block->mlength) == (uint32) next) {
		block->mlength += next->mlength;
		block->mnext = next->mnext;
	}
	restore(mask);
	return OK;
}