#include <xinu.h>

void vmhgetmem_procA()
{
    kprintf("in vmhgetmem_procA\n");
    /* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(1);
	if((uint32)b_ptr != SYSERR) {
		kprintf("successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
	for(i = 0; i < 100; i++) {
		b_ptr[i] = '1';
	}
	b_ptr[100] = '\0';
	kprintf("b_ptr: %s:\n", b_ptr);

	int ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory\n");
	}

    /* All frames in E1 should be free */
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1) {
            kprintf("Frame %d not free!\n", i);
        }
    }

    /* Only frames corresponding to page directory and page tables should be used */
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1) {
            kprintf("Frame %d not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
        }
    }

}

void vmhgetmem_procB()
{
    kprintf("in vmhgetmem_procB\n");
    
    /* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(1);
	if((uint32)b_ptr != SYSERR) {
		kprintf("successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
	for(i = 0; i < 100; i++) {
		b_ptr[i] = '1';
	}
	b_ptr[100] = '\0';
	kprintf("b_ptr: %s:\n", b_ptr);


    /* Frames should be used since they are not freed */
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1) {
            kprintf("Frame %d not free!\n", i);
        }
    }

    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1) {
            kprintf("Frame %d not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
        }
    }
}

void vmhgetmem_procC()
{
    
    kprintf("in vmhgetmem_procC\n");
    
    /* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(2);
	if((uint32)b_ptr != SYSERR) {
		kprintf("successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
	for(i = 0; i < 5000; i++) {
        b_ptr[i] = 'A';
	}
	b_ptr[5000] = '\0';
	kprintf("b_ptr: %s:\n", b_ptr);

	int ret = vmhfreemem(b_ptr, 2);
	if(ret == OK) {
		kprintf("Successfully freed memory\n");
	}

    /* Segmentation fault check - Should fail */
    kprintf("b_ptr[0]: %c\n", b_ptr[0]);

    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1) {
            kprintf("Frame %d not free!\n", i);
        }
    }

    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1) {
            kprintf("Frame %d not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
        }
    }
}

void test_vmhgetmem(int test_num)
{
    if(test_num == 1) {
        /* Basic test - Allocate one page, write 100 bytes and deallocate page */
        resume (create((void *)vmhgetmem_procA, INITSTK, INITPRIO, "vmhgetmem_procA process", 0, NULL));
    }

    if(test_num == 2) {
        /* Allocate one page, write 100 bytes and do not deallocate page. Deallocation should be done during process termination */
        resume (create((void *)vmhgetmem_procB, INITSTK, INITPRIO, "vmhgetmem_procB process", 0, NULL));
    }

    if(test_num == 3) {
        /* Allocate 2 pages and write to both pages. 2 page faults must be generated. Deallocate pages using vmhfreemem. Access page again to verify in unallocated memory check has been implemented */
        resume (create((void *)vmhgetmem_procC, INITSTK, INITPRIO, "vmhgetmem_procC process", 0, NULL));    
    }

    if(test_num == 4) {
        /* Allocate 2 pages and write to both pages. 2 page faults must be generated. Deallocate pages using using 2 separate calls to vmhfreemem() */
    }

    if(test_num == 5) {
        /* Allocate a page and write to it. Verify if R/W access violation check has been implemented - array indexing error */        
    }

    if(test_num == 6) {
        /* Allocate a page and write to it. Verify if unallocated memory check has been implemented. Access a page that has been freed using vmhfreemem */        
    }

    if(test_num == 7) {
        /* Spawn multiple process (of equal priority) each creating multiple pages in VF. Checks if processes can reuse same memory location in VF */       
    }

    if(test_num == 8) {
        /* Verify if vmhgetmem() allocates msize contiguous pages */
    }

    if(test_num == 9) {
        /* Verify if identity mapping for all regions works */
    }

    if(test_num == 10) {
        /* Verify if SYSERR is returned at appropriate places */
    }

    if(test_num == 11) {
        /* Verify if double vmhfreemem() fails */
    }

}