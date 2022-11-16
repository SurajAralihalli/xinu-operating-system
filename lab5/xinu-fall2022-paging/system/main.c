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

	/* Testing getmem() */
	char* a_ptr = getmem(4);
	a_ptr[0] = 'h';
	a_ptr[1] = 'i';
	a_ptr[2] = '\0'; 

	kprintf("a_ptr: %s\n", a_ptr);

	test_vmhgetmem(1);

	return OK;
}
