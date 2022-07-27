.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
.L1:
	push {lr}
	sub sp,sp, #0
	bl .init
	mov r0,#3
	add sp,sp, #0
	pop {pc}
