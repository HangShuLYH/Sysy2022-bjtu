.arch armv7ve
.arm
.fpu neon
.text
.global main
.section .bss
.align
seed:
	.space 12
.align
staticvalue:
	.space 4
.align
a:
	.space 40000
.section .text
.memset:
	push {r5}
	mov r4,#0
	mov r5,#0
.memset8:
	sub r1,r1,#8
	cmp r1,#0
	blt .memset4
	strd r4,r5,[r0],r3
	bne .memset8
	b .memset_end
.memset4:
	str r4,[r0],#4
.memset_end:
	pop {r5}
	bx lr
.init:
.L0:
	movw r1,#:lower16:seed
	movt r1,#:upper16:seed
	movw r0,#48287
	movt r0,#304
	str r0,[r1,#0]
	movw r1,#:lower16:seed
	movt r1,#:upper16:seed
	add r1,r1, #4
	movw r0,#58069
	movt r0,#304
	str r0,[r1,#0]
	movw r1,#:lower16:seed
	movt r1,#:upper16:seed
	add r1,r1, #8
	movw r0,#51712
	movt r0,#15258
	str r0,[r1,#0]
	mov r1,#0
	movw r0,#:lower16:staticvalue
	movt r0,#:upper16:staticvalue
	str r1,[r0,#0]
	bx lr
@ spilled Size: 0
@ stack Size: 412
main:
	push {lr}
	sub sp,sp, #412
	bl .init
.L1:
	add r0,sp, #0
	mov r1,#400
	bl .memset
	mov r0,#5
	str r0,[sp,#0]
	mov r0,#3
	str r0,[sp,#4]
	mov r0,#2
	str r0,[sp,#8]
	bl getint
	str r0,[sp,#400]
	bl getint
	movw r1,#:lower16:staticvalue
	movt r1,#:upper16:staticvalue
	str r0,[r1,#0]
	mov r0,#56
	bl _sysy_starttime
.L2:
	ldr r1,[sp,#400]
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	movgt r0,#1
	cmp r0,#0
	bne .L3
	beq .L4
.L3:
	ldr r1,[sp,#400]
	mov r0,#1
	sub r0,r1,r0
	str r0,[sp,#400]
	bl rand
	movw r2,#37856
	movt r2,#4
	sdiv r1,r0,r2
	mul r1,r1,r2
	sub r1,r0,r1
	str r1,[sp,#404]
	bl rand
	mov r2,#2
	sdiv r1,r0,r2
	mul r1,r1,r2
	sub r1,r0,r1
	str r1,[sp,#408]
	movw r0,#:lower16:a
	movt r0,#:upper16:a
	ldr r1,[sp,#404]
	ldr r2,[sp,#408]
	bl set
	b .L2
.L4:
	mov r0,#64
	bl _sysy_stoptime
	movw r1,#:lower16:a
	movt r1,#:upper16:a
	mov r0,#10000
	bl putarray
	mov r0,#0
	add sp,sp, #412
	pop {pc}
@ spilled Size: 0
@ stack Size: 4
rand:
	push {lr}
	sub sp,sp, #4
.L5:
	movw r0,#:lower16:staticvalue
	movt r0,#:upper16:staticvalue
	ldr r1,[r0,#0]
	movw r0,#:lower16:seed
	movt r0,#:upper16:seed
	ldr r0,[r0,#0]
	mul r1,r1,r0
	movw r0,#:lower16:seed
	movt r0,#:upper16:seed
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r1,r1,r0
	movw r0,#:lower16:staticvalue
	movt r0,#:upper16:staticvalue
	str r1,[r0,#0]
	movw r0,#:lower16:staticvalue
	movt r0,#:upper16:staticvalue
	ldr r2,[r0,#0]
	movw r0,#:lower16:seed
	movt r0,#:upper16:seed
	add r0,r0, #8
	ldr r0,[r0,#0]
	sdiv r1,r2,r0
	mul r1,r1,r0
	sub r1,r2,r1
	movw r0,#:lower16:staticvalue
	movt r0,#:upper16:staticvalue
	str r1,[r0,#0]
	movw r0,#:lower16:staticvalue
	movt r0,#:upper16:staticvalue
	ldr r1,[r0,#0]
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L6
	beq .L7
.L6:
	movw r0,#:lower16:seed
	movt r0,#:upper16:seed
	add r0,r0, #8
	ldr r1,[r0,#0]
	movw r0,#:lower16:staticvalue
	movt r0,#:upper16:staticvalue
	ldr r0,[r0,#0]
	add r1,r1,r0
	movw r0,#:lower16:staticvalue
	movt r0,#:upper16:staticvalue
	str r1,[r0,#0]
.L7:
	movw r0,#:lower16:staticvalue
	movt r0,#:upper16:staticvalue
	ldr r0,[r0,#0]
	add sp,sp, #4
	pop {pc}
@ spilled Size: 0
@ stack Size: 148
set:
	push {lr}
	sub sp,sp, #148
.L8:
	str r0,[sp,#0]
	str r1,[sp,#4]
	str r2,[sp,#8]
	add r0,sp, #48
	mov r1,#124
	bl .memset
	mov r0,#1
	str r0,[sp,#12]
	ldr r1,[sp,#12]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#16]
	ldr r1,[sp,#16]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#20]
	ldr r1,[sp,#20]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#24]
	ldr r1,[sp,#24]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#28]
	ldr r1,[sp,#28]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#32]
	ldr r1,[sp,#32]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#36]
	ldr r1,[sp,#36]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#40]
	ldr r1,[sp,#40]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#44]
	ldr r1,[sp,#44]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#48]
	ldr r1,[sp,#48]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#52]
	mov r0,#10
	str r0,[sp,#136]
.L9:
	ldr r1,[sp,#136]
	mov r0,#30
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L10
	beq .L11
.L10:
	ldr r1,[sp,#136]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#136]
	ldr r1,[sp,#136]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r0,#4
	add r1,sp, #12
	mla r0,r0,r2,r1
	ldr r2,[sp,#136]
	mov r1,#1
	sub r2,r2,r1
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	mov r2,#4
	add r1,sp, #12
	mla r1,r2,r3,r1
	ldr r2,[r1,#0]
	mov r1,#2
	mul r1,r2,r1
	str r1,[r0,#0]
	b .L9
.L11:
	mov r0,#0
	str r0,[sp,#140]
	ldr r1,[sp,#4]
	mov r0,#30
	sdiv r1,r1,r0
	mov r0,#10000
	cmp r1,r0
	mov r0,#0
	movge r0,#1
	cmp r0,#0
	bne .L12
	beq .L13
.L12:
	mov r0,#0
	add sp,sp, #148
	pop {pc}
.L13:
	ldr r2,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#30
	sdiv r1,r1,r0
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	ldr r3,[sp,#4]
	mov r1,#30
	sdiv r2,r3,r1
	mul r2,r2,r1
	sub r2,r3,r2
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	mov r2,#4
	add r1,sp, #12
	mla r1,r2,r3,r1
	ldr r1,[r1,#0]
	sdiv r2,r0,r1
	mov r0,#2
	sdiv r1,r2,r0
	mul r1,r1,r0
	sub r1,r2,r1
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r0,#0
	movne r0,#1
	cmp r0,#0
	bne .L14
	beq .L20
.L14:
	ldr r2,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#30
	sdiv r1,r1,r0
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	ldr r3,[sp,#4]
	mov r1,#30
	sdiv r2,r3,r1
	mul r2,r2,r1
	sub r2,r3,r2
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	mov r2,#4
	add r1,sp, #12
	mla r1,r2,r3,r1
	ldr r1,[r1,#0]
	sdiv r2,r0,r1
	mov r0,#2
	sdiv r1,r2,r0
	mul r1,r1,r0
	sub r1,r2,r1
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L15
	beq .L17
.L15:
	ldr r1,[sp,#8]
	mov r0,#1
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L16
	beq .L17
.L16:
	ldr r2,[sp,#4]
	mov r0,#30
	sdiv r1,r2,r0
	mul r1,r1,r0
	sub r1,r2,r1
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r0,#4
	add r1,sp, #12
	mla r0,r0,r2,r1
	ldr r0,[r0,#0]
	str r0,[sp,#140]
.L17:
	ldr r2,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#30
	sdiv r1,r1,r0
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	ldr r3,[sp,#4]
	mov r1,#30
	sdiv r2,r3,r1
	mul r2,r2,r1
	sub r2,r3,r2
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	mov r2,#4
	add r1,sp, #12
	mla r1,r2,r3,r1
	ldr r1,[r1,#0]
	sdiv r2,r0,r1
	mov r0,#2
	sdiv r1,r2,r0
	mul r1,r1,r0
	sub r1,r2,r1
	mov r0,#1
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L18
	beq .L20
.L18:
	ldr r1,[sp,#8]
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L19
	beq .L20
.L19:
	ldr r0,[sp,#140]
	ldr r3,[sp,#4]
	mov r1,#30
	sdiv r2,r3,r1
	mul r2,r2,r1
	sub r2,r3,r2
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	mov r2,#4
	add r1,sp, #12
	mla r1,r2,r3,r1
	ldr r1,[r1,#0]
	sub r0,r0,r1
	str r0,[sp,#140]
.L20:
	ldr r2,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#30
	sdiv r1,r1,r0
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r3,[sp,#0]
	ldr r2,[sp,#4]
	mov r1,#30
	sdiv r2,r2,r1
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#4
	mla r1,r1,r2,r3
	ldr r2,[r1,#0]
	ldr r1,[sp,#140]
	add r1,r2,r1
	str r1,[r0,#0]
	mov r0,#0
	add sp,sp, #148
	pop {pc}
