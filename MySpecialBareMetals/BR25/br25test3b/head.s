	.section .text.startup
	.global _start

_start:
	/* set stack pointer */
	sp = __sp

	/* store caller arguments */
	[--sp] = {r3-r0}

	/* copy data */
	r0 = _sdata
	r1 = _ldata
	r2 = _edata
	r2 = r2 - r0
	call memcpy

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
