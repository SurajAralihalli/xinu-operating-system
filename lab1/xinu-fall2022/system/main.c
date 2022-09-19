/*  main.c  - main */

#include <xinu.h>
void sndch(char);


process	main(void)
{
    
    // kprintf("\nTest process running code of main(): %d\n\n", getpid());
	
	// testTemp();
	// resume( create(sndch, 1024, 20, "send A", 1, 'A') );
	// resume( create(sndch, 1024, 20, "send B", 1, 'B') );

	// create2(sndch, 1024, 20, "send A", 1, 'A');
	// create2(sndch, 1024, 20, "send B", 1, 'B');

	// kprintf("\n fineclkcounter: %d", fineclkcounter);
	// kprintf("\n vfineclkcounter: %d", vfineclkcounter);

	// sleep(5);
	// kprintf("\n fineclkcounter: %d", fineclkcounter);
	// kprintf("\n vfineclkcounter: %d", vfineclkcounter);

	// create2(cpuIntensiveLow, 2024, 20, "cpuLow", 0);
	// sleep(10);
	

	// create2(cpuIntensiveHigh, 1024, 20, "cpuHigh", 0);

	// testTestgreaterfirst();
    	
	// int s = addfour(3, 4, 5, 6);
	// if(s==18)
	// {
	// 	kprintf("3+4+5+6 = %d", s);
	// }

	// int o = testgreaterfirst(3,4);

	// kprintf("\n3>4 = %d\n", o);

	// greaterfirst1(1,3);

	// int o = 5 / 0;
	// kprintf("\n\nEnd of Main\n");

	lab1Tests();

	#ifdef XINUTEST
		sleep(5);
		kprintf("\n fineclkcounter: %d", fineclkcounter);
		kprintf("\n vfineclkcounter: %d", vfineclkcounter);
    #endif

	return OK;
    
}
