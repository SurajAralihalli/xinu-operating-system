/* inspectmaxprio.c - inspectmaxprio */

#include <xinu.h>

pri16 inspectmaxprio(void)
{
    intmask	mask;			/* Saved interrupt mask		*/

	mask = disable();

    int priority = 9;
    while(priority>=0)
    {
        // atleast one pid is in the queue
        if(dynqueue[priority].count>=1)
        {
            break;
        }
        priority--;
    }

    restore(mask);
    return priority>=0?priority:SYSERR;
}