/* pgfdisp.s - pgfdisp (x86) */

/*------------------------------------------------------------------------
 * pgfdisp  -  Interrupt dispatcher for page faults
 *------------------------------------------------------------------------
 */


#include <icu.s>
    	   .text
pferrcode: .long 0
           .globl  pgfdisp,pferrcode 
pgfdisp:
	popl     pferrcode
	pushal			# Save registers
	cli			# Disable further interrupts
	movb	$EOI,%al	# Reset interrupt
	outb	%al,$OCW1_2

	call	pgfhandler	# Call high level handler

	sti			# Restore interrupt status
	popal			# Restore registers
	#movl $0x1000004, %eax
	iret			# Return from interrupt