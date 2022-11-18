/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

process	main(void)
{

	/* Start the network */
	/* DO NOT REMOVE OR COMMENT THIS CALL */
	netstart();

	/* Initialize the page server */
	/* DO NOT REMOVE OR COMMENT THIS CALL */
	// psinit();

	// Insert test code below

	kprintf("\n\n\nHello World\n");

	// int* b_ptr = vmhgetmem(1);

	// if((uint32)b_ptr != SYSERR) {
    // kprintf("successfully allocated memory in VF: %x!\n", b_ptr);
	// }

	// b_ptr[1] = 0;
	// unsigned long* eax = NULL;
    // asm("movl %%eax, %0;"
    //     :"=c"(eax)
    //     );
	// kprintf("eax is: %x\n", eax);
	// kprintf("main: %x\n", main);
	// kprintf("b_ptr: %d\n", b_ptr[0]);
	// kprintf("b_ptr: %d\n", b_ptr[1]);
	// kprintf("b_ptr: %d\n", b_ptr[100]);
	// kprintf("b_ptr: %d\n", b_ptr[200]);

	test_vmhgetmem(10);

	return OK;
}
