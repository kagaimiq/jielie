	.section .text.startup
	.global _start
_start:
	/* save caller's regs */
	push {rets, r14-r4}
	pushs {macch, maccl}

	/* set SP, and preserve caller's one */
	mov r4, sp
	movl sp, __usp
	movh sp, __usp
	push {r4}

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

	/* restore caller's SP */
	pop {r4}
	mov sp, r4

	/* restroe caller's regs and finally return */
	pops {macch,maccl}
	pop {pc, r14-r4}

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
