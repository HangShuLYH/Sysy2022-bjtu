.arch armv7ve
.arm
.section .bss
.align
b:
	.space 4
.align
c:
	.space 16
.global main
.section .text
.init:
.L0:
	mov r1,#5
	movw r0,#:lower16:b
	movt r0,#:upper16:b
	str r1,[r0,#0]
	movw r1,#:lower16:c
	movt r1,#:upper16:c
	add r1,r1, #0
	mov r0,#6
	str r0,[r1,#0]
	movw r1,#:lower16:c
	movt r1,#:upper16:c
	add r1,r1, #4
	mov r0,#7
	str r0,[r1,#0]
	movw r1,#:lower16:c
	movt r1,#:upper16:c
	add r1,r1, #8
	mov r0,#8
	str r0,[r1,#0]
	movw r1,#:lower16:c
	movt r1,#:upper16:c
	add r1,r1, #12
	mov r0,#9
	str r0,[r1,#0]
	bx lr
main:
	push {lr}
	sub sp,sp,#148
	bl .init
.L1:
	mov r0,#1
	str r0,[sp,#0]
	mov r0,#2
	str r0,[sp,#4]
	movw r0,#:lower16:c
	movt r0,#:upper16:c
	add r0,r0, #8
	ldr r0,[r0,#0]
	cmp r0,#0
	bne .L2
	beq .L3
.L2:
	mov r0,#0
	str r0,[sp,#8]
	mov r0,#0
	str r0,[sp,#12]
	mov r0,#0
	str r0,[sp,#16]
	mov r0,#0
	str r0,[sp,#20]
	mov r0,#0
	str r0,[sp,#24]
	mov r0,#0
	str r0,[sp,#28]
	mov r0,#0
	str r0,[sp,#32]
	mov r0,#0
	str r0,[sp,#36]
	mov r0,#0
	str r0,[sp,#40]
	mov r0,#0
	str r0,[sp,#44]
	mov r0,#2
	str r0,[sp,#48]
	mov r0,#1
	str r0,[sp,#52]
	mov r0,#8
	str r0,[sp,#56]
	mov r0,#0
	str r0,[sp,#60]
	mov r0,#0
	str r0,[sp,#64]
	mov r0,#0
	str r0,[sp,#68]
	mov r0,#0
	str r0,[sp,#72]
	mov r0,#0
	str r0,[sp,#76]
	mov r0,#0
	str r0,[sp,#80]
	mov r0,#0
	str r0,[sp,#84]
	mov r0,#0
	str r0,[sp,#88]
	mov r0,#0
	str r0,[sp,#92]
	mov r0,#0
	str r0,[sp,#96]
	mov r0,#0
	str r0,[sp,#100]
	mov r0,#0
	str r0,[sp,#104]
	mov r0,#0
	str r0,[sp,#108]
	mov r0,#0
	str r0,[sp,#112]
	mov r0,#0
	str r0,[sp,#116]
	mov r0,#0
	str r0,[sp,#120]
	mov r0,#0
	str r0,[sp,#124]
	mov r0,#0
	str r0,[sp,#128]
	mov r0,#0
	str r0,[sp,#132]
	mov r0,#0
	str r0,[sp,#136]
	mov r0,#0
	str r0,[sp,#140]
	mov r0,#0
	str r0,[sp,#144]
	ldr r1,[sp,#4]
	mov r0,#5
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r0,#4
	add r1,sp, #8
	mla r0,r0,r2,r1
	ldr r0,[r0,#0]
	bl putint
	ldr r2,[sp,#4]
	mov r0,#5
	mul r2,r2,r0
	mov r0,#1
	add r2,r2,r0
	mov r0,#4
	mla r0,r0,r2,r1
	ldr r0,[r0,#0]
	bl putint
	ldr r2,[sp,#4]
	mov r0,#5
	mul r2,r2,r0
	mov r0,#2
	add r2,r2,r0
	mov r0,#4
	mla r0,r0,r2,r1
	ldr r0,[r0,#0]
	bl putint
	b .L3
.L3:
	mov r0,#10
	bl putch
	movw r0,#:lower16:b
	movt r0,#:upper16:b
	ldr r0,[r0,#0]
	bl putint
	mov r0,#10
	bl putch
	movw r0,#:lower16:c
	movt r0,#:upper16:c
	add r0,r0, #0
	ldr r0,[r0,#0]
	bl putint
	movw r0,#:lower16:c
	movt r0,#:upper16:c
	add r0,r0, #4
	ldr r0,[r0,#0]
	bl putint
	movw r0,#:lower16:c
	movt r0,#:upper16:c
	add r0,r0, #8
	ldr r0,[r0,#0]
	bl putint
	movw r0,#:lower16:c
	movt r0,#:upper16:c
	add r0,r0, #12
	ldr r0,[r0,#0]
	bl putint
	mov r0,#10
	bl putch
	mov r0,#0
	add sp,sp, #148
	pop {pc}
