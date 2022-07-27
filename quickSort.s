.arch armv7ve
.arm
.section .data
.align
TOKEN_NUM:
	.4byte 0
.align
TOKEN_OTHER:
	.4byte 1
.section .bss
.align
last_char:
	.space 4
.align
num:
	.space 4
.align
other:
	.space 4
.align
cur_token:
	.space 4
.global main
.section .text
.init:
.L0:
	mov r1,#32
	movw r0,#:lower16:last_char
	movt r0,#:upper16:last_char
	str r1,[r0,#0]
	bx lr
main:
	push {lr}
	bl .init
.L1:
	mov r0,#0
	pop {pc}
next_token:
	push {lr}
.L2:
	movw r0,#:lower16:last_char
	movt r0,#:upper16:last_char
	ldr r0,[r0,#0]
	bl is_space
	cmp r0,#0
	bne .L3
	beq .L4
.L3:
	bl next_char
	b .L2
.L4:
	movw r0,#:lower16:cur_token
	movt r0,#:upper16:cur_token
	ldr r0,[r0,#0]
	pop {pc}
is_space:
	push {lr}
	sub sp,sp, #4
.L5:
	str r0,[sp,#0]
	mov r0,#0
	add sp,sp, #4
	pop {pc}
next_char:
	push {lr}
.L6:
	mov r0,#0
	pop {pc}
