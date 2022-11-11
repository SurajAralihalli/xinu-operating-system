/* init_paging.c */

#include <xinu.h>

/*------------------------------------------------------------------------
 * init_paging  -  set up kernel data structure to manage per process heaps in virtual memory
                   set up page fault handler for intr 14
                   update context switch to account for richer process context
 *------------------------------------------------------------------------
 */


void init_paging(void)
{

    /* Create page directory */
	pg_dir_t* page_dir_addr = (pg_dir_t*) get_empty_frame_from_regionD();

	/* Initialize page directory */
	initialize_empty_page_directory((pg_dir_t*) page_dir_addr);

	/* Create shared page tables for regions A-E, G*/
	uint32 pg_dir_indices[5] = {0, 1, 2, 3, 576};
	uint32 i;
	for(i = 0; i < 5; i++) {
		pg_tab_t* page_table_addr = (pg_tab_t*) get_empty_frame_from_regionD();
		
		/* Initialize page table */
		initialize_empty_page_table(page_table_addr);

		uint32 pg_dir_index = pg_dir_indices[i];

		pd_t* page_dir_entry = &(page_dir_addr[pg_dir_index]);

		set_page_directory_entry(page_dir_entry, ((uint32)page_table_addr) >> 12);

		uint32 base_addr = (uint32) page_dir_entry->pd_base;
		
		kprintf("%d page dir entry, page table addr: %d\n", pg_dir_index, page_table_addr);

		kprintf("%d page dir entry addr: %d: %d\n", pg_dir_index, base_addr, ((uint32) page_table_addr) >> 12);

		identity_map(page_table_addr, pg_dir_index);

		kprintf("Identity map for %d successful: %d\n", pg_dir_index, page_dir_entry->pd_pres);

		/* Save identity mapped page tables  */
		identityMapAddrList[i].pg_tab_addr = ((uint32) page_table_addr) >> 12;
		identityMapAddrList[i].pg_dir_index = pg_dir_index;
	}

	int a=0;

	/* Update CR3 to setup null process page directory address */
	uint32 cr3_val = 0;
	asm("movl %%cr3, %0" 
		: "=r"(cr3_val));
	cr3_val = (cr3_val & 0x00000FFF) | ((uint32)page_dir_addr & 0xFFFFF000);
	asm("movl %0, %%cr3" 
		:
		: "r"(cr3_val));


	/* Enable paging - Set PG bit of CR0 to 1 */
	uint32 cr0_val = 0;
	asm("movl %%cr0, %0" 
		: "=r"(cr0_val));
	uint32 cr0_val_pristine = cr0_val;
	cr0_val = cr0_val | 1 << 31;
	asm("movl %0, %%cr0" 
		:
		: "r"(cr0_val));

    // Setup page fault handler
	set_evec(14, (uint32)pgfdisp);
}