.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {r4,lr}
	sub sp,sp,#0
	bl .init
.L1:
	mov r0,#1
	bl findfa
	mov r4,r0
	mov r0,#2
	bl findfa
	cmp r4,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L2
	beq .L3
.L2:
	mov r0,#1
	add sp,sp, #0
	pop {r4,pc}
.L3:
	mov r0,#0
	add sp,sp, #0
	pop {r4,pc}
findfa:
	push {lr}
	sub sp,sp,#4
.L4:
	str r0,[sp,#0]
	mov r0,#1
	add sp,sp, #4
	pop {pc}
