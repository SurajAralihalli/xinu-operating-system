/* getpidx.c - getpidx */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  getpidx  -  Wrapper function to getpid thats returns the ID of the currently executing process
 *------------------------------------------------------------------------
 */
pid32	getpidx(void)
{
    pid32 pid;
    // call getpid
    asm("movl $20, %eax");
    // call interrupt
	asm("int $46");
    asm("movl %%eax, %0"
        : "=r"(pid)
    );
    // asm("popl %ebx");
    return pid;
}