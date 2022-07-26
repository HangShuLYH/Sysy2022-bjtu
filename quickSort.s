.arch armv7ve
.arm
.section .bss
.align
n:
	.space 4
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {lr}
	sub sp,sp,#48
	bl .init
.L1:
	add r0,sp, #0
	bl bubblesort
	str r0,[sp,#40]
	b .L2
.L2:
	ldr r1,[sp,#40]
	movw r0,#:lower16:n
	movt r0,#:upper16:n
	ldr r0,[r0,#0]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L3
	beq .L4
.L3:
	ldr r1,[sp,#40]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #0
	mla r0,r1,r2,r0
	ldr r0,[r0,#0]
	str r0,[sp,#44]
	ldr r0,[sp,#44]
	bl putint
	mov r0,#10
	str r0,[sp,#44]
	ldr r0,[sp,#44]
	bl putch
	ldr r1,[sp,#40]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#40]
	b .L2
.L4:
	mov r0,#0
	add sp,sp, #48
	pop {pc}
bubblesort:
	push {lr}
	sub sp,sp,#4
.L5:
	str r0,[sp,#0]
	mov r0,#0
	add sp,sp, #4
	pop {pc}
