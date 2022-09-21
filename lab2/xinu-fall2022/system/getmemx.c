/* chpriox.c - chpriox */

#include <xinu.h>


/*------------------------------------------------------------------------
 *  getmemx  -  Wrapper function to getmem that allocates heap storage, returning lowest word address
 *------------------------------------------------------------------------
 */
char* getmemx(
	  uint32	nbytes		/* Size of memory requested	*/
	)
{
    char *curr;
    asm("movl $21, %eax");
	asm("int $46");
    asm("movl %%eax, %0"
        : "=r"(curr)
    );

    return curr;
}