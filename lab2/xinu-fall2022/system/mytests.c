/* mytests.c - mytests */

#include <xinu.h>

/*------------------------------------------------------------------------
 * mytests - to check if the developed features are working as expected
 *------------------------------------------------------------------------
 */

pid32 pidSample;

void process1()
{
    sleep(3);
    pid32 pid = getpidx();
    pri16 oldPri = chpriox(pid, 35);

    if(oldPri!=30)
    {
        kprintf("\n FAIL oldPri!=30 \n");
    }
    else
    {
        kprintf("\n PASS oldPri!=30 \n");
    }

    if(getprio(pid)!=35)
    {
        kprintf("\n FAIL getprio(pid)!=35 \n");
    }
    else
    {
        kprintf("\n PASS getprio(pid)==35 \n");
    }
}

void test1()
{
    resume(create(process1,1024,30,"process1", 0));
}

void test2()
{
    char* address1 = getmemx(8);
    char* address2 = getmem(8);
    char* address3 = getmemx(32);
    char* address4 = getmem(32);
    
    if(address2-address1!=8)
    {
        kprintf("\n FAIL address2-address1!=8 \n");
    }
    else
    {
        kprintf("\n PASS address2-address1!=8 \n");
    }

    if(address3-address2!=8)
    {
        kprintf("\n FAIL address3-address2!=8 \n");
    }
    else
    {
        kprintf("\n PASS address3-address2==8 \n");
    }

    if(address4-address3!=32)
    {
        kprintf("\n FAIL address4-address3!=32 \n");
    }
    else
    {
        kprintf("\n PASS address4-address3==32 \n");
    }
    
}


void process3()
{
    if(getpid()!=getpidx())
    {
        kprintf("\n FAIL getpid()!=getpidx() \n");
    }
    else
    {
        kprintf("\n PASS getpid()==getpidx() \n");
    }
}

void test3()
{
    resume(create(process3,1024,30,"process3", 0));
}


void lab2Tests()
{
    #ifdef XINUDEBUG
    test1();
    test2();
    test3();
    #endif
}

