.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {lr}
	sub sp,sp,#8
	bl .init
.L1:
	mov r0,#0
	str r0,[sp,#0]
	mov r0,#0
	str r0,[sp,#4]
	b .L2
.L2:
	ldr r1,[sp,#0]
	mov r0,#100
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#1
	beq .L3
	bne .L6
.L3:
	ldr r1,[sp,#0]
	mov r0,#50
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#1
	beq .L4
	bne .L5
.L4:
	b .L5
.L5:
	ldr r1,[sp,#4]
	ldr r0,[sp,#0]
	add r0,r1,r0
	str r0,[sp,#4]
	ldr r1,[sp,#0]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#0]
	b .L2
.L6:
	ldr r0,[sp,#4]
	add sp,sp, #8
	pop {pc}
