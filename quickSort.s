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
	sub sp,sp, #48
	bl .init
.L1:
	mov r1,#10
	movw r0,#:lower16:n
	movt r0,#:upper16:n
	str r1,[r0,#0]
	mov r0,#4
	str r0,[sp,#0]
	mov r0,#3
	str r0,[sp,#4]
	mov r0,#9
	str r0,[sp,#8]
	mov r0,#2
	str r0,[sp,#12]
	mov r0,#0
	str r0,[sp,#16]
	mov r0,#1
	str r0,[sp,#20]
	mov r0,#6
	str r0,[sp,#24]
	mov r0,#5
	str r0,[sp,#28]
	mov r0,#7
	str r0,[sp,#32]
	mov r0,#8
	str r0,[sp,#36]
	add r0,sp, #0
	bl bubblesort
	str r0,[sp,#40]
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
	sub sp,sp, #16
.L5:
	str r0,[sp,#0]
	mov r0,#0
	str r0,[sp,#4]
.L6:
	ldr r2,[sp,#4]
	movw r0,#:lower16:n
	movt r0,#:upper16:n
	ldr r1,[r0,#0]
	mov r0,#1
	sub r0,r1,r0
	cmp r2,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L7
	beq .L13
.L7:
	mov r0,#0
	str r0,[sp,#8]
.L8:
	ldr r2,[sp,#8]
	movw r0,#:lower16:n
	movt r0,#:upper16:n
	ldr r1,[r0,#0]
	ldr r0,[sp,#4]
	sub r1,r1,r0
	mov r0,#1
	sub r0,r1,r0
	cmp r2,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L9
	beq .L12
.L9:
	ldr r2,[sp,#0]
	ldr r1,[sp,#8]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	ldr r3,[sp,#0]
	ldr r2,[sp,#8]
	mov r1,#1
	add r2,r2,r1
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#4
	mla r1,r1,r2,r3
	ldr r1,[r1,#0]
	cmp r0,r1
	mov r0,#0
	movgt r0,#1
	cmp r0,#0
	bne .L10
	beq .L11
.L10:
	ldr r2,[sp,#0]
	ldr r1,[sp,#8]
	mov r0,#1
	add r1,r1,r0
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	str r0,[sp,#12]
	ldr r2,[sp,#0]
	ldr r1,[sp,#8]
	mov r0,#1
	add r1,r1,r0
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r3,r0,r1,r2
	ldr r2,[sp,#0]
	ldr r1,[sp,#8]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	str r0,[r3,#0]
	ldr r2,[sp,#0]
	ldr r1,[sp,#8]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r1,r0,r1,r2
	ldr r0,[sp,#12]
	str r0,[r1,#0]
.L11:
	ldr r1,[sp,#8]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#8]
	b .L8
.L12:
	ldr r1,[sp,#4]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#4]
	b .L6
.L13:
	mov r0,#0
	add sp,sp, #16
	pop {pc}
