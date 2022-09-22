/*  main.c  - main */

#include <xinu.h>

process	main(void)
{
    
    kprintf("\nTest process running code of main(): %d\n\n", getpid());	
    // pid32 pid = 1000;
    // pid = getpidx();
    // kprintf("\npid is %d\n",pid);
    // pri16 oldPri = chpriox(pid, 300);
    // kprintf("\n oldpri is %d\n",oldPri);
    // kprintf("\n newpri is %d\n",getprio(pid));

    // kprintf("\n%x\n",getmem(4));
    // kprintf("\n%x\n",getmemx(4));
    // kprintf("\n%x\n",getmem(8));
    // kprintf("\n%x\n",getmemx(8));


	return OK;
    
}
