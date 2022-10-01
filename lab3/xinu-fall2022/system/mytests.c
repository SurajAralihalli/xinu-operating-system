/* mytests.c - mytests */

#include <xinu.h>


/*------------------------------------------------------------------------
 * mytests - to check if the developed features are working as expected
 *------------------------------------------------------------------------
 */

void process1()
{
    int i=0;
    while(i!=999999)
    {
        i++;
        if(i%2==0)
        {
            getprio(currpid);
        }
    }

    uint32 utime = usercpu(currpid);
    uint32 ttime = totcpu(currpid);

    if(ttime > utime)
    {
        kprintf("\n PASS ttime:%d > utime:%d \n",ttime,utime);
    }
    else
    {
        kprintf("\n FAIL ttime:%d < utime:%d \n",ttime,utime);
    }

}

void test1()
{
    resume(create(process1,1024,25,"process1", 0));
}

void lab3Tests()
{
    #ifdef XINUDEBUG
    kprintf("\n###test1####\n");
    test1();
    sleep(1);
    #endif
}