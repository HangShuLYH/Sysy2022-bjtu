.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {lr}
	sub sp,sp,#4
	bl .init
.L1:
	mov r0,#10
	str r0,[sp,#0]
	ldr r2,[sp,#0]
	mov r1,#3
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	add sp,sp, #4
	pop {pc}
