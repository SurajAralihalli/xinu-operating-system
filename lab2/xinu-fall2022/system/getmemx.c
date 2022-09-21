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

    //push arguments
    asm("pushl %0"
        :
        : "r"(nbytes));

	asm("int $46");
    asm("movl %%eax, %0"
        : "=r"(curr)
    );
    
    //pop arguments
    asm("popl %ecx");


    return curr;
}