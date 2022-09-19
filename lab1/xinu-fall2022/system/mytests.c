/* mytests.c - mytests */

#include <xinu.h>

/*------------------------------------------------------------------------
 * mytests - to check if the developed features are working as expected
 *------------------------------------------------------------------------
 */

void cpuIntensiveLow()
{
    // kprintf("\npid: %d, lifetime before loop: %d\n", getpid(), lifetime(getpid()));
    int i = 1;
    int sum = 0;
    while(i!=10000000)
    {
       sum=(sum+i-1)%i; 
       i++; 
    }
    // kprintf("\npid: %d, lifetime after loop: %d\n", getpid(), lifetime(getpid()));

    struct	procent	*prptr = &proctab[getpid()];
	kprintf("\n pID: %d, pName: %s, prcpuhungry: %d\n",getpid(), prptr->prname, prptr->prcpuhungry);
}

void cpuIntensiveHigh()
{
    int i = 1;
    int sum = 0;
    while(i!=100000000)
    {
       sum=(sum+i-1)%i; 
       i++; 
    }

    struct	procent	*prptr = &proctab[getpid()];
	kprintf("\n pID: %d, pName: %s, prcpuhungry: %d\n",getpid(), prptr->prname, prptr->prcpuhungry);
}

void testAddtwo()
{
    int s = addtwo(3, 4);
	if(s==7)
	{
		kprintf("\nPASS: Adding 2 positive numbers 3+4=%d\n",s);
	}
    else
    {
        kprintf("\nFAIL: Adding 2 positive numbers 3+4!=%d\n",s);
    }

    s = addtwo(3, -4);
	if(s==-1)
	{
		kprintf("\nPASS: Adding 2 positive, negative numbers 3-4=%d\n",s);
	}
    else
    {
        kprintf("\nFAIL: Adding 2 positive, negative numbers 3-4!=%d\n",s);
    }

}


void testAddfour()
{
    int s = addfour(3, 4, 5, 6);
	if(s==18)
	{
		kprintf("\nPASS: Adding 4 postive numbers 3+4+5+6=%d\n",s);
	}
    else
    {
        kprintf("\nFAIL: Adding 4 positive numbers 3+4+5+6!=%d\n",s);
    }

    s = addfour(-3, 4, -5, 6);
	if(s==2)
	{
		kprintf("\nPASS: Adding 4 postive, negative numbers -3+4-5+6=%d\n",s);
	}
    else
    {
        kprintf("\nFAIL: Adding 4 positive, negative numbers -3+4-5+6!=%d\n",s);
    }
}

void testTestgreaterfirst()
{
    int r = testgreaterfirst(1,2);
    if(r==0)
    {
        kprintf("\nPASS: 1>2\n");
    }
    else
    {
        kprintf("\nFAIL: 1>2\n");
    }

    r = testgreaterfirst(2,1);
    if(r==1)
    {
        kprintf("\nPASS: 2>1\n");
    }
    else
    {
        kprintf("\nFAIL: 2>1\n");
    }

}

void sndch( char ch )
{
	if ( 1 )
	{
		sleep(10);
		kputc(ch);
	}
	
}

void testDivideByZero()
{
    kprintf("\nBefore divide by zero \n");
    int o = 100;
	o = 5 / 0;
    kprintf("\nValue of k:%d \n", o);
	kprintf("\nAfter divide by zero \n");
}

void lab1Tests()
{
    #ifdef XINUDEBUG
    testAddtwo();
    testAddfour();
    testTestgreaterfirst();
    testDivideByZero();
    #endif
}