/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
    
    kprintf("\nTest process running code of main(): %d\n\n", getpid());	
    pid32 pid = 1000;
    pid = getpidx();
    kprintf("\npid is %d\n",pid);
	return OK;
    
}
