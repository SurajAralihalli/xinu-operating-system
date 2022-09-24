/* mytests.c - mytests */

#include <xinu.h>

/*------------------------------------------------------------------------
 * mytests - to check if the developed features are working as expected
 *------------------------------------------------------------------------
 */

pid32 pidSample;

void process1()
{
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

void loopALot()
{
    int i=0;
    while(usercpu(currpid) < 2500)
    {
        i++;
    }
    userCpuTime[currpid] = i;
    return;
}

void loops1()
{
    resume(create(loopALot,1024,40,"loop1", 0));
    resume(create(loopALot,1024,40,"loop2", 0));
    // resume(create(loopALot,1024,40,"loop3", 0));
    // resume(create(loopALot,1024,40,"loop4", 0));
}


void parentOfLoops1()
{
    resume(create(loops1,1024,45,"parentOfLoops1", 0));
}

void q4test1()
{
    parentOfLoops1();
}


void loopWithGetPrio()
{
    int i=0;
    while(usercpu(currpid) < 2500)
    {
        getprio(currpid);
        i++;
    }
    userCpuTime[currpid] = i;
    return;
}

void loops2()
{
    resume(create(loopALot,1024,40,"loop1", 0));
    resume(create(loopWithGetPrio,1024,40,"loop2", 0));
    resume(create(loopALot,1024,40,"loop3", 0));
    resume(create(loopWithGetPrio,1024,40,"loop4", 0));
}


void parentOfLoops2()
{
    resume(create(loops2,1024,45,"parentOfLoops2", 0));
}

void q4test2()
{
    parentOfLoops2();
}

void process5()
{
    int i=10000000;
    while(i!=0)
    {
        i--;
    }
    int32 ms1 = usercpu(currpid);
    int32 ms2 = usercpux(currpid);
    if(ms1!=ms2)
    {
        kprintf("\n FAIL %d!=%d \n",ms1,ms2);
    }
    else
    {
        kprintf("\n PASS %d==%d \n",ms1,ms2);
    }
    return;
}

void test5()
{
    resume(create(process5,1024,45,"process5", 0));
}


void lab2Tests()
{
    #ifdef XINUDEBUG
    kprintf("\n###test1####\n");
    test1();
    sleep(1);
    kprintf("\n###test2####\n");
    test2();
    sleep(1);
    kprintf("\n###test3####\n");
    test3();
    sleep(1);
    // kprintf("\n###q4test1####\n");
    // q4test1();
    // sleep(1);
    // kprintf("\n###q4test2####\n");
    // q4test2();
    // sleep(1);
    kprintf("\n###test5####\n");
    test5();
    #endif
}

