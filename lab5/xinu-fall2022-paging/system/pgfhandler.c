/* pgfhandler.c - pgfhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * pgfhandler - high level page fault interrupt handler
 *------------------------------------------------------------------------
 */
void	pgfhandler()
{
    unsigned long* ebp = NULL;
    int status;

    struct	procent	*prptr = &proctab[currpid];

    v32addr_t page_faulted_addr = get_page_faulted_addr_cr2();


    /* Check if page fault corresponds to unallocated memory */
    status = is_addr_allocated_by_vmhgetmem(page_faulted_addr);
    if(status == 0) { //status is false
        /* Terminate process */
        kill(currpid);
    }

    page_faulted_addr = drop_offset_from_addr(page_faulted_addr);

    pd_t* page_dir_entry = get_page_directory_entry(page_faulted_addr, (p32addr_t*)prptr->page_dir_addr);

    // check if page table is present
    if(page_dir_entry->pd_pres==0)
    {
        // build a page table
        int32 page_table_addr_raw = (int32) get_empty_frame_from_regionD(currpid);
        if(page_table_addr_raw == SYSERR) {
            return; // TODO: What to do? Process will continue to page fault
        }

        p32addr_t* page_table_addr = (p32addr_t*) page_table_addr_raw;

        // Initialize page table
		initialize_empty_page_table(page_table_addr);

        // Set pres bit to 1 and make page dir entry point to new page table
        set_page_directory_entry(page_dir_entry, (p32addr_t)page_table_addr);

    }

    pt_t* page_table_entry = get_page_table_entry(page_faulted_addr, page_dir_entry);

    p32addr_t* page_table_addr = (p32addr_t*) (page_dir_entry->pd_base << 12);

    //check if page is present
    if(page_table_entry->pt_pres==0)
    {
        // Build a page
        p32addr_t* page_addr = (p32addr_t*) get_empty_frame_from_regionE1(page_faulted_addr);

        // Translate page table address into index for fHolderListD
        uint16 index_fHolderListD = (p32addr_t)page_table_addr/NBPG - FRAME0;

        increment_number_entries_allocated(index_fHolderListD);

        //set pres bit to 1 and make page table entry point to new page
        set_page_table_entry(page_table_entry, (p32addr_t)page_addr);

        // kprintf("page addr: %x\n", page_addr);
    } else {
        
        /* Get error code */
        asm("movl %%ebp, %0;"
            :"=r"(ebp)
            );
        ebp += 10; // (ebp + ret + general purpose registers) + errorcode + return addr to page faulted instruction

        /* Check for access violation */
        status = is_read_write_access_violation(*ebp, page_table_entry);
        if(status == 1) {
            /* Terminate process */
            kill(currpid);
        }
    }

}
