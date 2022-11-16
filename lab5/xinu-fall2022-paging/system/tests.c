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
}