.arch armv7ve
.arm
.section .bss
.align
a:
	.space 4
.global main
.section .text
.init:
.L0:
	mov r1,#7
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	str r1,[r0,#0]
	bx lr
main:
	push {lr}
	sub sp,sp,#8
	bl .init
.L1:
	mov r1,#0
	str r1,[sp,#0]
	mov r1,#0
	str r1,[sp,#4]
	b .L2
.L2:
	ldr r2,[sp,#4]
	mov r1,#100
	cmp r2,r1
	mov r1,#0
	movlt r1,#1
	cmp r1,#0
	bne .L3
	beq .L6
.L3:
	bl func
	mov r1,#1
	cmp r0,r1
	mov r1,#0
	moveq r1,#1
	cmp r1,#0
	bne .L4
	beq .L5
.L4:
	ldr r2,[sp,#0]
	mov r1,#1
	add r1,r2,r1
	str r1,[sp,#0]
	b .L5
.L5:
	ldr r2,[sp,#4]
	mov r1,#1
	add r1,r2,r1
	str r1,[sp,#4]
	b .L2
.L6:
	ldr r1,[sp,#0]
	mov r0,#100
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L7
	beq .L8
.L7:
	mov r0,#1
	bl putint
	b .L9
.L8:
	mov r0,#0
	bl putint
	b .L9
.L9:
	mov r0,#0
	add sp,sp, #8
	pop {pc}
func:
	push {lr}
	sub sp,sp,#8
.L10:
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	ldr r0,[r0,#0]
	str r0,[sp,#0]
	mov r0,#1
	str r0,[sp,#4]
	ldr r1,[sp,#4]
	ldr r0,[sp,#0]
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L11
	beq .L12
.L11:
	ldr r1,[sp,#4]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#4]
	mov r0,#1
	add sp,sp, #8
	pop {pc}
.L12:
	mov r0,#0
	add sp,sp, #8
	pop {pc}
