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

    // kprintf("in vmhgetmem_procC\n");

    
    /* Testing vmhgetmem() */
	int* b_ptr = (int*) vmhgetmem(2);
	if((uint32)b_ptr != SYSERR) {
		kprintf("successfully allocated memory in VF: %x!\n", b_ptr);		
	}
    *b_ptr = 4;
	kprintf("b_ptr: %x\n", *b_ptr);
	// uint32 i;
    // kprintf("b_ptr[0]:%c\n", b_ptr[0]);
	// b_ptr[0] = 'A';
	// for(i = 0; i < 5000; i++) {
    //     b_ptr[i] = 'A';
	// }
	// b_ptr[10] = '\0';
	// kprintf("b_ptr: %c\n", b_ptr[0]);
    // b_ptr += 4096;
    // b_ptr[10] = '\0';
	// kprintf("b_ptr: %s\n", b_ptr);

	int ret = vmhfreemem((char*) b_ptr, 2);
	if(ret == OK) {
		kprintf("Successfully freed memory\n");
	}

    /* Segmentation fault check - Should fail */
    // kprintf("b_ptr[0]: %c\n", b_ptr[0]);

    // for(i = 0; i < NFRAMES_E1; i++) {
    //     if(fHolderListE1[i].frame_pres == 1) {
    //         kprintf("Frame %d not free!\n", i);
    //     }
    // }

    // for(i = 0; i < NFRAMES_D; i++) {
    //     if(fHolderListD[i].frame_pres == 1) {
    //         kprintf("Frame %d not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
    //     }
    // }


	// test_vmhgetmem(3);

	return OK;
}
