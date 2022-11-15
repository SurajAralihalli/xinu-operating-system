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

	kprintf("Hello World\n");

	/* Testing getmem() */
	char* a_ptr = getmem(4);
	a_ptr[0] = 'h';
	a_ptr[1] = 'i';
	a_ptr[2] = '\0'; 

	kprintf("a_ptr: %s\n", a_ptr);

	/* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(1);
	if((uint32)b_ptr != SYSERR) {
		kprintf("successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
	for(i = 0; i < 100; i++) {
		b_ptr[i] = '1';
		kprintf("i:%d\n", i);
	}
	b_ptr[100] = '\0';
	kprintf("b_ptr: %s\n", b_ptr);

	int ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory\n");
	}

	return OK;
}
