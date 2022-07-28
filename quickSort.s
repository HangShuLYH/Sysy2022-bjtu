.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {lr}
	sub sp,sp, #32768
	bl .init
.L1:
	add r0,sp, #0
	bl read_str
	add r0,sp, #16384
	bl read_str
	add r0,sp, #0
	add r1,sp, #16384
	bl KMP
	bl putint
	mov r0,#10
	bl putch
	mov r0,#0
	add sp,sp, #32768
	pop {pc}
read_str:
	push {r4,lr}
	sub sp,sp, #8
.L2:
	str r0,[sp,#0]
	mov r0,#0
	str r0,[sp,#4]
.L3:
.L4:
	ldr r2,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r4,r0,r1,r2
	bl getch
	str r0,[r4,#0]
	ldr r2,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r1,[r0,#0]
	mov r0,#10
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L5
	beq .L6
.L5:
	b .L7
.L6:
	ldr r1,[sp,#4]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#4]
	b .L3
.L7:
	ldr r2,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r1,r0,r1,r2
	mov r0,#0
	str r0,[r1,#0]
	ldr r0,[sp,#4]
	add sp,sp, #8
	pop {r4,pc}
KMP:
	push {r12,lr}
	mov r12,#16400
	sub sp,sp,r12
.L8:
	str r0,[sp,#0]
	str r1,[sp,#4]
	ldr r0,[sp,#0]
	add r1,sp, #8
	bl get_next
	mov r0,#0
	add r12,sp, #16392
	str r0,[r12,#0]
	mov r0,#0
	add r12,sp, #16396
	str r0,[r12,#0]
.L9:
	ldr r2,[sp,#4]
	add r12,sp, #16396
	ldr r1,[r12,#0]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	cmp r0,#0
	bne .L10
	beq .L15
.L10:
	ldr r2,[sp,#0]
	add r12,sp, #16392
	ldr r1,[r12,#0]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r3,[r0,#0]
	ldr r2,[sp,#4]
	add r12,sp, #16396
	ldr r1,[r12,#0]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	cmp r3,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L11
	beq .L13
.L11:
	add r12,sp, #16392
	ldr r1,[r12,#0]
	mov r0,#1
	add r0,r1,r0
	add r12,sp, #16392
	str r0,[r12,#0]
	add r12,sp, #16396
	ldr r1,[r12,#0]
	mov r0,#1
	add r0,r1,r0
	add r12,sp, #16396
	str r0,[r12,#0]
	ldr r2,[sp,#0]
	add r12,sp, #16392
	ldr r1,[r12,#0]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	cmp r0,#0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L12
	beq .L9
.L12:
	add r12,sp, #16396
	ldr r0,[r12,#0]
	mov r12,#16400
	add sp,sp,r12
	pop {r12,pc}
.L13:
	add r12,sp, #16392
	ldr r1,[r12,#0]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #8
	mla r0,r1,r2,r0
	ldr r0,[r0,#0]
	add r12,sp, #16392
	str r0,[r12,#0]
	add r12,sp, #16392
	ldr r1,[r12,#0]
	mvn r0,#0
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L14
	beq .L9
.L14:
	add r12,sp, #16392
	ldr r1,[r12,#0]
	mov r0,#1
	add r0,r1,r0
	add r12,sp, #16392
	str r0,[r12,#0]
	add r12,sp, #16396
	ldr r1,[r12,#0]
	mov r0,#1
	add r0,r1,r0
	add r12,sp, #16396
	str r0,[r12,#0]
	b .L9
.L15:
	mov r0,#-1
	mov r12,#16400
	add sp,sp,r12
	pop {r12,pc}
get_next:
	push {lr}
	sub sp,sp, #16
.L16:
	str r0,[sp,#0]
	str r1,[sp,#4]
	ldr r0,[sp,#4]
	add r1,r0, #0
	mvn r0,#0
	str r0,[r1,#0]
	mov r0,#0
	str r0,[sp,#8]
	mvn r0,#0
	str r0,[sp,#12]
.L17:
	ldr r2,[sp,#0]
	ldr r1,[sp,#8]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	cmp r0,#0
	bne .L18
	beq .L22
.L18:
	ldr r1,[sp,#12]
	mvn r0,#0
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L20
	beq .L19
.L19:
	ldr r2,[sp,#0]
	ldr r1,[sp,#8]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r3,[r0,#0]
	ldr r2,[sp,#0]
	ldr r1,[sp,#12]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	cmp r3,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L20
	beq .L21
.L20:
	ldr r1,[sp,#12]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#12]
	ldr r1,[sp,#8]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#8]
	ldr r2,[sp,#4]
	ldr r1,[sp,#8]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r1,r0,r1,r2
	ldr r0,[sp,#12]
	str r0,[r1,#0]
	b .L17
.L21:
	ldr r2,[sp,#4]
	ldr r1,[sp,#12]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	str r0,[sp,#12]
	b .L17
.L22:
	add sp,sp, #16
	pop {pc}
