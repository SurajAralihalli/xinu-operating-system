/* inspectmaxprio.c - inspectmaxprio */

#include <xinu.h>

pri16 inspectmaxprio(void)
{
    int priority = 10;
    while(priority>=0)
    {
        // atleast one pid is in the queue
        if(dynqueue[priority].count>0)
        {
            break;
        }
        priority--;
    }
    return priority>=0?priority:SYSERR;
}