/* pgfhandler.c - pgfhandler */

#include <xinu.h>

/*------------------------------------------------------------------------
 * pgfhandler - high level page fault interrupt handler
 *------------------------------------------------------------------------
 */
void	pgfhandler()
{
    struct	procent	*prptr = &proctab[currpid];
    v32addr_t page_faulted_addr;

    // find page directory entry
    pg_dir_t* page_dir_addr = prptr->page_dir_addr;
    uint32 page_dir_index = page_faulted_addr >> 22;
    pd_t* page_dir_entry = &(page_dir_addr[page_dir_index]);

    // check if page table is present
    if(page_dir_entry->pd_pres==0)
    {
        //build a page table
        pg_tab_t* page_table_addr = (pg_tab_t*) get_empty_frame_from_regionD();

        //Initialize page table
		initialize_empty_page_table(page_table_addr);

        //set pres bit to 1 and make page dir entry point to new page table
        set_page_directory_entry(page_dir_entry, (p32addr_t)page_table_addr);

    }

    // find page table entry
    pg_tab_t* page_table_addr = (page_dir_entry->pd_base)<<12;
    uint32 page_table_index = (page_faulted_addr & 0x003FF000) >> 12;
    pt_t* page_table_entry =  &(page_table_addr[page_table_index]);

    // check if page is present
    if(page_table_entry->pt_pres==0)
    {
        //build a page
    }
    

}
