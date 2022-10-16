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

void process2()
{
    int i=10;
    while(i==0)
    {
        i--;
    }
    sleepms(10);
    i=10;
    while(i==0)
    {
        i--;
    }
    sleepms(10);

    if(proctab[currpid].prcurrcount==3)
    {
        kprintf("\n PASS proctab[currpid].prcurrcount==%d \n",proctab[currpid].prcurrcount);
    }
    else
    {
        kprintf("\n FAIL proctab[currpid].prcurrcount==%d \n",proctab[currpid].prcurrcount);
    }
	
}

void test2()
{
    resume(create(process2,1024,45,"process2", 0));
}

void process3a()
{
    // fetch pid's prusercpu
    struct	procent	*prptr;
    prptr = &proctab[currpid];

    uint32 totalresponseMs = prptr->prtotalresponse / (double)(389 * 1000);

    if(resptime(currpid) == totalresponseMs)
    {
        kprintf("\n PASS avgresptime == totalresponseMs (%d) \n",totalresponseMs);
    }
    else
    {
        kprintf("\n FAIL avgresptime == totalresponseMs (%d) \n",totalresponseMs);
    }

    if(prptr->prmaxresponse == totalresponseMs)
    {
        kprintf("\n PASS maxresponse == totalresponseMs (%d) \n",totalresponseMs);
    }
    else
    {
        kprintf("\n FAIL maxresponse == totalresponseMs (%d) \n",totalresponseMs);
    }

    int i=0;
    while(i!=99999999)
    {
        i++;
    }
}

void process3b()
{
    resume(create(process3a,1024,35,"process3a", 1, 1));
    int i=0;
    while(i!=99999999)
    {
        i++;
    }
}

void test3()
{
    resume(create(process3b,1024,45,"process3b", 0));
}

void process4()
{
    int i=0;
    while(i!=999999999)
    {
        i++;
    }
    struct	procent	*prptr;
    prptr = &proctab[currpid];
    if(prptr->prpreemptcount1 + prptr->prpreemptcount2 <= prptr->prcurrcount)
    {
        kprintf("\n PASS prpreemptcount1(%d) + prpreemptcount2(%d) <= prcurrcount(%d) \n",prptr->prpreemptcount1,prptr->prpreemptcount2,prptr->prcurrcount);
    }
    else
    {
        kprintf("\n FAIL prpreemptcount1(%d) + prpreemptcount2(%d) <= prcurrcount(%d) \n",prptr->prpreemptcount1,prptr->prpreemptcount2,prptr->prcurrcount);
    }
}

void test4()
{
    resume(create(process4,1024,25,"process4", 0));
}

void process5()
{
    uint32 start = vfineclkcounter;
    int i=0;
    while(i<999999999)
    {
        if(vfineclkcounter - start>=2)
        {
            break;
        }
        i++;
    }
    kprintf("\n &&&&&&&&& iterations i:%d &&&&&&&&& \n",i);
}

void test5()
{
    resume(create(process5,1024,4,"cpu1", 0));
    resume(create(process5,1024,4,"cpu2", 0));
    resume(create(process5,1024,4,"cpu3", 0));
}


void process6()
{
   kprintf("\n before -> total resptime: %d, usercpu: %d \n", totcpu(currpid), proctab[currpid].prusercpu);
   sleep(5);
   kprintf("\n after -> total resptime: %d, usercpu: %d \n", totcpu(currpid), proctab[currpid].prusercpu);
}

void test6()
{
    resume(create(process6,1024,4,"cpu1", 0));
}



void lab3Tests()
{
    #ifdef XINUDEBUG
    // kprintf("\n###test1####\n");
    // test1();
    // sleep(1);
    // kprintf("\n###test2####\n");
    // test2();
    // sleep(1);
    // kprintf("\n###test3####\n");
    // test3();
    // sleep(1);
    // kprintf("\n###test4####\n");
    // test4();
    // sleep(1);
    // kprintf("\n### test6 ####\n");
    // test6();
    // sleep(3);
    #endif
}