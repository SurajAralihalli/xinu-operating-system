#include <xinu.h>


void test_swapping_procA()
{
    struct procent* prptr;
    uint16 num_pages_allocated = 512;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint16 i, j;

    prptr = &proctab[currpid];

    // Make E1 half-full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("A: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("A: page511:%d\t", ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    sleep(5);
    uint32 oldest_frame_index_E1 = get_index_oldest_frame_regionE1();;
    display_E1_oldest_frame_details(oldest_frame_index_E1, currpid);


    // Check size of E1 and E2
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1(currpid);
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2(currpid);
    kprintf("E1, E2 size: %d, %d\n", num_frames_allocated_E1, num_frames_allocated_E2);

    // Allocate another page n VF
    int* ptr2 = (int* )vmhgetmem(1);
    if((int)ptr2 == SYSERR) {
        kprintf("Failed to allocate virtual mem!\n");
        return;
    }
    for(i = 0 ; i < NBPG/4; i++) {
        ptr2[i] =  513;
    }

    for(i = 0; i < NBPG/4; i++) {
        kprintf("A: page513:%d\t", ptr2[i]);
        break;
    }
    kprintf("\n");

    // Check if fHolderListE1[older_frame_index] has correct entries - start of E1
    display_E1_oldest_frame_details(oldest_frame_index_E1, currpid);


	int ret = vmhfreemem((char*) ptr, num_pages_allocated);
	if(ret == OK) {
        intmask mask = disable();
		kprintf("Successfully freed memory in %s\n", prptr->prname);
        restore(mask);
	}

    ret = vmhfreemem((char*) ptr2, 1);
	if(ret == OK) {
        intmask mask = disable();
		kprintf("Successfully freed memory in %s\n", prptr->prname);
        restore(mask);
	}

    /* All frames in E1 must be free */
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1  && fHolderListE1[i].owner_process == currpid) {
            intmask mask = disable();
            kprintf("Frame %d in E1 not free!\n", i);
            restore(mask);
        }
    }

    for(i = 0; i < NFRAMES_E2; i++) {
        if(fHolderListE2[i].frame_pres == 1  && fHolderListE2[i].owner_process == currpid) {
            intmask mask = disable();
            kprintf("Frame %d in E2 not free!\n", i);
            restore(mask);
        }
    } 

    /* Only frames corresponding to page directory and page tables should be used */
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1 && fHolderListD[i].owner_process == currpid) {
            intmask mask = disable();
            kprintf("Frame %d in D not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
            restore(mask);
        }
    }
}


void test_swapping_procB()
{
    struct procent* prptr;
    uint16 num_pages_allocated = 512;

    // Allocate 512 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint16 i, j;

    prptr = &proctab[currpid];


    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("B: page1:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("B: page511:%d\t", ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    sleep(10);

    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1(currpid);
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2(currpid);
    kprintf("B: E1, E2 size: %d, %d\n", num_frames_allocated_E1, num_frames_allocated_E2);


    int ret = vmhfreemem((char*) ptr, num_pages_allocated);
	if(ret == OK) {
        intmask mask = disable();
		kprintf("B: Successfully freed memory in %s\n", prptr->prname);
        restore(mask);
	}

    /* All frames in E1 must be free */
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1) {
            intmask mask = disable();
            kprintf("B: Frame %d in E1 not free!\n", i);
            restore(mask);
        }
    }

    for(i = 0; i < NFRAMES_E2; i++) {
        if(fHolderListE2[i].frame_pres == 1) {
            intmask mask = disable();
            kprintf("B: Frame %d in E2 not free!\n", i);
            restore(mask);
        }
    } 

    /* Only frames corresponding to page directory and page tables should be used */
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1) {
            intmask mask = disable();
            kprintf("B: Frame %d in D not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
            restore(mask);
        }
    }
}

