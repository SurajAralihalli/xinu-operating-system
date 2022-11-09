/*  myhello.c  - myhello */

#include <xinu.h>

process	myhello(void)
{
    #ifdef XINUTEST
    kprintf("\n##############################################################################\n");
    kprintf("\nGreetings from Suraj Aralihalli!\nUsername: saraliha\n");
    kprintf("\n##############################################################################\n\n");
    #endif
	return OK;
    
}