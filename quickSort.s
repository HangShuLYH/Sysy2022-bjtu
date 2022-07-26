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
	bl defn
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	add sp,sp, #4
	pop {pc}
defn:
	push {lr}
	sub sp,sp,#0
.L2:
	mov r0,#4
	add sp,sp, #0
	pop {pc}
