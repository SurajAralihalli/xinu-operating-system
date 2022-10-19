/*  main.c  - main */

#include <xinu.h>

void benchmarkA()
{
    resume(createtsx(cpubound,1024,TSXINIT,"cpubound1", 0));
    resume(createtsx(cpubound,1024,TSXINIT,"cpubound2", 0));
    resume(createtsx(cpubound,1024,TSXINIT,"cpubound3", 0));
    resume(createtsx(cpubound,1024,TSXINIT,"cpubound4", 0));
    resume(createtsx(cpubound,1024,TSXINIT,"cpubound5", 0));
    resume(createtsx(cpubound,1024,TSXINIT,"cpubound6", 0));
    resume(createtsx(cpubound,1024,TSXINIT,"cpubound7", 0));
    resume(createtsx(cpubound,1024,TSXINIT,"cpubound8", 0));
}

// void benchmarkB()
// {
//     resume(createtsx(iobound,1024,"iobound1", 0));
//     resume(createtsx(iobound,1024,"iobound2", 0));
//     resume(createtsx(iobound,1024,"iobound3", 0));
//     resume(createtsx(iobound,1024,"iobound4", 0));
//     resume(createtsx(iobound,1024,"iobound5", 0));
//     resume(createtsx(iobound,1024,"iobound6", 0));
//     resume(createtsx(iobound,1024,"iobound7", 0));
//     resume(createtsx(iobound,1024,"iobound8", 0));
// }

// void benchmarkC()
// {
//     resume(createtsx(iobound,1024,"iobound5", 0));
//     resume(createtsx(iobound,1024,"iobound6", 0));
//     resume(createtsx(iobound,1024,"iobound7", 0));
//     resume(createtsx(iobound,1024,"iobound8", 0));
//     resume(createtsx(cpubound,1024,"cpubound1", 0));
//     resume(createtsx(cpubound,1024,"cpubound2", 0));
//     resume(createtsx(cpubound,1024,"cpubound3", 0));
//     resume(createtsx(cpubound,1024,"cpubound4", 0));
// }

// void benchmarkD()
// {

//     resume(createtsx(iobound,1024,"iobound1", 0));
//     resume(createtsx(iobound,1024,"iobound2", 0));
//     resume(createtsx(iobound,1024,"iobound3", 0));
//     resume(createtsx(iobound,1024,"iobound4", 0));
//     resume(createtsx(iobound,1024,"iobound5", 0));
//     resume(createtsx(iobound,1024,"iobound6", 0));
//     resume(createtsx(iobound,1024,"iobound7", 0));
//     resume(createtsx(iobound,1024,"iobound8", 0));
//     resume(createtsx(iobound,1024,"iobound9", 0));

//     resume(createtsx(iobound,1024,"iobound1", 0));
//     resume(createtsx(iobound,1024,"iobound2", 0));
//     resume(createtsx(iobound,1024,"iobound3", 0));
//     resume(createtsx(iobound,1024,"iobound4", 0));
//     resume(createtsx(iobound,1024,"iobound5", 0));
//     resume(createtsx(iobound,1024,"iobound6", 0));
//     resume(createtsx(iobound,1024,"iobound7", 0));
//     resume(createtsx(iobound,1024,"iobound8", 0));
//     resume(createtsx(iobound,1024,"iobound9", 0));

//     resume(createtsx(iobound,1024,"iobound1", 0));
//     resume(createtsx(iobound,1024,"iobound2", 0));
//     resume(createtsx(iobound,1024,"iobound3", 0));
//     resume(createtsx(iobound,1024,"iobound4", 0));
//     resume(createtsx(iobound,1024,"iobound5", 0));
//     resume(createtsx(iobound,1024,"iobound6", 0));
//     resume(createtsx(iobound,1024,"iobound7", 0));
//     resume(createtsx(iobound,1024,"iobound8", 0));
//     resume(createtsx(iobound,1024,"iobound9", 0));

//     resume(createtsx(iobound,1024,"iobound1", 0));
//     resume(createtsx(iobound,1024,"iobound2", 0));
//     resume(createtsx(iobound,1024,"iobound3", 0));
//     resume(createtsx(iobound,1024,"iobound4", 0));
//     resume(createtsx(iobound,1024,"iobound5", 0));
//     resume(createtsx(iobound,1024,"iobound6", 0));
//     resume(createtsx(iobound,1024,"iobound7", 0));
//     resume(createtsx(iobound,1024,"iobound8", 0));
//     resume(createtsx(iobound,1024,"iobound9", 0));

//     resume(createtsx(iobound,1024,"iobound1", 0));
//     resume(createtsx(iobound,1024,"iobound2", 0));
//     resume(createtsx(iobound,1024,"iobound3", 0));
//     resume(createtsx(iobound,1024,"iobound4", 0));
//     resume(createtsx(iobound,1024,"iobound5", 0));
//     resume(createtsx(iobound,1024,"iobound6", 0));
//     resume(createtsx(iobound,1024,"iobound7", 0));
//     resume(createtsx(iobound,1024,"iobound8", 0));
//     resume(createtsx(iobound,1024,"iobound9", 0));

//     resume(createtsx(iobound,1024,"iobound1", 0));
//     resume(createtsx(iobound,1024,"iobound2", 0));
//     resume(createtsx(iobound,1024,"iobound3", 0));
//     resume(createtsx(iobound,1024,"iobound4", 0));
//     resume(createtsx(iobound,1024,"iobound5", 0));
//     resume(createtsx(iobound,1024,"iobound6", 0));
//     resume(createtsx(iobound,1024,"iobound7", 0));
//     resume(createtsx(iobound,1024,"iobound8", 0));
//     resume(createtsx(iobound,1024,"iobound9", 0));

//     resume(createtsx(iobound,1024,"iobound1", 0));
//     resume(createtsx(iobound,1024,"iobound2", 0));
//     resume(createtsx(iobound,1024,"iobound3", 0));
//     resume(createtsx(iobound,1024,"iobound4", 0));
//     resume(createtsx(iobound,1024,"iobound5", 0));
//     resume(createtsx(iobound,1024,"iobound6", 0));
//     resume(createtsx(iobound,1024,"iobound7", 0));
//     resume(createtsx(iobound,1024,"iobound8", 0));
//     resume(createtsx(iobound,1024,"iobound9", 0));

//     resume(createtsx(cpubound,1024,"cpubound1", 0));


// }

process	main(void)
{	
    benchmarkA();
	return OK;
}
