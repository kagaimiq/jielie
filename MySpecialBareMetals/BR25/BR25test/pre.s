	.section .text.startup
	.global _start
_start:
	// save return address and caller regs
	[--sp] = {rets, r15-r4}

	// save caller arguments
	[--sp] = {r3-r0}

	// clear bss
	r0 = _sbss
	r1 = 0
	r2 = _ebss
	r2 = r2 - r0
	call memset

	// restore caller arguments
	{r3-r0} = [sp++]

	// call main
	call JieLi

	// restore caller regs and return
	{pc, r15-r4} = [sp++]


	.global ExceptionHandler_entry
ExceptionHandler_entry:
	// store all the regs - make an exception frame
	[--sp] = {pc, sp, ssp, usp, icfg, sr10, sr9, sr8, sr7, cnum, psr, sr4, rets, retx, rete, reti}
	[--sp] = {r15-r0}

	// pass the pointer to the exception frame
	r0 = sp

	// call the function
	call ExceptionHandler

	// halt
1:	idle
	goto 1b

