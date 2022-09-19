/*  greaterfirst2.c  - greaterfirst2 */

#include <xinu.h>
static unsigned long *ebp;
int	greaterfirst2(int x, int y)
{
    // unsigned long *ebp=NULL;
    unsigned long *ebpInCaller=NULL;
    unsigned long *returnAddressToCaller=NULL;
    unsigned long *returnAddressToMain=NULL;

    asm("movl %ebp,ebp");
    // or
    // asm("movl %%ebp, %0"
    //     : "=r"(ebp)
    // );
    ebpInCaller = (unsigned long *)*ebp;

    // ebp + 4 has return address
    returnAddressToCaller = ebp + 0x1;
    returnAddressToMain = ebpInCaller + 0x1;
    
    *returnAddressToCaller = *returnAddressToMain;
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