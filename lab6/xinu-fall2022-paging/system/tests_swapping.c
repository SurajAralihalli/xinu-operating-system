#include <xinu.h>


void test_swapping_procA()
{
    uint16 num_pages_allocated = 512;

    // Allocate 1024 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint16 i, j;

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
    uint16 num_pages_allocated = 512;

    // Allocate 512 pages
    int* ptr = (int* )vmhgetmem(num_pages_allocated);
    uint16 i, j;

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

void test_swapping(int test_num)
{
    if(test_num == 1) {
        /* E1 becomes full and memory is not allocated in E1. A new page allocated in VF (when E1 is full) results in page eviction 
            from E1 to E2 and allocation of page in E1 */
        resume (create((void *)test_swapping_procA, INITSTK, INITPRIO + 1, "test_swapping_procA process", 0, NULL));
        resume (create((void *)test_swapping_procB, INITSTK, INITPRIO, "test_swapping_procB process", 0, NULL));
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

}