/* usercpux.c - usercpux */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  usercpux  -  Wrapper function to usercpu
 *------------------------------------------------------------------------
 */
int32	usercpux(
	  pid32		pid		/* ID of process to change	*/
	)
{
	int32 cpums= (int32) SYSERR;

	// push arguments
	asm("pushl %0"
        :
        : "r"(pid));

    // call usercpux
    asm("movl $23, %eax");

	// call interrupt
	asm("int $46");
    asm("movl %%eax, %0"
        : "=r"(cpums)
    );

	//pop arguments
    asm("popl %ecx");
	return cpums;
}