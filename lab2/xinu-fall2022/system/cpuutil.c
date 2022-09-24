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
    uint16 percentage = ( timems / vfineclkcounter) * 100;

    // CPU util is (100 - idle process%)
    return (100-percentage);

}
