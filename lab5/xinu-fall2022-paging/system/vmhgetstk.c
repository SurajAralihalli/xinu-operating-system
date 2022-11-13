/* getstk.c - getstk */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  vmhgetstk  -  Allocate stack memory, returning highest word address
 *------------------------------------------------------------------------
 */
char* vmhgetstk(uint16 msize)
{
	intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();
	if (msize == 0) {
		restore(mask);
		return (char *)SYSERR;
	}

    v32addr_t vaddr = vmhgetmem(msize);
	restore(mask);

	return (char *)(vaddr + (msize*NBPG) - sizeof(uint32));
}

