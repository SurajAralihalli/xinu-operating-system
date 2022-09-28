/* mytests.c - mytests */

#include <xinu.h>


/*------------------------------------------------------------------------
 * mytests - to check if the developed features are working as expected
 *------------------------------------------------------------------------
 */

int breakLoop = 0;
int userCpuTime[4];
int iter[4];
int endTime[4];

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
        kprintf("\n FAIL address2:0x%x - address1:0x%x != 8 \n",address2,address1);
    }
    else
    {
        kprintf("\n PASS address2:0x%x - address1:0x%x == 8 \n",address2,address1);
    }

    if(address3-address2!=8)
    {
        kprintf("\n FAIL address3:0x%x - address2:0x%x != 8 \n",address3, address2);
    }
    else
    {
        kprintf("\n PASS address3:0x%x - address2:0x%x == 8 \n",address3, address2);
    }

    if(address4-address3!=32)
    {
        kprintf("\n FAIL address4:0x%x - address3:0x%x != 8 \n",address4, address3);
    }
    else
    {
        kprintf("\n PASS address4:0x%x - address4:0x%x == 8 \n",address4, address3);
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

void loopALot(int id)
{
    int i=0;
    while(i!=999999 && breakLoop==0)
    {
        i++;
    }
    if(breakLoop==0)
    {
        breakLoop = 1;
    }

    iter[id] = i;
    userCpuTime[id] = usercpu(currpid);
    endTime[id] = vfineclkcounter;
    return;
}

void loops1()
{
    resume(create(loopALot,1024,40,"loop1", 1, 0));
    resume(create(loopALot,1024,40,"loop2", 1, 1));
    resume(create(loopALot,1024,40,"loop3", 1, 2));
    resume(create(loopALot,1024,40,"loop4", 1, 3));
}


void q4test1()
{
    resume(create(loops1,1024,45,"q4test1", 0));
    sleep(5);
    int i=0;
    while(i!=4)
    {
        kprintf("\nid:%d, iter:%d, userCpuTime:%d, endTime:%d\n",i,iter[i],userCpuTime[i], endTime[i]);
        i++;
    }

    // reset it for q4test2
    breakLoop = 0;
}

void loopWithGetPrio(int id)
{
    int i=0;
    while(breakLoop==0)
    {
        getprio(currpid);
        i++;
    }
    iter[id] = i;
    endTime[id] = vfineclkcounter;
    userCpuTime[id] = usercpu(currpid);
    return;
}

void loops2()
{
    resume(create(loopALot,1024,40,"loop1", 1, 0));
    resume(create(loopALot,1024,40,"loop2", 1, 1));
    resume(create(loopWithGetPrio,1024,40,"loop3", 1, 2));
    resume(create(loopWithGetPrio,1024,40,"loop4", 1, 3));
}


void q4test2()
{
    resume(create(loops2,1024,45,"q4test2", 0));
    sleep(5);
    int i=0;
    while(i!=4)
    {
        kprintf("\nid:%d, iter:%d, userCpuTime:%d, endTime:%d\n",i,iter[i],userCpuTime[i], endTime[i]);
        i++;
    }
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
        kprintf("\n FAIL usercpu(currpid):%d!=usercpux(currpid):%d \n",ms1,ms2);
    }
    else
    {
        kprintf("\n PASS usercpu(currpid):%d==usercpux(currpid):%d \n",ms1,ms2);
    }
    return;
}

void test5()
{
    resume(create(process5,1024,45,"process5", 0));
}

void test6help()
{
    uint16 cpuUtil = cpuutil();    
    if(cpuUtil!=100)
    {
        kprintf("\nPASS cpuUtil:%d != 100 \n",cpuUtil);
    }
    else
    {
        kprintf("\nFAIL cpuUtil:%d == 100 \n",cpuUtil);
    }
    
}

void test6()
{
    resume(create(test6help,1024,45,"test6", 0));
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

    kprintf("\n###q4test1####\n");
    q4test1();
    sleep(1);
    kprintf("\n###q4test2####\n");
    q4test2();
    sleep(1);

    kprintf("\n###test5####\n");
    test5();
    kprintf("\n###test6####\n");
    test6();
    #endif
}

