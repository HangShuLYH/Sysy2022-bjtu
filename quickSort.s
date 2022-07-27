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
	push {r4,lr}
	sub sp,sp,#20
	bl .init
.L1:
	mov r1,#2
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	str r1,[r0,#0]
	mov r0,#0
	bl set_a
	cmp r0,#0
	bne .L2
	beq .L3
.L2:
	mov r0,#1
	bl set_b
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
	mov r1,#2
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	str r1,[r0,#0]
	mov r0,#0
	bl set_a
	cmp r0,#0
	bne .L4
	beq .L5
.L4:
	mov r0,#1
	bl set_b
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
.L6:
	mov r0,#3
	bl set_d
.L7:
	movw r0,#:lower16:d
	movt r0,#:upper16:d
	ldr r0,[r0,#0]
	bl putint
	b .L9
.L8:
	mov r0,#4
	bl set_d
.L9:
	movw r0,#:lower16:d
	movt r0,#:upper16:d
	ldr r0,[r0,#0]
	bl putint
.L10:
	mov r0,#65
	bl putch
.L11:
	b .L13
.L12:
	mov r0,#66
	bl putch
.L13:
	b .L15
.L14:
	mov r0,#67
	bl putch
.L15:
.L16:
	mov r0,#68
	bl putch
.L17:
	b .L19
.L18:
	mov r0,#69
	bl putch
.L19:
.L20:
	mov r0,#70
	bl putch
.L21:
	mov r0,#10
	bl putch
	mov r0,#0
	str r0,[sp,#0]
	mov r0,#1
	str r0,[sp,#4]
	mov r0,#2
	str r0,[sp,#8]
	mov r0,#3
	str r0,[sp,#12]
	mov r0,#4
	str r0,[sp,#16]
.L22:
	ldr r0,[sp,#0]
	cmp r0,#0
	bne .L23
	beq .L24
.L23:
	ldr r4,[sp,#4]
	mov r0,#32
	bl putch
	cmp r4,#0
	bne .L22
	beq .L24
.L24:
	ldr r0,[sp,#0]
	cmp r0,#0
	bne .L26
	beq .L25
.L25:
	ldr r0,[sp,#4]
	cmp r0,#0
	bne .L26
	beq .L27
.L26:
	mov r0,#67
	bl putch
.L27:
	ldr r1,[sp,#0]
	ldr r0,[sp,#4]
	cmp r1,r0
	mov r0,#0
	movge r0,#1
	cmp r0,#0
	bne .L29
	beq .L28
.L28:
	ldr r1,[sp,#4]
	ldr r0,[sp,#0]
	cmp r1,r0
	mov r0,#0
	movle r0,#1
	cmp r0,#0
	bne .L29
	beq .L30
.L29:
	mov r0,#72
	bl putch
.L30:
	ldr r1,[sp,#8]
	ldr r0,[sp,#4]
	cmp r1,r0
	mov r0,#0
	movge r0,#1
	cmp r0,#0
	bne .L31
	beq .L33
.L31:
	ldr r1,[sp,#16]
	ldr r0,[sp,#12]
	cmp r1,r0
	mov r0,#0
	movne r0,#1
	cmp r0,#0
	bne .L32
	beq .L33
.L32:
	mov r0,#73
	bl putch
.L33:
	ldr r1,[sp,#0]
	ldr r0,[sp,#4]
	cmp r0,#0
	mov r0,#0
	moveq r0,#1
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L34
	beq .L35
.L34:
	ldr r1,[sp,#12]
	ldr r0,[sp,#12]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L36
	beq .L35
.L35:
	ldr r1,[sp,#16]
	ldr r0,[sp,#16]
	cmp r1,r0
	mov r0,#0
	movge r0,#1
	cmp r0,#0
	bne .L36
	beq .L37
.L36:
	mov r0,#74
	bl putch
.L37:
	ldr r1,[sp,#0]
	ldr r0,[sp,#4]
	cmp r0,#0
	mov r0,#0
	moveq r0,#1
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L40
	beq .L38
.L38:
	ldr r1,[sp,#12]
	ldr r0,[sp,#12]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L39
	beq .L41
.L39:
	ldr r1,[sp,#16]
	ldr r0,[sp,#16]
	cmp r1,r0
	mov r0,#0
	movge r0,#1
	cmp r0,#0
	bne .L40
	beq .L41
.L40:
	mov r0,#75
	bl putch
.L41:
	mov r0,#10
	bl putch
	mov r0,#0
	add sp,sp, #20
	pop {r4,pc}
set_d:
	push {lr}
	sub sp,sp,#4
.L42:
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
.L43:
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
.L44:
	ldr r1,[sp,#0]
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	str r1,[r0,#0]
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	ldr r0,[r0,#0]
	add sp,sp, #4
	pop {pc}
