/*  main.c  - main */

#include <xinu.h>

void benchmarkA()
{
    resume(create(cpubound,1024,4,"cpubound1", 0));
    resume(create(cpubound,1024,4,"cpubound2", 0));
    resume(create(cpubound,1024,4,"cpubound3", 0));

    // resume(createtsx(cpubound,1024,"cpubound1", 0));
    // resume(createtsx(cpubound,1024,"cpubound2", 0));
    // resume(createtsx(cpubound,1024,"cpubound3", 0));
    // resume(createtsx(cpubound,1024,"cpubound4", 0));
    // resume(createtsx(cpubound,1024,"cpubound5", 0));
    // resume(createtsx(cpubound,1024,"cpubound6", 0));
    // resume(createtsx(cpubound,1024,"cpubound7", 0));
    // resume(createtsx(cpubound,1024,"cpubound8", 0));
}

process	main(void)
{	
    resume(create(cpubound,1024,4,"cpubound1", 0));
    resume(create(cpubound,1024,4,"cpubound2", 0));
    resume(create(cpubound,1024,4,"cpubound3", 0));
	return OK;
}
