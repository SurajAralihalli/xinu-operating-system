/* mytests.c - mytests */

#include <xinu.h>


/*------------------------------------------------------------------------
 * mytests - to check if the developed features are working as expected
 *------------------------------------------------------------------------
 */

void func()
{
    int i=0;
    while(i!=999999)
    {
        i++;
    }
    kprintf("\n I was called \n");

}

void process1()
{
    int i=0;
    alarmx(3, func);
    while(i!=999999)
    {
        i++;
        if(i%2==0)
        {
            getprio(currpid);
        }
    }
}

void test1()
{
    resume(create(process1,1024,25,"process1", 0));
}


void lab4Tests()
{
    #ifdef XINUDEBUG
    // kprintf("\n###test1####\n");
    // test1();
    // sleep(1);
    #endif
}