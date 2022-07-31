.arch armv7ve
.arm
.fpu neon
.text
.global main
.section .data
.align
MAX:
	.4byte 1000000000
.align
TWO:
	.4byte 2
.align
THREE:
	.4byte 3
.align
FIVE:
	.4byte 5
.section .text
.init:
.L0:
	bx lr
@ spilled Size: 0
@ stack Size: 64
main:
	push {lr}
	vpush {s1,s2}
	sub sp,sp, #64
	bl .init
.L1:
	movw r12,#:lower16:FACT
	movt r12,#:upper16:FACT
	vldr.32 s1,[r12,#0]
	movw r12,#:lower16:HEX2
	movt r12,#:upper16:HEX2
	vldr.32 s0,[r12,#0]
	bl float_eq
	bl assert_not
	movw r12,#:lower16:EVAL2
	movt r12,#:upper16:EVAL2
	vldr.32 s1,[r12,#0]
	movw r12,#:lower16:EVAL1
	movt r12,#:upper16:EVAL1
	vldr.32 s0,[r12,#0]
	bl float_eq
	bl assert_not
	movw r12,#:lower16:EVAL2
	movt r12,#:upper16:EVAL2
	vldr.32 s1,[r12,#0]
	movw r12,#:lower16:EVAL2
	movt r12,#:upper16:EVAL2
	vldr.32 s0,[r12,#0]
	bl float_eq
	bl assert
	mov r0,#5
	bl circle_area
	vmov.32 s2,s0
	mov r0,#5
	bl circle_area
	vmov.32 s1,s0
	vmov.32 s0,s2
	bl float_eq
	bl assert
	movw r12,#:lower16:CONV2
	movt r12,#:upper16:CONV2
	vldr.32 s1,[r12,#0]
	movw r12,#:lower16:CONV1
	movt r12,#:upper16:CONV1
	vldr.32 s0,[r12,#0]
	bl float_eq
	bl assert_not
.L2:
	bl ok
.L3:
.L4:
	bl ok
.L5:
	b .L8
.L6:
.L7:
	bl error
.L8:
.L9:
.L10:
	bl ok
.L11:
	mov r0,#1
	str r0,[sp,#0]
	mov r0,#0
	str r0,[sp,#4]
	movw r0,#0
	movt r0,#16256
	str r0,[sp,#8]
	movw r0,#0
	movt r0,#16384
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
	add r0,sp, #8
	bl getfarray
	str r0,[sp,#48]
.L12:
	ldr r1,[sp,#0]
	movw r0,#51712
	movt r0,#15258
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L13
	beq .L14
.L13:
	bl getfloat
	vstr.32 s0,[sp,#52]
	vldr.32 s1,[sp,#52]
	movw r12,#:lower16:PI
	movt r12,#:upper16:PI
	vldr.32 s0,[r12,#0]
	vmul.f32 s1,s0,s1
	vldr.32 s0,[sp,#52]
	vmul.f32 s0,s1,s0
	vstr.32 s0,[sp,#56]
	vldr.32 s0,[sp,#52]
	vcvt.s32.f32 s0,s0
	vmov r0,s0
	bl circle_area
	vstr.32 s0,[sp,#60]
	ldr r1,[sp,#4]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	add r2,sp, #8
	mla r3,r0,r1,r2
	ldr r1,[sp,#4]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	add r2,sp, #8
	mla r0,r0,r1,r2
	vldr.32 s1,[r0,#0]
	vldr.32 s0,[sp,#52]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[r3,#0]
	vldr.32 s0,[sp,#56]
	bl putfloat
	mov r0,#32
	bl putch
	vldr.32 s0,[sp,#60]
	vcvt.s32.f32 s0,s0
	vmov r0,s0
	bl putint
	mov r0,#10
	bl putch
	ldr r0,[sp,#0]
	vmov s1,r0
	vcvt.f32.s32 s1,s1
	movw r12,#:lower16:.f0
	movt r12,#:upper16:.f0
	vldr.32 s0,[r12,#0]
	vmul.f32 s0,s1,s0
	vcvt.s32.f32 s0,s0
	vmov r0,s0
	str r0,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#4]
	b .L12
.L14:
	ldr r0,[sp,#48]
	add r1,sp, #8
	bl putfarray
	mov r0,#0
	add sp,sp, #64
	vpop {s1,s2}
	pop {pc}
@ spilled Size: 0
@ stack Size: 4
assert_not:
	push {lr}
	sub sp,sp, #4
.L15:
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	cmp r0,#0
	bne .L16
	beq .L17
.L16:
	bl error
	b .L18
.L17:
	bl ok
.L18:
	add sp,sp, #4
	pop {pc}
@ spilled Size: 0
@ stack Size: 4
assert:
	push {lr}
	sub sp,sp, #4
.L19:
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	cmp r0,#0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L20
	beq .L21
.L20:
	bl error
	b .L22
.L21:
	bl ok
.L22:
	add sp,sp, #4
	pop {pc}
@ spilled Size: 0
@ stack Size: 0
ok:
	push {lr}
.L23:
	mov r0,#111
	bl putch
	mov r0,#107
	bl putch
	mov r0,#10
	bl putch
	pop {pc}
@ spilled Size: 0
@ stack Size: 0
error:
	push {lr}
.L24:
	mov r0,#101
	bl putch
	mov r0,#114
	bl putch
	mov r0,#114
	bl putch
	mov r0,#111
	bl putch
	mov r0,#114
	bl putch
	mov r0,#10
	bl putch
	pop {pc}
@ spilled Size: 0
@ stack Size: 8
float_eq:
	push {lr}
	vpush {s1}
	sub sp,sp, #8
.L25:
	vstr.32 s0,[sp,#0]
	vstr.32 s1,[sp,#4]
	vldr.32 s1,[sp,#0]
	vldr.32 s0,[sp,#4]
	vsub.f32 s0,s1,s0
	bl float_abs
	movw r12,#:lower16:EPS
	movt r12,#:upper16:EPS
	vldr.32 s1,[r12,#0]
	vcmpe.f32 s0,s1
	vmrs APSR_nzcv, FPSCR
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L26
	beq .L27
.L26:
	mov r0,#1
	add sp,sp, #8
	vpop {s1}
	pop {pc}
.L27:
	mov r0,#0
	add sp,sp, #8
	vpop {s1}
	pop {pc}
@ spilled Size: 0
@ stack Size: 4
circle_area:
	push {lr}
	vpush {s1,s2}
	sub sp,sp, #4
.L28:
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	vmov s1,r0
	vcvt.f32.s32 s1,s1
	movw r12,#:lower16:PI
	movt r12,#:upper16:PI
	vldr.32 s0,[r12,#0]
	vmul.f32 s1,s0,s1
	ldr r0,[sp,#0]
	vmov s0,r0
	vcvt.f32.s32 s0,s0
	vmul.f32 s2,s1,s0
	ldr r1,[sp,#0]
	ldr r0,[sp,#0]
	mul r0,r1,r0
	vmov s1,r0
	vcvt.f32.s32 s1,s1
	movw r12,#:lower16:PI
	movt r12,#:upper16:PI
	vldr.32 s0,[r12,#0]
	vmul.f32 s0,s1,s0
	vadd.f32 s1,s2,s0
	movw r12,#:lower16:.f1
	movt r12,#:upper16:.f1
	vldr.32 s0,[r12,#0]
	vdiv.f32 s0,s1,s0
	add sp,sp, #4
	vpop {s1,s2}
	pop {pc}
@ spilled Size: 0
@ stack Size: 4
float_abs:
	push {lr}
	vpush {s1}
	sub sp,sp, #4
.L29:
	vstr.32 s0,[sp,#0]
	vldr.32 s1,[sp,#0]
	movw r12,#:lower16:.f2
	movt r12,#:upper16:.f2
	vldr.32 s0,[r12,#0]
	vcmpe.f32 s1,s0
	vmrs APSR_nzcv, FPSCR
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L30
	beq .L31
.L30:
	vldr.32 s0,[sp,#0]
	vneg.f32 s0,s0
	add sp,sp, #4
	vpop {s1}
	pop {pc}
.L31:
	vldr.32 s0,[sp,#0]
	add sp,sp, #4
	vpop {s1}
	pop {pc}
.align
FACT:
	.4byte 3338725376
.align
.f2:
	.4byte 0
.align
EPS:
	.4byte 897988541
.align
HEX2:
	.4byte 1033895936
.align
.f1:
	.4byte 1073741824
.align
PI:
	.4byte 1078530011
.align
RADIUS:
	.4byte 1085276160
.align
.f0:
	.4byte 1092616192
.align
EVAL2:
	.4byte 1107966695
.align
EVAL1:
	.4byte 1119752446
.align
CONV1:
	.4byte 1130954752
.align
CONV2:
	.4byte 1166012416
