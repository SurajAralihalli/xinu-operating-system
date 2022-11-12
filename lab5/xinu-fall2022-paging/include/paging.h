/* paging.h */

//typedef unsigned int	 bsd_t;

/* Structure for a page directory entry */

typedef struct {

  unsigned int pd_pres	: 1;		/* page table present?		*/
  unsigned int pd_write : 1;		/* page is writable?		*/
  unsigned int pd_user	: 1;		/* is use level protection?	*/
  unsigned int pd_pwt	: 1;		/* write through cachine for pt?*/
  unsigned int pd_pcd	: 1;		/* cache disable for this pt?	*/
  unsigned int pd_acc	: 1;		/* page table was accessed?	*/
  unsigned int pd_mbz	: 1;		/* must be zero			*/
  unsigned int pd_fmb	: 1;		/* four MB pages?		*/
  unsigned int pd_global: 1;		/* global (ignored)		*/
  unsigned int pd_avail : 3;		/* for programmer's use		*/
  unsigned int pd_base	: 20;		/* location of page table?	*/
} pd_t;

/* Structure for a page table entry */

typedef struct {

  unsigned int pt_pres	: 1;		/* page is present?		*/
  unsigned int pt_write : 1;		/* page is writable?		*/
  unsigned int pt_user	: 1;		/* is use level protection?	*/
  unsigned int pt_pwt	: 1;		/* write through for this page? */
  unsigned int pt_pcd	: 1;		/* cache disable for this page? */
  unsigned int pt_acc	: 1;		/* page was accessed?		*/
  unsigned int pt_dirty : 1;		/* page was written?		*/
  unsigned int pt_mbz	: 1;		/* must be zero			*/
  unsigned int pt_global: 1;		/* should be zero in 586	*/
  unsigned int pt_avail : 3;		/* for programmer's use		*/
  unsigned int pt_base	: 20;		/* location of page?		*/
} pt_t;


/* Prototypes for required API calls */
//SYSCALL xmmap(int, bsd_t, int);
//SYSCALL xmunmap(int);

#define NBPG		4096	/* number of bytes per page	*/
#define FRAME0		1024	/* zero-th frame		*/
#define NFRAMES		3072	/* number of frames		*/

#define ENTRIES_PER_FRAME 1024

#define MAP_SHARED 1
#define MAP_PRIVATE 2

#define FIFO 3
#define MYPOLICY 4

#define MAX_ID		7		/* You get 8 mappings, 0 - 7 */
#define MIN_ID          0



#define NFRAMES_D		1000	/* number of frames		*/
#define NFRAMES_E1		1024

// NEW DATASTRUCTURES // 

typedef uint32 pg_dir_t;
typedef uint32 pg_tab_t;

typedef uint32 v32addr_t;
typedef uint32 p32addr_t;

// struct to indicate which frames are free
struct fholder{
  unsigned int frame_pres	: 1;		/* frame is present?		*/
  pid32  owner_process;
};

extern	struct	fholder fHolderListD[];
extern	struct	fholder fHolderListE1[];

struct identityMapAddr {
  pg_tab_t* page_table_addr;
  uint32   page_dir_index;
};

extern struct identityMapAddr identityMapAddrList[]; 
