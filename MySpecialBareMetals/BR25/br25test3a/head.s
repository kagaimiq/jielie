	.section .text.startup
	.global _start

_start:
	/* store caller arguments */
	[--sp] = {r3-r0}

	/* clear bss */
	r0 = _sbss
	r1 = 0
	r2 = _ebss
	r2 = r2 - r0
	call memset

	/* restore caller arguments */
	{r3-r0} = [sp++]

	/* call main */
	call JieLi

	/* halt */
1:	idle
	goto	1b
