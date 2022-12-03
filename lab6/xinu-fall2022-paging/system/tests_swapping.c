#include <xinu.h>


void test_swapping_procA()
{
    uint32 num_pages_allocated = 512;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

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

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("Num allocated frames in E1: %d\n", num_frames_allocated_E1);

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
    uint32 oldest_frame_index_E1 = 2024 * NBPG;
    kprintf("fHolderListE1[oldest_frame_index_E1].vaddr: %d\n", fHolderListE1[oldest_frame_index_E1].vaddr);

}


void test_swapping_procB()
{
    uint32 num_pages_allocated = 512;

    // Allocate 512 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    // for(i = 0; i < NBPG/4; i++) {
    //     kprintf("B: page1:%d\t", ptr[i]);
    // }
    // kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("B: page511:%d\t", ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    sleep(10);
}



void test_swapping_procC()
{
    uint32 num_pages_allocated = 1024;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("C: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("C: page1023:%d\t", ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("C: Num allocated frames in E1: %d\n", num_frames_allocated_E1);


    // Check size of E2
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2();
    kprintf("C: Num allocated frames in E2: %d\n", num_frames_allocated_E2);

    sleep(7);
    display_proctab();

    kprintf("\n#####\n");

}


void test_swapping_procD()
{
    uint32 num_pages_allocated = 1024;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("D: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("D: page1023:%d\t", ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("D: Num allocated frames in E1: %d\n", num_frames_allocated_E1);

    // Check size of E2
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2();
    kprintf("D: Num allocated frames in E2: %d\n", num_frames_allocated_E2);

    sleep(7);
    display_proctab();

    kprintf("\n#####\n");
}


void test_swapping_procE()
{
    // Allocate another page n VF
    int* ptr2 = (int* )vmhgetmem(100);
    if((int)ptr2 == SYSERR) {
        kprintf("Failed to allocate virtual mem!\n");
        return;
    }
    uint32 i;

    
    for(i = 0 ; i < (NBPG/4) * 100; i++) {
        ptr2[i] =  1;
    }

    for(i = 0; i < NBPG/4; i++) {
        kprintf("E: page1:%d\t", ptr2[i]);
        break;
    }
    kprintf("\n");

    kprintf("\n#####\n");
}

void test_swapping_procF()
{
    uint32 num_pages_allocated = 1024;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("F: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("F: page1023:%d\t", ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("F: Num allocated frames in E1: %d\n", num_frames_allocated_E1);


    // Check size of E2
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2();
    kprintf("F: Num allocated frames in E2: %d\n", num_frames_allocated_E2);

    sleep(7);
    

    kprintf("\n#####\n");

    // Print content of oldest page
    for(i = 0; i < 5; i++) {
        kprintf("F: page0:%d\t", ptr[i]);
    }
    kprintf("\n");

    // Check for single frame owned by this process in E1
    p32addr_t frame_paddr = 0;
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].owner_process == currpid) {
            frame_paddr = (i + REGIONSTART_E1) * NBPG ;
            break;
        }
    }

    kprintf("frame_paddr: %d\n", frame_paddr);

}


