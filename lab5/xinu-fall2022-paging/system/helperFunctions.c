/* helperFunctions.c */

#include <xinu.h>

/*------------------------------------------------------------------------
 * helperFunctions  -  Helper Functions
 *------------------------------------------------------------------------
 */



/*------------------------------------------------------------------------
TODO:

1. Page Directory (Array of structs): 1024 (default: NULL)
2. Page Table (Array of structs): 1024 (creation on demand)

3. In regions F
Pages or Vframes: To maintain which pages are vacant for use
free list
Used by: vmhgetmem, vmhfreemem

4. In regions D and E1
Frames: To maintain which frame are vacant for use
Used by: page fault handler




 *------------------------------------------------------------------------
 */

/*------------------------------------------------------------------------
 * get_empty_frame_from_regionD  -  Return absolute address of empty frame from region D
 *------------------------------------------------------------------------
 */
char* get_empty_frame_from_regionD()
{
    uint32 absolute_addr;
    int32 i;
    for(i = 0; i < NFRAMES_D; i++) {
        if(fHolderListD[i].frame_pres == 0) {
            fHolderListD[i].frame_pres = 1;
            fHolderListD[i].owner_process = currpid;
            absolute_addr = (i + FRAME0) * NBPG;
            break;
        }
    }
    return (char*) absolute_addr;   
}


/*------------------------------------------------------------------------
 * get_empty_frame_from_regionE1 -  Return absolute address of empty frame from region E1
 *------------------------------------------------------------------------
 */
char* get_empty_frame_from_regionE1()
{
    uint32 absolute_addr;
    int32 i;
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres == 0) {
            fHolderListE1[i].frame_pres = 1;
            fHolderListE1[i].owner_process = currpid;
            absolute_addr = (i + FRAME0) * NBPG;
            break;
        }
    }
    return (char*) absolute_addr;  
}

/*------------------------------------------------------------------------
 * initialize_empty_page_directory -  Initialize page directory entries to default values
 *------------------------------------------------------------------------
 */
void initialize_empty_page_directory(pg_dir_t* page_dir_addr)
{
    uint32 i;
	for(i = 0; i < ENTRIES_PER_FRAME; i++) {
        pd_t* page_dir_entry = &(page_dir_addr[i]);
		page_dir_entry->pd_pres = 0;  	/* page table present?		*/
        page_dir_entry->pd_write =1;			/* page is writable?		*/
        page_dir_entry->pd_user= 0;		/* is use level protection?	*/
        page_dir_entry->pd_pwt	=0;		/* write through cachine for pt?*/
        page_dir_entry->pd_pcd	=0;		/* cache disable for this pt?	*/
        page_dir_entry->pd_acc	=0;		/* page table was accessed?	*/
        page_dir_entry->pd_mbz	=0;		/* must be zero			*/
        page_dir_entry->pd_fmb	=0;		/* four MB pages?		*/
        page_dir_entry->pd_global=1;		/* global (ignored)		*/
        page_dir_entry->pd_avail =0;		/* for programmer's use		*/
        page_dir_entry->pd_base	=0;	    /* location of page table?	*/
	}
}

/*------------------------------------------------------------------------
 * initialize_empty_page_table -  Initialize page table entries to default values
 *------------------------------------------------------------------------
 */
void initialize_empty_page_table(pg_tab_t* page_table_addr)
{
    int32 i;
	for(i = 0; i < ENTRIES_PER_FRAME; i++) {
        pt_t* page_table_entry = &(page_table_addr[i]);
        page_table_entry->pt_pres	= 0;		/* page is present?		*/
        page_table_entry->pt_write = 0;		/* page is writable?		*/
        page_table_entry->pt_user	= 0;		/* is use level protection?	*/
        page_table_entry->pt_pwt	= 0;		/* write through for this page? */
        page_table_entry->pt_pcd	= 0;		/* cache disable for this page? */
        page_table_entry->pt_acc	= 0;		/* page was accessed?		*/
        page_table_entry->pt_dirty = 0;		/* page was written?		*/
        page_table_entry->pt_mbz	= 0;		/* must be zero			*/
        page_table_entry->pt_global= 0;		/* should be zero in 586	*/
        page_table_entry->pt_avail = 0;		/* for programmer's use		*/
        page_table_entry->pt_base	= 0;		/* location of page?		*/
	}
}

/*------------------------------------------------------------------------
 * identity_map -  Perform identity mapping of entries in page table with
                    start address `page_tab_addr`. Mapping is performed for
                    page directory entry corresponding to `page_dir_index`
                    of the null process
 *------------------------------------------------------------------------
 */
void identity_map(pg_tab_t* page_table_addr, uint32 page_dir_index)
{
    uint32 i;
    for(i = 0 ; i < ENTRIES_PER_FRAME; i++) {
        pt_t* page_tab_entry = &(page_table_addr[i]);
        page_tab_entry->pt_pres = 1;
        page_tab_entry->pt_write = 1;		/* page is writable?		*/
        page_tab_entry->pt_user = 0;		/* is use level protection?	*/
        page_tab_entry->pt_pwt	= 0;		/* write through for this page? */
        page_tab_entry->pt_pcd	= 0;		/* cache disable for this page? */
        page_tab_entry->pt_acc	= 0;		/* page was accessed?		*/
        page_tab_entry->pt_dirty = 0;		/* page was written?		*/
        page_tab_entry->pt_mbz	= 0;		/* must be zero			*/
        page_tab_entry->pt_global= 0;		/* should be zero in 586	*/
        page_tab_entry->pt_avail = 0;		/* for programmer's use		*/
        page_tab_entry->pt_base = i | (page_dir_index << 10);		/* location of page?		*/


    }
}

/*------------------------------------------------------------------------
 * set_page_directory_entry -  Set P bit  and page table frame number 
                            of page directory entry
 *------------------------------------------------------------------------
 */
void set_page_directory_entry(pd_t* page_dir_entry, p32addr_t page_table_addr)
{
    
    /* Mark present bit to 1 */
    page_dir_entry->pd_pres = 1;

    /* Assign page table address to page directory entry */
    page_dir_entry->pd_base = ((p32addr_t)page_table_addr) >> 12;
}