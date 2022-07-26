.arch armv7ve
.arm
.section .bss
.align
buf:
	.space 800
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {lr}
	sub sp,sp,#4
	bl .init
.L1:
	movw r0,#:lower16:buf
	movt r0,#:upper16:buf
	add r0,r0, #400
	bl getarray
	str r0,[sp,#0]
	ldr r1,[sp,#0]
	mov r0,#0
	bl merge_sort
	ldr r0,[sp,#0]
	movw r1,#:lower16:buf
	movt r1,#:upper16:buf
	add r1,r1, #0
	bl putarray
	mov r0,#0
	add sp,sp, #4
	pop {pc}
merge_sort:
	push {lr}
	sub sp,sp,#24
.L2:
	str r0,[sp,#0]
	str r1,[sp,#4]
	ldr r1,[sp,#0]
	mov r0,#1
	add r1,r1,r0
	ldr r0,[sp,#4]
	cmp r1,r0
	mov r0,#0
	movge r0,#1
	cmp r0,#0
	bne .L3
	beq .L4
.L3:
	add sp,sp, #24
	pop {pc}
.L4:
	ldr r1,[sp,#0]
	ldr r0,[sp,#4]
	add r1,r1,r0
	mov r0,#2
	sdiv r0,r1,r0
	str r0,[sp,#8]
	ldr r0,[sp,#0]
	ldr r1,[sp,#8]
	bl merge_sort
	ldr r0,[sp,#8]
	ldr r1,[sp,#4]
	bl merge_sort
	ldr r0,[sp,#0]
	str r0,[sp,#12]
	ldr r0,[sp,#8]
	str r0,[sp,#16]
	ldr r0,[sp,#0]
	str r0,[sp,#20]
	b .L5
.L5:
	ldr r1,[sp,#12]
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L6
	beq .L11
.L6:
	ldr r1,[sp,#16]
	ldr r0,[sp,#4]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L7
	beq .L11
.L7:
	ldr r1,[sp,#12]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	movw r1,#:lower16:buf
	movt r1,#:upper16:buf
	mov r0,#4
	mla r1,r0,r2,r1
	ldr r3,[r1,#0]
	ldr r1,[sp,#16]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	movw r1,#:lower16:buf
	movt r1,#:upper16:buf
	mov r0,#4
	mla r1,r0,r2,r1
	ldr r0,[r1,#0]
	cmp r3,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L8
	beq .L9
.L8:
	ldr r1,[sp,#20]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#100
	add r2,r1,r0
	movw r0,#:lower16:buf
	movt r0,#:upper16:buf
	mov r1,#4
	mla r0,r1,r2,r0
	ldr r2,[sp,#12]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	movw r2,#:lower16:buf
	movt r2,#:upper16:buf
	mov r1,#4
	mla r2,r1,r3,r2
	ldr r1,[r2,#0]
	str r1,[r0,#0]
	ldr r1,[sp,#12]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#12]
	b .L10
.L9:
	ldr r1,[sp,#20]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#100
	add r2,r1,r0
	movw r0,#:lower16:buf
	movt r0,#:upper16:buf
	mov r1,#4
	mla r0,r1,r2,r0
	ldr r2,[sp,#16]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	movw r2,#:lower16:buf
	movt r2,#:upper16:buf
	mov r1,#4
	mla r2,r1,r3,r2
	ldr r1,[r2,#0]
	str r1,[r0,#0]
	ldr r1,[sp,#16]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#16]
	b .L10
.L10:
	ldr r1,[sp,#20]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#20]
	b .L5
.L11:
	ldr r1,[sp,#12]
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L12
	beq .L13
.L12:
	ldr r1,[sp,#20]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#100
	add r2,r1,r0
	movw r0,#:lower16:buf
	movt r0,#:upper16:buf
	mov r1,#4
	mla r0,r1,r2,r0
	ldr r2,[sp,#12]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	movw r2,#:lower16:buf
	movt r2,#:upper16:buf
	mov r1,#4
	mla r2,r1,r3,r2
	ldr r1,[r2,#0]
	str r1,[r0,#0]
	ldr r1,[sp,#12]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#12]
	ldr r1,[sp,#20]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#20]
	b .L11
.L13:
	ldr r1,[sp,#16]
	ldr r0,[sp,#4]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L14
	beq .L15
.L14:
	ldr r1,[sp,#20]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#100
	add r2,r1,r0
	movw r0,#:lower16:buf
	movt r0,#:upper16:buf
	mov r1,#4
	mla r0,r1,r2,r0
	ldr r2,[sp,#16]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	movw r2,#:lower16:buf
	movt r2,#:upper16:buf
	mov r1,#4
	mla r2,r1,r3,r2
	ldr r1,[r2,#0]
	str r1,[r0,#0]
	ldr r1,[sp,#16]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#16]
	ldr r1,[sp,#20]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#20]
	b .L13
.L15:
	ldr r1,[sp,#0]
	ldr r0,[sp,#4]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L16
	beq .L17
.L16:
	ldr r1,[sp,#0]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	movw r0,#:lower16:buf
	movt r0,#:upper16:buf
	mov r1,#4
	mla r0,r1,r2,r0
	ldr r2,[sp,#0]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#100
	add r3,r2,r1
	movw r2,#:lower16:buf
	movt r2,#:upper16:buf
	mov r1,#4
	mla r2,r1,r3,r2
	ldr r1,[r2,#0]
	str r1,[r0,#0]
	ldr r1,[sp,#0]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#0]
	b .L15
.L17:
	add sp,sp, #24
	pop {pc}
