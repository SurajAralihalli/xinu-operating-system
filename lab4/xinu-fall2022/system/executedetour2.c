/* executedetour2.c - executedetour2 */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  executedetour2  -  Called by clock interrupt handler to awaken processes
 *------------------------------------------------------------------------
 */

void executedetour2(void)
{
    // initialize
    struct procent *prptr = &proctab[currpid];
    
    // exit
    if(prptr->prmakedetour!=1)
    {
        return;
    }

    //set prmakedetour to 0
    prptr->prmakedetour=0;

    // kprintf("\n ##Invoking prcbftn from executedetour2## \n");
    
    //invoke the function
    (proctab[currpid].prcbftn)();

}