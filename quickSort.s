.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {lr}
	sub sp,sp,#16
	bl .init
.L1:
	mov r0,#7
	str r0,[sp,#0]
	mov r0,#15
	str r0,[sp,#4]
	mov r0,#1
	str r0,[sp,#8]
	mov r0,#1
	str r0,[sp,#12]
	ldr r0,[sp,#0]
	ldr r1,[sp,#4]
	add r2,sp, #8
	add r3,sp, #12
	bl exgcd
	ldr r2,[sp,#8]
	ldr r0,[sp,#4]
	sdiv r1,r2,r0
	mul r1,r1,r0
	sub r1,r2,r1
	ldr r0,[sp,#4]
	add r2,r1,r0
	ldr r1,[sp,#4]
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	str r0,[sp,#8]
	ldr r0,[sp,#8]
	bl putint
	mov r0,#0
	add sp,sp, #16
	pop {pc}
exgcd:
	push {lr}
	sub sp,sp,#24
.L2:
	str r0,[sp,#0]
	str r1,[sp,#4]
	str r2,[sp,#8]
	str r3,[sp,#12]
	ldr r1,[sp,#4]
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L3
	beq .L4
.L3:
	ldr r0,[sp,#8]
	mov r0,#1
	str r0,[sp,#0]
	ldr r0,[sp,#12]
	mov r0,#0
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	add sp,sp, #24
	pop {pc}
.L4:
	ldr r0,[sp,#4]
	ldr r3,[sp,#0]
	ldr r2,[sp,#4]
	sdiv r1,r3,r2
	mul r1,r1,r2
	sub r1,r3,r1
	ldr r2,[sp,#8]
	ldr r2,[sp,#12]
	add r2,sp, #0
	add r3,sp, #0
	bl exgcd
	str r0,[sp,#16]
	ldr r0,[sp,#8]
	ldr r0,[sp,#0]
	str r0,[sp,#20]
	ldr r0,[sp,#8]
	ldr r0,[sp,#12]
	ldr r0,[sp,#0]
	str r0,[sp,#0]
	ldr r0,[sp,#12]
	ldr r2,[sp,#20]
	ldr r1,[sp,#0]
	ldr r0,[sp,#4]
	sdiv r1,r1,r0
	ldr r0,[sp,#12]
	ldr r0,[sp,#0]
	mul r0,r1,r0
	sub r0,r2,r0
	str r0,[sp,#0]
	ldr r0,[sp,#16]
	add sp,sp, #24
	pop {pc}
