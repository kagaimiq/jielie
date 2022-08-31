	.section .text.startup
	.global _start
_start:
	/* set SP */
	movl sp, __usp
	movh sp, __usp

	/* save caller's arguments */
	push {r3-r0}

	/* Set exception handler */
	movl r4, _jl_exc_handler
	movh r4, _jl_exc_handler
	movz r5, 0x00 /* vector 0 */
	sw r4, r5

	/* clear bss */
	movl r0, _sbss
	movh r0, _sbss
	movz r1, 0
	movl r2, _ebss
	movh r2, _ebss
	sub r2, r2, r0
	call memset

	/* restore caller's arguments */
	pop {r3-r0}

	/* call main */
	call JieLi

	/* halt */
1:	idle
	j 1b

/*======================================================================*/

	.global _jl_exc_handler	
_jl_exc_handler:
	/* push all regs */
	push {r14-r0}
	pushs {usp,ssp}
	pushs {macch,maccl}
	pushs {icfg,ie0,ie1}
	pushs {rets,reti}
	pushs {pc,psr}

	/* pass the stack pointer as argument */
	mov r0, sp

	/* enter handler */
	call jl_exc_handler

	/* halt */
1:	j 1b
