/* executedetour.c - executedetour */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  executedetour  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */

struct detourHelper
{
    struct procent *prptr;
};

void executedetour(void)
{
    static struct detourHelper detour;

    detour.prptr = &proctab[currpid];

    // exit
    if(detour.prptr->prmakedetour!=1)
    {
        return;
    }
}