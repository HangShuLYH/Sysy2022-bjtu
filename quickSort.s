.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {lr}
	sub sp,sp,#0
	bl .init
.L1:
	bl ififElse
	add sp,sp, #0
	pop {pc}
ififElse:
	push {lr}
	sub sp,sp,#8
.L2:
	mov r0,#5
	str r0,[sp,#0]
	mov r0,#10
	str r0,[sp,#4]
	ldr r1,[sp,#0]
	mov r0,#5
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#1
	beq .L3
	bne .L4
.L3:
	ldr r1,[sp,#4]
	mov r0,#10
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#1
	beq .L4
	bne .L4
.L4:
	ldr r0,[sp,#0]
	add sp,sp, #8
	pop {pc}
