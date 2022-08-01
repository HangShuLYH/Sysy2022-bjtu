.arch armv7ve
.arm
.fpu neon
.text
.global main
.section .bss
.align
M:
	.space 4
.align
L:
	.space 4
.align
N:
	.space 4
.section .text
.init:
.L0:
	bx lr
@ spilled Size: 0
@ stack Size: 148
main:
	push {lr}
	sub sp,sp, #148
	bl .init
.L1:
	mov r1,#3
	movw r0,#:lower16:N
	movt r0,#:upper16:N
	str r1,[r0,#0]
	mov r1,#3
	movw r0,#:lower16:M
	movt r0,#:upper16:M
	str r1,[r0,#0]
	mov r1,#3
	movw r0,#:lower16:L
	movt r0,#:upper16:L
	str r1,[r0,#0]
	mov r0,#0
	str r0,[sp,#140]
.L2:
	ldr r1,[sp,#140]
	movw r0,#:lower16:M
	movt r0,#:upper16:M
	ldr r0,[r0,#0]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L3
	beq .L4
.L3:
	ldr r1,[sp,#140]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #20
	mla r1,r1,r2,r0
	ldr r0,[sp,#140]
	vmov s0,r0
	vcvt.f32.s32 s0,s0
	vstr.32 s0,[r1,#0]
	ldr r1,[sp,#140]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #32
	mla r1,r1,r2,r0
	ldr r0,[sp,#140]
	vmov s0,r0
	vcvt.f32.s32 s0,s0
	vstr.32 s0,[r1,#0]
	ldr r1,[sp,#140]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #44
	mla r1,r1,r2,r0
	ldr r0,[sp,#140]
	vmov s0,r0
	vcvt.f32.s32 s0,s0
	vstr.32 s0,[r1,#0]
	ldr r1,[sp,#140]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #56
	mla r1,r1,r2,r0
	ldr r0,[sp,#140]
	vmov s0,r0
	vcvt.f32.s32 s0,s0
	vstr.32 s0,[r1,#0]
	ldr r1,[sp,#140]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #68
	mla r1,r1,r2,r0
	ldr r0,[sp,#140]
	vmov s0,r0
	vcvt.f32.s32 s0,s0
	vstr.32 s0,[r1,#0]
	ldr r1,[sp,#140]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #80
	mla r1,r1,r2,r0
	ldr r0,[sp,#140]
	vmov s0,r0
	vcvt.f32.s32 s0,s0
	vstr.32 s0,[r1,#0]
	ldr r1,[sp,#140]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#140]
	b .L2
.L4:
	add r0,sp, #128
	str r0,[sp,#16]
	add r0,sp, #116
	str r0,[sp,#12]
	add r0,sp, #92
	str r0,[sp,#8]
	add r0,sp, #80
	str r0,[sp,#4]
	add r0,sp, #68
	str r0,[sp,#0]
	add r3,sp, #56
	add r2,sp, #44
	add r1,sp, #32
	add r0,sp, #20
	bl add
	str r0,[sp,#140]
.L5:
	ldr r1,[sp,#140]
	movw r0,#:lower16:N
	movt r0,#:upper16:N
	ldr r0,[r0,#0]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L6
	beq .L7
.L6:
	ldr r1,[sp,#140]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #92
	mla r0,r1,r2,r0
	vldr.32 s0,[r0,#0]
	vcvt.s32.f32 s0,s0
	vmov r0,s0
	str r0,[sp,#144]
	ldr r0,[sp,#144]
	bl putint
	ldr r1,[sp,#140]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#140]
	b .L5
.L7:
	mov r0,#10
	str r0,[sp,#144]
	ldr r0,[sp,#144]
	bl putch
	mov r0,#0
	str r0,[sp,#140]
.L8:
	ldr r1,[sp,#140]
	movw r0,#:lower16:N
	movt r0,#:upper16:N
	ldr r0,[r0,#0]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L9
	beq .L10
.L9:
	ldr r1,[sp,#140]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #116
	mla r0,r1,r2,r0
	vldr.32 s0,[r0,#0]
	vcvt.s32.f32 s0,s0
	vmov r0,s0
	str r0,[sp,#144]
	ldr r0,[sp,#144]
	bl putint
	ldr r1,[sp,#140]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#140]
	b .L8
.L10:
	mov r0,#10
	str r0,[sp,#144]
	ldr r0,[sp,#144]
	bl putch
	mov r0,#0
	str r0,[sp,#140]
.L11:
	ldr r1,[sp,#140]
	movw r0,#:lower16:N
	movt r0,#:upper16:N
	ldr r0,[r0,#0]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L12
	beq .L13
.L12:
	ldr r1,[sp,#140]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #128
	mla r0,r1,r2,r0
	vldr.32 s0,[r0,#0]
	vcvt.s32.f32 s0,s0
	vmov r0,s0
	str r0,[sp,#144]
	ldr r0,[sp,#144]
	bl putint
	ldr r1,[sp,#140]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#140]
	b .L11
.L13:
	mov r0,#10
	str r0,[sp,#144]
	ldr r0,[sp,#144]
	bl putch
	mov r0,#0
	add sp,sp, #148
	pop {pc}
@ spilled Size: 0
@ stack Size: 40
add:
	push {lr}
	vpush {s1}
	sub sp,sp, #40
.L14:
	str r0,[sp,#0]
	str r1,[sp,#4]
	str r2,[sp,#8]
	str r3,[sp,#12]
	mov r0,#0
	str r0,[sp,#36]
.L15:
	ldr r1,[sp,#36]
	movw r0,#:lower16:M
	movt r0,#:upper16:M
	ldr r0,[r0,#0]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L16
	beq .L17
.L16:
	ldr r2,[sp,#56]
	ldr r1,[sp,#36]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r3,[sp,#0]
	ldr r2,[sp,#36]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#4
	mla r1,r1,r2,r3
	vldr.32 s1,[r1,#0]
	ldr r3,[sp,#12]
	ldr r2,[sp,#36]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#4
	mla r1,r1,r2,r3
	vldr.32 s0,[r1,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[r0,#0]
	ldr r2,[sp,#60]
	ldr r1,[sp,#36]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r3,[sp,#4]
	ldr r2,[sp,#36]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#4
	mla r1,r1,r2,r3
	vldr.32 s1,[r1,#0]
	ldr r3,[sp,#48]
	ldr r2,[sp,#36]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#4
	mla r1,r1,r2,r3
	vldr.32 s0,[r1,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[r0,#0]
	ldr r2,[sp,#64]
	ldr r1,[sp,#36]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r3,[sp,#8]
	ldr r2,[sp,#36]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#4
	mla r1,r1,r2,r3
	vldr.32 s1,[r1,#0]
	ldr r3,[sp,#52]
	ldr r2,[sp,#36]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#4
	mla r1,r1,r2,r3
	vldr.32 s0,[r1,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[r0,#0]
	ldr r1,[sp,#36]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#36]
	b .L15
.L17:
	mov r0,#0
	add sp,sp, #40
	vpop {s1}
	pop {pc}
