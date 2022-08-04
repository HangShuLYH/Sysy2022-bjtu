.arch armv7ve
.arm
.global quickSort
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {r0,r1,r2,lr}
	sub sp,sp,#36
	bl .init
.L1:
	mov r0,#9
	str r0,[sp,#0]
	mov r0,#8
	str r0,[sp,#4]
	mov r0,#7
	str r0,[sp,#8]
	mov r0,#1
	str r0,[sp,#12]
	mov r0,#6
	str r0,[sp,#16]
	mov r0,#5
	str r0,[sp,#20]
	mov r0,#2
	str r0,[sp,#24]
	mov r0,#3
	str r0,[sp,#28]
	mov r0,#4
	str r0,[sp,#32]
	add r0,sp, #0
	mov r1,#0
	mov r2,#8
	bl quickSort
	mov r0,#0
	add sp,sp, #28
	pop {r0,r1,r2,pc}
quickSort:
	push {r0,r1,r2,r3,lr}
	sub sp,sp,#28
.L2:
	str r0,[sp,#0]
	str r1,[sp,#4]
	str r2,[sp,#8]
	ldr r1,[sp,#4]
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#1
	beq .L3
	bne .L13
.L3:
	ldr r0,[sp,#4]
	str r0,[sp,#20]
	ldr r0,[sp,#4]
	str r0,[sp,#12]
	ldr r0,[sp,#8]
	str r0,[sp,#16]
	b .L4
.L4:
	ldr r1,[sp,#12]
	ldr r0,[sp,#16]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#1
	beq .L5
	bne .L12
.L5:
	ldr r2,[sp,#0]
	ldr r1,[sp,#12]
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r3,[r0,#0]
	ldr r2,[sp,#0]
	ldr r1,[sp,#20]
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	cmp r3,r0
	mov r0,#0
	movle r0,#1
	cmp r0,#1
	beq .L6
	bne .L8
.L6:
	ldr r1,[sp,#12]
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#1
	beq .L7
	bne .L8
.L7:
	ldr r1,[sp,#12]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#12]
	b .L5
.L8:
	ldr r2,[sp,#0]
	ldr r1,[sp,#16]
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r3,[r0,#0]
	ldr r2,[sp,#0]
	ldr r1,[sp,#20]
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	cmp r3,r0
	mov r0,#0
	movgt r0,#1
	cmp r0,#1
	beq .L9
	bne .L10
.L9:
	ldr r1,[sp,#16]
	mov r0,#1
	sub r0,r1,r0
	str r0,[sp,#16]
	b .L8
.L10:
	ldr r1,[sp,#12]
	ldr r0,[sp,#16]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#1
	beq .L11
	bne .L4
.L11:
	ldr r2,[sp,#0]
	ldr r1,[sp,#12]
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	str r0,[sp,#24]
	ldr r2,[sp,#0]
	ldr r1,[sp,#12]
	mov r0,#4
	mla r3,r0,r1,r2
	ldr r2,[sp,#0]
	ldr r1,[sp,#16]
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	str r0,[r3,#0]
	ldr r2,[sp,#0]
	ldr r1,[sp,#16]
	mov r0,#4
	mla r1,r0,r1,r2
	ldr r0,[sp,#24]
	str r0,[r1,#0]
	b .L4
.L12:
	ldr r2,[sp,#0]
	ldr r1,[sp,#20]
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	str r0,[sp,#24]
	ldr r2,[sp,#0]
	ldr r1,[sp,#20]
	mov r0,#4
	mla r3,r0,r1,r2
	ldr r2,[sp,#0]
	ldr r1,[sp,#16]
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	str r0,[r3,#0]
	ldr r2,[sp,#0]
	ldr r1,[sp,#16]
	mov r0,#4
	mla r1,r0,r1,r2
	ldr r0,[sp,#24]
	str r0,[r1,#0]
	ldr r0,[sp,#0]
	ldr r1,[sp,#4]
	ldr r3,[sp,#16]
	mov r2,#1
	sub r2,r3,r2
	bl quickSort
	ldr r0,[sp,#0]
	ldr r2,[sp,#16]
	mov r1,#1
	add r1,r2,r1
	ldr r2,[sp,#8]
	bl quickSort
	b .L13
.L13:
	add sp,sp, #28
	pop {r0,r1,r2,r3,pc}
