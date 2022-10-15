/* createtsx.c - create */

#include <xinu.h>

/*------------------------------------------------------------------------
 *  create  -  Create a process to start running a function on x86
 *------------------------------------------------------------------------
 */

// pid32	createtsx(
// 	  void		*funcaddr,	/* Address of the function	*/
// 	  uint32	ssize,		/* Stack size in bytes		*/
// 	//   pri16		priority,	/* Process priority > 0		*/
// 	  char		*name,		/* Name (for debugging)		*/
// 	  uint32	nargs,		/* Number of args that follow	*/
// 	  ...
// 	)
// {
// 	return create(funcaddr, ssize, TSXINIT, name, nargs, ...);
// }
