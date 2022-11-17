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
	// kprintf("b_ptr: before: %c\n", b_ptr[0]);
	for(i = 0; i < 100; i++) {
		b_ptr[i] = 'A';
	}
	b_ptr[100] = '\0';
	kprintf("b_ptr: %s\n", b_ptr);

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

void vmhgetmem_procD()
{    
    kprintf("in vmhgetmem_procD\n");
    
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

	int ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory - 1\n");
	}

	ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory - 2\n");
	}

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

void vmhgetmem_procE()
{
    /* TODO: Page should be created as read-only */
    kprintf("in vmhgetmem_procE\n");
    
    /* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(1);
	if((uint32)b_ptr != SYSERR) {
		kprintf("successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
    /* Write operation on read-only page */
	for(i = 0; i < 1000; i++) {
        b_ptr[i] = 'A';
	}

    /* Anything beyond this point should not execute */
	b_ptr[1000] = '\0';
	kprintf("b_ptr: %s:\n", b_ptr);

	int ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory - 1\n");
	}

	ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory - 2\n");
	}

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

void vmhgetmem_procF()
{
    kprintf("in vmhgetmem_procF\n");

    /* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(1);
	if((uint32)b_ptr != SYSERR) {
		kprintf("successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
	// kprintf("b_ptr: before: %c\n", b_ptr[0]);
	for(i = 0; i < 4096; i++) {
		b_ptr[i] = 'A';
	}
	b_ptr[4096] = '\0'; // Should cause page fault leading to segmentation fault

	kprintf("b_ptr: %s\n", b_ptr);

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

void vmhgetmem_procG()
{
    kprintf("in vmhgetmem_procG\n");

    /* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(2);
	if((uint32)b_ptr != SYSERR) {
		kprintf("G: successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
	// kprintf("b_ptr: before: %c\n", b_ptr[0]);
	for(i = 0; i < 5000; i++) {
		b_ptr[i] = 'G';
	}
	b_ptr[10] = '\0'; // Should cause page fault leading to segmentation fault

	kprintf("G: b_ptr: %s\n", b_ptr);

	int ret = vmhfreemem(b_ptr, 2);
	if(ret == OK) {
		kprintf("Successfully freed memory in G\n");
	}

    /* All frames in E1 should be free */
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1) {
            kprintf("G:  %d not free!\n", i);
        }
    }

    /* Only frames corresponding to page directory and page tables should be used */
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1) {
            kprintf("G: Frame %d not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
        }
    }
}

void vmhgetmem_procH()
{
    kprintf("in vmhgetmem_procH\n");

    /* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(1);
	if((uint32)b_ptr != SYSERR) {
		kprintf("H: successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
	// kprintf("b_ptr: before: %c\n", b_ptr[0]);
	for(i = 0; i < 4000; i++) {
		b_ptr[i] = 'H';
	}
	b_ptr[10] = '\0'; // Should cause page fault leading to segmentation fault

	kprintf("H: b_ptr: %s\n", b_ptr);

	int ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory in H\n");
	}

    /* All frames in E1 should be free */
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1) {
            kprintf("H: Frame %d not free!\n", i);
        }
    }

    /* Only frames corresponding to page directory and page tables should be used */
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1) {
            kprintf("H: Frame %d not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
        }
    }
}

void vmhgetmem_procI()
{
    kprintf("in vmhgetmem_procI\n");

    /* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(3);
	if((uint32)b_ptr != SYSERR) {
		kprintf("I: successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
	// kprintf("b_ptr: before: %c\n", b_ptr[0]);
	for(i = 0; i < 9000; i++) {
		b_ptr[i] = 'I';
	}
	b_ptr[10] = '\0'; // Should cause page fault leading to segmentation fault

	kprintf("I: b_ptr: %s\n", b_ptr);

	int ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory in I\n");
	}

    /* All frames in E1 should be free */
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1) {
            kprintf("I: Frame %d not free!\n", i);
        }
    }

    /* Only frames corresponding to page directory and page tables should be used */
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1) {
            kprintf("I: Frame %d not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
        }
    }
}

void vmhgetmem_procJ()
{
    /* Check if identity mapping is working correctly for Region G */
    kprintf("in vmhgetmem_procJ\n");

    char* addr_G = 0x90000000;
    kprintf("Accessing G: %d\n",addr_G[0]);

    char* addr_B = 1052672;
    kprintf("Accessing B: %d\n",addr_B[0]);

    char* addr_C = 1339395;
    kprintf("Accessing C: %d\n",addr_C[0]);

    char* addr_D = 4194400;
    kprintf("Accessing D: %d\n",addr_D[0]);

    char* addr_E = 12288000;
    kprintf("Accessing E: %d\n",addr_E[0]);
}

void vmhgetmem_procK()
{
    kprintf("in vmhgetmem_procK\n");

    /* Testing vmhgetmem() */
	char* b_ptr = vmhgetmem(1);
	if((uint32)b_ptr != SYSERR) {
		kprintf("K: successfully allocated memory in VF: %x!\n", b_ptr);		
	}
	uint32 i;
	// kprintf("b_ptr: before: %c\n", b_ptr[0]);
	for(i = 0; i < 100; i++) {
		b_ptr[i] = 'K';
	}
	b_ptr[10] = '\0'; // Should cause page fault leading to segmentation fault

	kprintf("K: b_ptr: %s\n", b_ptr);

	int ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory in I\n");
	}

    /* Should fail! */
	ret = vmhfreemem(b_ptr, 1);
	if(ret == OK) {
		kprintf("Successfully freed memory in I\n");
	}

    /* All frames in E1 should be free */
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1) {
            kprintf("I: Frame %d not free!\n", i);
        }
    }

    /* Only frames corresponding to page directory and page tables should be used */
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1) {
            kprintf("I: Frame %d not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
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
        resume (create((void *)vmhgetmem_procD, INITSTK, INITPRIO, "vmhgetmem_procC process", 0, NULL));    
    }

    if(test_num == 5) {
        /* Allocate a page and write to it. Verify if R/W access violation check has been implemented */        
        resume (create((void *)vmhgetmem_procE, INITSTK, INITPRIO, "vmhgetmem_procE process", 0, NULL));    
    }

    if(test_num == 6) {
        /* Allocate a page and write to it. Verify if unallocated memory check has been implemented - array indexing error */        
        resume (create((void *)vmhgetmem_procF, INITSTK, INITPRIO, "vmhgetmem_procF process", 0, NULL));    
    }

    if(test_num == 7) {
        /* Spawn multiple process (of equal priority) each creating multiple pages in VF. Checks if processes can reuse same memory location in VF */       
        resume (create((void *)vmhgetmem_procG, INITSTK, INITPRIO, "vmhgetmem_procG process", 0, NULL));    
        resume (create((void *)vmhgetmem_procH, INITSTK, INITPRIO, "vmhgetmem_procH process", 0, NULL));    
        resume (create((void *)vmhgetmem_procI, INITSTK, INITPRIO, "vmhgetmem_procI process", 0, NULL));    
    }

    if(test_num == 9) {
        /* Verify if identity mapping for all regions works */
        resume (create((void *)vmhgetmem_procJ, INITSTK, INITPRIO, "vmhgetmem_procJ process", 0, NULL));    
    }

    if(test_num == 10) {
        /* Verify if double vmhfreemem() fails */
        resume (create((void *)vmhgetmem_procK, INITSTK, INITPRIO, "vmhgetmem_procK process", 0, NULL));    
    }

}