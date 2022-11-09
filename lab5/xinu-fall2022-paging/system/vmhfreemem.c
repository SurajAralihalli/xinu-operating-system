/* vmhfreemem.c */

#include <xinu.h>

/*------------------------------------------------------------------------
 * vmhfreemem  -  vmhfreemem() is a counterpart of freemem() with corresponding arguments for private heap in virtual memory, 
                  albeit with the second argument in unit of pages (not bytes)
 *------------------------------------------------------------------------
 */


syscall vmhfreemem(char *blockaddr, uint16 msize)
{
    return SYSERR;
}