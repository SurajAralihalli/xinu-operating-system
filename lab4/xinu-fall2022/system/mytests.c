/* mytests.c - mytests */

#include <xinu.h>


/*------------------------------------------------------------------------
 * mytests - to check if the developed features are working as expected
 *------------------------------------------------------------------------
 */

void keepAlive()
{
    int i=0;
    while(i!=99999999)
    {
        i++;
    }
}

void func1()
{
    kprintf("\n func1 was called \n");
}

void func2()
{
    kprintf("\n func2 was called \n");   
}

void process1()
{
    kprintf("\n @@process1 started@@ \n");
    alarmx(3, func1);
    alarmx(8, func2);
    keepAlive();
    keepAlive();
    keepAlive();
    keepAlive();
    keepAlive();
    kprintf("\n @@process1 terminated@@ \n");

}

void test1()
{
    resume(create(process1,1024,25,"process1", 0));
}

void process2()
{
    kprintf("\n @@process2 started@@ \n");
    alarmx(4, func1);
    sleepms(5);
    kprintf("\n @@process2 terminated@@ \n");

}

void test2()
{
    resume(create(process2,1024,25,"process2", 0));
}


void lab4Tests()
{
    #ifdef XINUDEBUG
    // kprintf("\n###test1####\n");
    // test1();
    // sleep(1);
    kprintf("\n###test2####\n");
    test2();
    sleep(1);
    #endif
}