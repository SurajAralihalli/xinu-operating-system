/* chpriox.c - chpriox */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  chpriox  -  Wrapper function to chprio thats changes the scheduling priority of a process
 *------------------------------------------------------------------------
 */
pri16	chpriox(
	  pid32		pid,		/* ID of process to change	*/
	  pri16		newprio		/* New priority			*/
	)
{
	pri16 oldprio= (pri16) SYSERR;

	// push arguments
    asm("push %0"
        :
        : "r"(newprio));
	asm("pushl %0"
        :
        : "r"(pid));

    // call chprio
    asm("movl $22, %eax");

	// call interrupt
	asm("int $46");
    asm("mov %%ax, %0"
        : "=r"(oldprio)
    );

	//pop arguments
    asm("popl %ecx");
    asm("popl %ecx");
	return oldprio;
}