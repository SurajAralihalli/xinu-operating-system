/* helper_functions_swapping.c */

#include <xinu.h>


/*------------------------------------------------------------------------
 * get_index_oldest_frame_regionE1  -  returns the oldest frame in E1 (FIFO)
 *------------------------------------------------------------------------
 */


int get_index_oldest_frame_regionE1()
{
    int32 i;
    int oldest_index;
    uint32 smallest_counter = 0xFFFFFFFF;
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE1[i].frame_pres != 0) {
            if(fHolderListE1[i].time_counter < smallest_counter)
            {
                smallest_counter = fHolderListE1[i].time_counter;
                oldest_index = i;
            }
        }
    }

    return oldest_index;
}


/*------------------------------------------------------------------------
 * get_matching_frame_from_regionE2  -  returns the index of the frame in E2 which was swapped from E1 if exists else returns -1
 *------------------------------------------------------------------------
 */
int get_matching_frame_from_regionE2(v32addr_t vaddr)
{
    int index = -1;
    int32 i;
    for(i = 0; i < NFRAMES_E2; i++) {
        if(fHolderListE2[i].frame_pres != 0 
            && fHolderListE2[i].owner_process == currpid 
            && fHolderListE2[i].vaddr == vaddr) 
        {
            index = i;
        }
    }

    return index;
}


/*------------------------------------------------------------------------
 * free_frame_in_regionE2 -  Update fHolderListE1 to reuse frames
 *------------------------------------------------------------------------
 */
void free_frame_in_regionE2(v32addr_t vaddr, pid32 owner_pid)
{
    vaddr = drop_offset_from_addr(vaddr);
    uint32 i;
    for(i = 0; i < NFRAMES_E2; i++) {
        if(fHolderListE2[i].vaddr == vaddr && fHolderListE2[i].owner_process == owner_pid) {
            fHolderListE2[i].frame_pres = 0;
            fHolderListE2[i].owner_process = -1;
            fHolderListE2[i].vaddr = 0x0;
            break;
        }
    }
}


/*------------------------------------------------------------------------
 * get_empty_frame_from_regionE2 -  Return absolute address of empty frame from region E2
 *------------------------------------------------------------------------
 */
char* get_empty_frame_from_regionE2(v32addr_t vaddr, pid32 pid)
{
    uint32 absolute_addr = 0;
    int32 i;
    for(i = 0; i < NFRAMES_E1; i++) {
        if(fHolderListE2[i].frame_pres == 0) {
            fHolderListE2[i].frame_pres = 1;
            fHolderListE2[i].owner_process = pid;
            fHolderListE2[i].vaddr = vaddr;
            absolute_addr = (i + REGIONSTART_E2) * NBPG; // REGIONSTART_E2 is starting frame in E2

            return (char*) absolute_addr;  
        }
    }
    return (char*) SYSERR;
}