void test_swapping_procX()
{
    struct procent* prptr;
    uint16 num_pages_allocated = 512;

    // Allocate 512 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint16 i, j;

    prptr = &proctab[currpid];
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1(currpid);

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }


    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("X: page1:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    // Check size of E1 and E2
    num_frames_allocated_E1 = get_number_allocated_frames_E1(currpid);
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2(currpid);
    kprintf("X: E1, E2 size: %d, %d\n", num_frames_allocated_E1, num_frames_allocated_E2);


    // Check if fHolderListE1[older_frame_index] has correct entries - start of E1
    uint32 oldest_frame_index_E1 = get_index_oldest_frame_regionE1();
    display_E1_oldest_frame_details(oldest_frame_index_E1, currpid);

    // Allocate another page n VF
    int* ptr2 = (int* )vmhgetmem(1);
    if((int)ptr2 == SYSERR) {
        kprintf("X: Failed to allocate virtual mem!\n");
        return;
    }
    for(i = 0 ; i < NBPG/4; i++) {
        ptr2[i] =  513;
    }

    for(i = 0; i < NBPG/4; i++) {
        kprintf("X: page513:%d\t", ptr2[i]);
        break;
    }
    kprintf("\n");

    display_E1_oldest_frame_details(oldest_frame_index_E1, currpid);

    int ret = vmhfreemem((char*) ptr, num_pages_allocated);
	if(ret == OK) {
        intmask mask = disable();
		kprintf("X: Successfully freed memory in %s\n", prptr->prname);
        restore(mask);
	}

    ret = vmhfreemem((char*) ptr2, 1);
	if(ret == OK) {
        intmask mask = disable();
		kprintf("X: Successfully freed memory in %s\n", prptr->prname);
        restore(mask);
	}

    /* All frames in E1 must be free */
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 1  && fHolderListE1[i].owner_process == currpid) {
            intmask mask = disable();
            kprintf("X: Frame %d in E1 not free!\n", i);
            restore(mask);
        }
    }

    for(i = 0; i < NFRAMES_E2; i++) {
        if(fHolderListE2[i].frame_pres == 1  && fHolderListE2[i].owner_process == currpid) {
            intmask mask = disable();
            kprintf("X: Frame %d in E2 not free!\n", i);
            restore(mask);
        }
    } 

    /* Only frames corresponding to page directory and page tables should be used */
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 1 && fHolderListD[i].owner_process == currpid) {
            intmask mask = disable();
            kprintf("X: Frame %d in D not free. owner process: %d!\n", i, fHolderListD[i].owner_process);
            restore(mask);
        }
    }
}

void test_swapping(int test_num)
{
    if(test_num == 1) {
        /* E1 becomes full and memory is not allocated in E1. A new page allocated in VF (when E1 is full) results in page eviction 
            from E1 to E2 and allocation of page in E1. New page is allocated for the same process for which frame from E1 is evicted */
        resume (create((void *)test_swapping_procA, INITSTK, INITPRIO + 1, "procA process", 0, NULL));
        resume (create((void *)test_swapping_procB, INITSTK, INITPRIO, "procB process", 0, NULL));
    }

    if(test_num == 2) {
        /* E1 becomes full and memory is not allocated in E1. E2 is also full and process goes into state PR_FRAME */
    }

    if(test_num == 3) {
        /* Access a frame in E2 when E1 is full */
    }

    if(test_num == 4) {
        /* Access a frame in E2 when E1 and E2 are full */
    }

    if(test_num == 5) {
        /* E1 becomes full and memory is not allocated in E1. A new page allocated in VF (when E1 is full) results in page eviction 
            from E1 to E2 and allocation of page in E1. New page is allocated for a different process for which frame from E1 is evicted */
        resume (create((void *)test_swapping_procB, INITSTK, INITPRIO + 1, "procB process", 0, NULL));
        resume (create((void *)test_swapping_procX, INITSTK, INITPRIO, "procX process", 0, NULL));
    }
    

}