void test_swapping_procG()
{
    uint32 num_pages_allocated = 1024;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("G: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("G: page1047:%d\t", ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("G: Num allocated frames in E1: %d\n", num_frames_allocated_E1);

    // Check size of E2
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2();
    kprintf("G: Num allocated frames in E2: %d\n", num_frames_allocated_E2);

    sleep(10);

    kprintf("\n#####\n");
}



void test_swapping_procH()
{
    uint32 num_pages_allocated = 1024;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("H: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("H: page1023:%d\t", ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("H: Num allocated frames in E1: %d\n", num_frames_allocated_E1);


    // Check size of E2
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2();
    kprintf("H: Num allocated frames in E2: %d\n", num_frames_allocated_E2);

    sleep(10);
    
    kprintf("\n#####\n");
    display_proctab();

    // Print content of oldest page
    for(i = (1024 * 500); i < (1024 * 500) + 5; i++) {
        kprintf("H: page%d:%d\t",i/1024, ptr[i]);
    }

    for(i = (1024 * 600); i < (1024 * 600) + 5; i++) {
        kprintf("H: page%d:%d\t",i/1024, ptr[i]);
    }
    kprintf("\n");

}


void test_swapping_procI()
{
    uint32 num_pages_allocated = 1024;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("I: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("I: page1047:%d\t", ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("I: Num allocated frames in E1: %d\n", num_frames_allocated_E1);

    // Check size of E2
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2();
    kprintf("I: Num allocated frames in E2: %d\n", num_frames_allocated_E2);

    kprintf("\n#####\n");
}



void test_swapping_procJ()
{
    uint32 num_pages_allocated = 1024;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("J: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("J: page%d:%d\t",i/1024, ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("H: Num allocated frames in E1: %d\n", num_frames_allocated_E1);


    // Check size of E2
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2();
    kprintf("H: Num allocated frames in E2: %d\n", num_frames_allocated_E2);

    sleep(7);
    
    kprintf("\n#####\n");
    display_proctab();

    // Print content of oldest page
    for(i = (1024 * 500); i < (1024 * 500) + 5; i++) {
        kprintf("H: page%d:%d\t",i/1024, ptr[i]);
    }

    for(i = (1024 * 600); i < (1024 * 600) + 5; i++) {
        kprintf("H: page%d:%d\t",i/1024, ptr[i]);
    }
    kprintf("\n");

}


void test_swapping_procK()
{
    uint32 num_pages_allocated = 1024;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("K: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("K: page%d:%d\t",i/1024, ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("K: Num allocated frames in E1: %d\n", num_frames_allocated_E1);

    // Check size of E2
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2();
    kprintf("K: Num allocated frames in E2: %d\n", num_frames_allocated_E2);

    kprintf("\n#####\n");

    sleep(7);
}


void test_swapping_procL()
{
    uint32 num_pages_allocated = 24;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint32 i, j;

    // Make E1 full
    for(i = 0; i < num_pages_allocated; i++) {
        for(j = 0; j < NBPG/4; j++) {
            ptr[(i*NBPG)/4 + j] = i;
        }
    }

    // Print content of oldest page
    for(i = 0; i < NBPG/4; i++) {
        kprintf("L: page0:%d\t", ptr[i]);
        break;
    }
    kprintf("\n");

    for(i = 0; i < NBPG/4; i++) {
        kprintf("L: page%d:%d\t",i/1024, ptr[((num_pages_allocated - 1)*NBPG)/4 + i]);
        break;
    }
    kprintf("\n");

    // Check size of E1
    uint32 num_frames_allocated_E1 = get_number_allocated_frames_E1();
    kprintf("K: Num allocated frames in E1: %d\n", num_frames_allocated_E1);

    // Check size of E2
    uint32 num_frames_allocated_E2 = get_number_allocated_frames_E2();
    kprintf("K: Num allocated frames in E2: %d\n", num_frames_allocated_E2);

    kprintf("\n#####\n");

    sleep(7);
}



void test_swapping(int test_num)
{
    if(test_num == 1) {
        /* E1 becomes full and memory is not allocated in E1. A new page allocated in VF (when E1 is full) results in page eviction 
            from E1 to E2 and allocation of page in E1 */
        resume (create((void *)test_swapping_procA, INITSTK, INITPRIO + 1, "procA", 0, NULL));
        resume (create((void *)test_swapping_procB, INITSTK, INITPRIO, "procB", 0, NULL));
    }

    if(test_num == 2) {
        /* E1 becomes full and memory is not allocated in E1. E2 is also full and process goes into state PR_FRAME */
        resume (create((void *)test_swapping_procC, INITSTK, INITPRIO + 2, "procC", 0, NULL));
        resume (create((void *)test_swapping_procD, INITSTK, INITPRIO + 1, "procD", 0, NULL));
        resume (create((void *)test_swapping_procE, INITSTK, INITPRIO, "procE", 0, NULL));
    }

    if(test_num == 3) {
        /* Access a frame in E2 when E1 is full */
        resume (create((void *)test_swapping_procF, INITSTK, INITPRIO + 2, "procF", 0, NULL));
        resume (create((void *)test_swapping_procG, INITSTK, INITPRIO + 1, "procG", 0, NULL));
    }

    if(test_num == 4) {
        /* Access a frame in E2 when E1 and E2 are full */
        resume (create((void *)test_swapping_procJ, INITSTK, INITPRIO + 2, "procJ", 0, NULL));
        resume (create((void *)test_swapping_procK, INITSTK, INITPRIO + 1, "procK", 0, NULL));
        resume (create((void *)test_swapping_procL, INITSTK, INITPRIO, "procL", 0, NULL));
    }

    if(test_num == 5) {
        /* Access a frame in E2 when E1 and E2 are full */
    }

    if(test_num == 6) {
        // E1 is free (bring frame from E2 to E1)
        resume (create((void *)test_swapping_procH, INITSTK, INITPRIO + 2, "procH", 0, NULL));
        resume (create((void *)test_swapping_procI, INITSTK, INITPRIO + 1, "procI", 0, NULL));
    }


}