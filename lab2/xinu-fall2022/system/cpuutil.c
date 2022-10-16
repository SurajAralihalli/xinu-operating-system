/* cpuutil.c - cpuutil */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  cpuutil - Wrapper function to calculate CPU utilization
 *------------------------------------------------------------------------
 */


uint16 cpuutil(void)
{
    pid32 pidIdle = 0;
    uint32 timems = usercpu(pidIdle);
    uint16 percentage = ( (double)timems  * 100 / vfineclkcounter);

    // CPU util is (100 - idle process%)
    return (uint16)(100-percentage);

}
