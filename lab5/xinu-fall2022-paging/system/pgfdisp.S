/* pgfdisp.s - pgfdisp (x86) */

/*------------------------------------------------------------------------
 * pgfdisp  -  Interrupt dispatcher for page faults
 *------------------------------------------------------------------------
 */


#include <icu.s>
		.text
		.globl	pgfdisp		# Page Fault interrupt dispatcher
pgfdisp:
    pushal			# Save registers
	cli				# Disable further interrupts
	# movb	$EOI,%al	# Reset interrupt
	# outb	%al,$OCW1_2

	call	pgfhandler	# Call high level handler

	sti			# Restore interrupt status
	popal			# Restore registers
	iret			# Return from interrupt