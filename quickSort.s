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
	sub sp,sp,#220
	bl .init
.L1:
	mov r0,#1
	str r0,[sp,#0]
	mov r0,#2
	str r0,[sp,#4]
	mov r0,#3
	str r0,[sp,#4]
	ldr r0,[sp,#4]
	bl putint
	ldr r0,[sp,#4]
	bl putint
	ldr r0,[sp,#0]
	bl putint
	mov r0,#10
	bl putch
	b .L2
.L2:
	ldr r2,[sp,#0]
	mov r0,#5
	cmp r2,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L3
	beq .L5
.L3:
	mov r0,#0
	str r0,[sp,#8]
	ldr r2,[sp,#8]
	mov r0,#1
	add r0,r2,r0
	str r0,[sp,#8]
	ldr r0,[sp,#8]
	cmp r0,#0
	bne .L4
	beq .L2
.L4:
	b .L5
.L5:
	ldr r0,[sp,#0]
	bl putint
	mov r0,#10
	bl putch
	movw r2,#:lower16:c
	movt r2,#:upper16:c
	add r2,r2, #8
	mov r0,#1
	str r0,[r2,#0]
	mov r0,#0
	str r0,[sp,#12]
	mov r0,#9
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
	mov r0,#8
	str r0,[sp,#44]
	mov r0,#3
	str r0,[sp,#48]
	mov r0,#0
	str r0,[sp,#52]
	mov r0,#0
	str r0,[sp,#56]
	mov r0,#0
	str r0,[sp,#60]
	mov r0,#0
	str r0,[sp,#64]
	mov r0,#0
	str r0,[sp,#68]
	mov r0,#0
	str r0,[sp,#72]
	mov r0,#2
	str r0,[sp,#76]
	movw r0,#:lower16:c
	movt r0,#:upper16:c
	add r0,r0, #8
	ldr r0,[r0,#0]
	cmp r0,#0
	bne .L6
	beq .L7
.L6:
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
	mov r0,#2
	str r0,[sp,#120]
	mov r0,#1
	str r0,[sp,#124]
	mov r0,#8
	str r0,[sp,#128]
	mov r0,#0
	str r0,[sp,#132]
	mov r0,#0
	str r0,[sp,#136]
	mov r0,#0
	str r0,[sp,#140]
	mov r0,#0
	str r0,[sp,#144]
	mov r0,#0
	str r0,[sp,#148]
	mov r0,#0
	str r0,[sp,#152]
	mov r0,#0
	str r0,[sp,#156]
	mov r0,#0
	str r0,[sp,#160]
	mov r0,#0
	str r0,[sp,#164]
	mov r0,#0
	str r0,[sp,#168]
	mov r0,#0
	str r0,[sp,#172]
	mov r0,#0
	str r0,[sp,#176]
	mov r0,#0
	str r0,[sp,#180]
	mov r0,#0
	str r0,[sp,#184]
	mov r0,#0
	str r0,[sp,#188]
	mov r0,#0
	str r0,[sp,#192]
	mov r0,#0
	str r0,[sp,#196]
	mov r0,#0
	str r0,[sp,#200]
	mov r0,#0
	str r0,[sp,#204]
	mov r0,#0
	str r0,[sp,#208]
	mov r0,#0
	str r0,[sp,#212]
	mov r0,#0
	str r0,[sp,#216]
	ldr r2,[sp,#76]
	mov r0,#5
	mul r2,r2,r0
	mov r0,#0
	add r2,r2,r0
	mov r0,#4
	mla r0,r0,r2,r1
	ldr r0,[r0,#0]
	bl putint
	ldr r2,[sp,#76]
	mov r0,#5
	mul r2,r2,r0
	mov r0,#1
	add r2,r2,r0
	mov r0,#4
	mla r0,r0,r2,r1
	ldr r0,[r0,#0]
	bl putint
	ldr r2,[sp,#76]
	mov r0,#5
	mul r2,r2,r0
	mov r0,#2
	add r2,r2,r0
	mov r0,#4
	mla r0,r0,r2,r1
	ldr r0,[r0,#0]
	bl putint
	b .L7
.L7:
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
	add sp,sp, #220
	pop {pc}
