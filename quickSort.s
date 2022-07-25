.arch armv7ve
.arm
.section .bss
.align
a:
	.space 4
.align
b:
	.space 4
.align
d:
	.space 4
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {lr}
	sub sp,sp,#28
	bl .init
.L1:
	mov r2,#2
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	str r2,[r0,#0]
	mov r2,#3
	movw r0,#:lower16:b
	movt r0,#:upper16:b
	str r2,[r0,#0]
	mov r0,#0
	bl set_a
	cmp r0,#1
	beq .L2
	bne .L3
.L2:
	mov r0,#1
	bl set_b
	cmp r0,#1
	beq .L3
	bne .L3
.L3:
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	ldr r0,[r0,#0]
	bl putint
	mov r0,#32
	bl putch
	movw r0,#:lower16:b
	movt r0,#:upper16:b
	ldr r0,[r0,#0]
	bl putint
	mov r0,#32
	bl putch
	mov r2,#2
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	str r2,[r0,#0]
	mov r2,#3
	movw r0,#:lower16:b
	movt r0,#:upper16:b
	str r2,[r0,#0]
	mov r0,#0
	bl set_a
	cmp r0,#1
	beq .L4
	bne .L5
.L4:
	mov r0,#1
	bl set_b
	cmp r0,#1
	beq .L5
	bne .L5
.L5:
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	ldr r0,[r0,#0]
	bl putint
	mov r0,#32
	bl putch
	movw r0,#:lower16:b
	movt r0,#:upper16:b
	ldr r0,[r0,#0]
	bl putint
	mov r0,#10
	bl putch
	mov r2,#2
	movw r0,#:lower16:d
	movt r0,#:upper16:d
	str r2,[r0,#0]
	mov r0,#1
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	cmp r0,#1
	beq .L6
	bne .L7
.L6:
	mov r0,#3
	bl set_d
	cmp r0,#1
	beq .L7
	bne .L7
.L7:
	movw r0,#:lower16:d
	movt r0,#:upper16:d
	ldr r0,[r0,#0]
	bl putint
	mov r0,#32
	bl putch
	mov r0,#1
	str r0,[sp,#4]
	ldr r0,[sp,#4]
	cmp r0,#1
	beq .L9
	bne .L8
.L8:
	mov r0,#4
	bl set_d
	cmp r0,#1
	beq .L9
	bne .L9
.L9:
	movw r0,#:lower16:d
	movt r0,#:upper16:d
	ldr r0,[r0,#0]
	bl putint
	mov r0,#10
	bl putch
	cmp r1,#1
	beq .L10
	bne .L11
.L10:
	mov r0,#65
	bl putch
	b .L11
.L11:
	mov r0,#66
	bl putch
	cmp r1,#1
	beq .L12
	bne .L13
.L12:
	mov r0,#67
	bl putch
	b .L13
.L13:
	cmp r1,#1
	beq .L14
	bne .L15
.L14:
	mov r0,#68
	bl putch
	b .L15
.L15:
	mov r0,#69
	bl putch
	mov r0,#70
	bl putch
	mov r0,#10
	bl putch
	mov r0,#0
	str r0,[sp,#8]
	mov r0,#1
	str r0,[sp,#12]
	mov r0,#2
	str r0,[sp,#16]
	mov r0,#3
	str r0,[sp,#20]
	mov r0,#4
	str r0,[sp,#24]
	b .L16
.L16:
	ldr r0,[sp,#8]
	cmp r0,#1
	beq .L17
	bne .L18
.L17:
	ldr r1,[sp,#12]
	mov r0,#32
	bl putch
	cmp r1,#1
	beq .L16
	bne .L18
.L18:
	ldr r0,[sp,#8]
	cmp r0,#1
	beq .L20
	bne .L19
.L19:
	ldr r1,[sp,#12]
	mov r0,#67
	bl putch
	cmp r1,#1
	beq .L20
	bne .L20
.L20:
	ldr r1,[sp,#8]
	ldr r0,[sp,#12]
	cmp r1,r0
	mov r0,#0
	movge r0,#1
	cmp r0,#1
	beq .L22
	bne .L21
.L21:
	ldr r1,[sp,#12]
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r1,#0
	movle r1,#1
	mov r0,#72
	bl putch
	cmp r1,#1
	beq .L22
	bne .L22
.L22:
	ldr r1,[sp,#16]
	ldr r0,[sp,#12]
	cmp r1,r0
	mov r0,#0
	movge r0,#1
	cmp r0,#1
	beq .L23
	bne .L25
.L23:
	ldr r1,[sp,#24]
	ldr r0,[sp,#20]
	cmp r1,r0
	mov r0,#0
	movne r0,#1
	cmp r0,#1
	beq .L24
	bne .L25
.L24:
	mov r0,#73
	bl putch
	b .L25
.L25:
	ldr r1,[sp,#8]
	ldr r0,[sp,#12]
	cmp r0,#0
	mov r0,#0
	moveq r0,#1
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#1
	beq .L26
	bne .L27
.L26:
	ldr r1,[sp,#20]
	ldr r0,[sp,#20]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#1
	beq .L28
	bne .L27
.L27:
	ldr r1,[sp,#24]
	ldr r0,[sp,#24]
	cmp r1,r0
	mov r0,#0
	movge r0,#1
	cmp r0,#1
	beq .L28
	bne .L29
.L28:
	mov r0,#74
	bl putch
	b .L29
.L29:
	ldr r1,[sp,#8]
	ldr r0,[sp,#12]
	cmp r0,#0
	mov r0,#0
	moveq r0,#1
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#1
	beq .L32
	bne .L30
.L30:
	ldr r1,[sp,#20]
	ldr r0,[sp,#20]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#1
	beq .L31
	bne .L32
.L31:
	ldr r1,[sp,#24]
	ldr r0,[sp,#24]
	cmp r1,r0
	mov r1,#0
	movge r1,#1
	mov r0,#75
	bl putch
	cmp r1,#1
	beq .L32
	bne .L32
.L32:
	mov r0,#10
	bl putch
	mov r0,#0
	add sp,sp, #28
	pop {pc}
set_d:
	push {lr}
	sub sp,sp,#4
.L33:
	str r0,[sp,#0]
	ldr r1,[sp,#0]
	movw r0,#:lower16:d
	movt r0,#:upper16:d
	str r1,[r0,#0]
	movw r0,#:lower16:d
	movt r0,#:upper16:d
	ldr r0,[r0,#0]
	add sp,sp, #4
	pop {pc}
set_b:
	push {lr}
	sub sp,sp,#4
.L34:
	str r0,[sp,#0]
	ldr r1,[sp,#0]
	movw r0,#:lower16:b
	movt r0,#:upper16:b
	str r1,[r0,#0]
	movw r0,#:lower16:b
	movt r0,#:upper16:b
	ldr r0,[r0,#0]
	add sp,sp, #4
	pop {pc}
set_a:
	push {lr}
	sub sp,sp,#4
.L35:
	str r0,[sp,#0]
	ldr r1,[sp,#0]
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	str r1,[r0,#0]
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	ldr r0,[r0,#0]
	add sp,sp, #4
	pop {pc}
