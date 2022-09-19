/*  greaterfirst1.c  - greaterfirst1 */

#include <xinu.h>
static unsigned long *ebp;
int	greaterfirst1(int x, int y)
{
    // unsigned long *ebp=NULL;
    unsigned long *returnAddressToCaller=NULL;

    asm("movl %ebp,ebp");
    // or
    // asm("movl %%ebp, %0"
    //     : "=r"(ebp)
    // );

    // ebp + 4 has return address
    returnAddressToCaller = ebp + 0x1;
    
    *returnAddressToCaller = 0x123456;
    // or
    // asm("movl $0x123456, %0"
    //     : "=r"(*returnAddressToCaller)
    // );

    if(x>y) 
    {
        return 1;
    }
    {
        return 0;
    }
    
}