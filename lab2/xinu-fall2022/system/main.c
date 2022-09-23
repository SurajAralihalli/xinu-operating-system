/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
    
    kprintf("\nTest process running code of main(): %d\n\n", getpid());	
    lab2Tests();
	return OK;
    
}
