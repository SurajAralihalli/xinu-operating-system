/* pgfhandler.c - pgfhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * pgfhandler - high level page fault interrupt handler
 *------------------------------------------------------------------------
 */
void	pgfhandler()
{
    struct	procent	*prptr = &proctab[currpid];

    v32addr_t page_faulted_addr = get_page_faulted_addr_cr2();

    // find page directory entry
    p32addr_t* page_dir_addr = (p32addr_t*)prptr->page_dir_addr;
    uint32 page_dir_index = page_faulted_addr >> 22;
    pd_t* page_dir_entry = &(page_dir_addr[page_dir_index]);

    // check if page table is present
    if(page_dir_entry->pd_pres==0)
    {
        //build a page table
        p32addr_t page_table_addr = get_empty_frame_from_regionD();

        //Initialize page table
		initialize_empty_page_table(page_table_addr);

        //set pres bit to 1 and make page dir entry point to new page table
        set_page_directory_entry(page_dir_entry, (p32addr_t)page_table_addr);

    }

    // find page table entry
    p32addr_t* page_table_addr = (page_dir_entry->pd_base)<<12;  //base + "000000000000"
    uint32 page_table_index = (page_faulted_addr & 0x003FF000) >> 12; //page table index + page index + offset
    pt_t* page_table_entry =  &(page_table_addr[page_table_index]);

    // check if page is present
    if(page_table_entry->pt_pres==0)
    {
        //build a page
        p32addr_t page_addr = get_empty_frame_from_regionE1();

        //set pres bit to 1 and make page table entry point to new page
        set_page_table_entry(page_table_entry, (p32addr_t)page_addr);
    }
}
