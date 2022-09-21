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
	pri16 oldprio=10;
    // asm("movl $22, %eax");
	// asm("int $46");
    // asm("movl %%eax, %0"
    //     : "=r"(oldprio)
    // );
	return oldprio;
}