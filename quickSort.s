.arch armv7ve
.arm
.section .data
.align
maxn:
	.4byte 18
.align
mod:
	.4byte 1000000007
.section .bss
.align
dp:
	.space 52907904
.align
list:
	.space 800
.align
cns:
	.space 80
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {r4,r5,lr}
	sub sp,sp, #40
	bl .init
.L1:
	bl getint
	str r0,[sp,#8]
	mov r0,#0
	str r0,[sp,#12]
.L2:
	ldr r1,[sp,#12]
	mov r0,#18
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L3
	beq .L19
.L3:
	mov r0,#0
	str r0,[sp,#16]
.L4:
	ldr r1,[sp,#16]
	mov r0,#18
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L5
	beq .L18
.L5:
	mov r0,#0
	str r0,[sp,#20]
.L6:
	ldr r1,[sp,#20]
	mov r0,#18
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L7
	beq .L17
.L7:
	mov r0,#0
	str r0,[sp,#24]
.L8:
	ldr r1,[sp,#24]
	mov r0,#18
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L9
	beq .L16
.L9:
	mov r0,#0
	str r0,[sp,#28]
.L10:
	ldr r1,[sp,#28]
	mov r0,#18
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L11
	beq .L15
.L11:
	mov r0,#0
	str r0,[sp,#32]
.L12:
	ldr r1,[sp,#32]
	mov r0,#7
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L13
	beq .L14
.L13:
	ldr r1,[sp,#32]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	ldr r1,[sp,#28]
	mov r0,#7
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#24]
	mov r0,#126
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#20]
	mov r0,#2268
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#16]
	mov r0,#40824
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#12]
	movw r0,#13936
	movt r0,#11
	mul r0,r1,r0
	add r2,r2,r0
	movw r1,#:lower16:dp
	movt r1,#:upper16:dp
	mov r0,#4
	mla r1,r0,r2,r1
	mvn r0,#0
	str r0,[r1,#0]
	ldr r1,[sp,#32]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#32]
	b .L12
.L14:
	ldr r1,[sp,#28]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#28]
	b .L10
.L15:
	ldr r1,[sp,#24]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#24]
	b .L8
.L16:
	ldr r1,[sp,#20]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#20]
	b .L6
.L17:
	ldr r1,[sp,#16]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#16]
	b .L4
.L18:
	ldr r1,[sp,#12]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#12]
	b .L2
.L19:
	mov r0,#0
	str r0,[sp,#12]
.L20:
	ldr r1,[sp,#12]
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L21
	beq .L22
.L21:
	ldr r1,[sp,#12]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	movw r4,#:lower16:list
	movt r4,#:upper16:list
	mov r0,#4
	mla r4,r0,r1,r4
	bl getint
	str r0,[r4,#0]
	ldr r1,[sp,#12]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	movw r1,#:lower16:list
	movt r1,#:upper16:list
	mov r0,#4
	mla r1,r0,r2,r1
	ldr r1,[r1,#0]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	movw r0,#:lower16:cns
	movt r0,#:upper16:cns
	mov r1,#4
	mla r0,r1,r2,r0
	ldr r2,[sp,#12]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	movw r2,#:lower16:list
	movt r2,#:upper16:list
	mov r1,#4
	mla r2,r1,r3,r2
	ldr r2,[r2,#0]
	mov r1,#1
	mul r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	movw r2,#:lower16:cns
	movt r2,#:upper16:cns
	mov r1,#4
	mla r2,r1,r3,r2
	ldr r2,[r2,#0]
	mov r1,#1
	add r1,r2,r1
	str r1,[r0,#0]
	ldr r1,[sp,#12]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#12]
	b .L20
.L22:
	movw r0,#:lower16:cns
	movt r0,#:upper16:cns
	add r0,r0, #4
	ldr r0,[r0,#0]
	movw r1,#:lower16:cns
	movt r1,#:upper16:cns
	add r1,r1, #8
	ldr r1,[r1,#0]
	movw r2,#:lower16:cns
	movt r2,#:upper16:cns
	add r2,r2, #12
	ldr r2,[r2,#0]
	movw r3,#:lower16:cns
	movt r3,#:upper16:cns
	add r3,r3, #16
	ldr r3,[r3,#0]
	movw r4,#:lower16:cns
	movt r4,#:upper16:cns
	add r4,r4, #20
	ldr r4,[r4,#0]
	str r4,[sp,#0]
	mov r5,#0
	str r5,[sp,#4]
	bl dfs
	str r0,[sp,#36]
	ldr r0,[sp,#36]
	bl putint
	ldr r0,[sp,#36]
	add sp,sp, #40
	pop {r4,r5,pc}
dfs:
	push {r4,r5,r6,r7,lr}
	sub sp,sp, #36
.L23:
	str r0,[sp,#8]
	str r1,[sp,#12]
	str r2,[sp,#16]
	str r3,[sp,#20]
	ldr r1,[sp,#60]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	ldr r1,[sp,#56]
	mov r0,#7
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#20]
	mov r0,#126
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#16]
	mov r0,#2268
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#12]
	mov r0,#40824
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#8]
	movw r0,#13936
	movt r0,#11
	mul r0,r1,r0
	add r2,r2,r0
	movw r1,#:lower16:dp
	movt r1,#:upper16:dp
	mov r0,#4
	mla r1,r0,r2,r1
	ldr r1,[r1,#0]
	mvn r0,#0
	cmp r1,r0
	mov r0,#0
	movne r0,#1
	cmp r0,#0
	bne .L24
	beq .L25
.L24:
	ldr r1,[sp,#60]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	ldr r1,[sp,#56]
	mov r0,#7
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#20]
	mov r0,#126
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#16]
	mov r0,#2268
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#12]
	mov r0,#40824
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#8]
	movw r0,#13936
	movt r0,#11
	mul r0,r1,r0
	add r2,r2,r0
	movw r1,#:lower16:dp
	movt r1,#:upper16:dp
	mov r0,#4
	mla r1,r0,r2,r1
	ldr r0,[r1,#0]
	add sp,sp, #36
	pop {r4,r5,r6,r7,pc}
.L25:
	ldr r1,[sp,#8]
	ldr r0,[sp,#12]
	add r1,r1,r0
	ldr r0,[sp,#16]
	add r1,r1,r0
	ldr r0,[sp,#20]
	add r1,r1,r0
	ldr r0,[sp,#56]
	add r1,r1,r0
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L26
	beq .L27
.L26:
	mov r0,#1
	add sp,sp, #36
	pop {r4,r5,r6,r7,pc}
.L27:
	mov r0,#0
	str r0,[sp,#32]
	ldr r0,[sp,#8]
	cmp r0,#0
	bne .L28
	beq .L29
.L28:
	ldr r6,[sp,#32]
	ldr r4,[sp,#8]
	ldr r0,[sp,#60]
	mov r1,#2
	bl equal
	sub r4,r4,r0
	ldr r1,[sp,#8]
	mov r0,#1
	sub r0,r1,r0
	ldr r1,[sp,#12]
	ldr r2,[sp,#16]
	ldr r3,[sp,#20]
	ldr r5,[sp,#56]
	str r5,[sp,#0]
	mov r5,#1
	str r5,[sp,#4]
	bl dfs
	mul r0,r4,r0
	add r2,r6,r0
	movw r1,#51719
	movt r1,#15258
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	str r0,[sp,#32]
.L29:
	ldr r0,[sp,#12]
	cmp r0,#0
	bne .L30
	beq .L31
.L30:
	ldr r6,[sp,#32]
	ldr r4,[sp,#12]
	ldr r0,[sp,#60]
	mov r1,#3
	bl equal
	sub r4,r4,r0
	ldr r1,[sp,#8]
	mov r0,#1
	add r0,r1,r0
	ldr r2,[sp,#12]
	mov r1,#1
	sub r1,r2,r1
	ldr r2,[sp,#16]
	ldr r3,[sp,#20]
	ldr r5,[sp,#56]
	str r5,[sp,#0]
	mov r5,#2
	str r5,[sp,#4]
	bl dfs
	mul r0,r4,r0
	add r2,r6,r0
	movw r1,#51719
	movt r1,#15258
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	str r0,[sp,#32]
.L31:
	ldr r0,[sp,#16]
	cmp r0,#0
	bne .L32
	beq .L33
.L32:
	ldr r6,[sp,#32]
	ldr r4,[sp,#16]
	ldr r0,[sp,#60]
	mov r1,#4
	bl equal
	sub r4,r4,r0
	ldr r0,[sp,#8]
	ldr r2,[sp,#12]
	mov r1,#1
	add r1,r2,r1
	ldr r3,[sp,#16]
	mov r2,#1
	sub r2,r3,r2
	ldr r3,[sp,#20]
	ldr r5,[sp,#56]
	str r5,[sp,#0]
	mov r5,#3
	str r5,[sp,#4]
	bl dfs
	mul r0,r4,r0
	add r2,r6,r0
	movw r1,#51719
	movt r1,#15258
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	str r0,[sp,#32]
.L33:
	ldr r0,[sp,#20]
	cmp r0,#0
	bne .L34
	beq .L35
.L34:
	ldr r6,[sp,#32]
	ldr r4,[sp,#20]
	ldr r0,[sp,#60]
	mov r1,#5
	bl equal
	sub r4,r4,r0
	ldr r0,[sp,#8]
	ldr r1,[sp,#12]
	ldr r3,[sp,#16]
	mov r2,#1
	add r2,r3,r2
	ldr r5,[sp,#20]
	mov r3,#1
	sub r3,r5,r3
	ldr r5,[sp,#56]
	str r5,[sp,#0]
	mov r5,#4
	str r5,[sp,#4]
	bl dfs
	mul r0,r4,r0
	add r2,r6,r0
	movw r1,#51719
	movt r1,#15258
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	str r0,[sp,#32]
.L35:
	ldr r0,[sp,#56]
	cmp r0,#0
	bne .L36
	beq .L37
.L36:
	ldr r6,[sp,#32]
	ldr r4,[sp,#56]
	ldr r0,[sp,#8]
	ldr r1,[sp,#12]
	ldr r2,[sp,#16]
	ldr r5,[sp,#20]
	mov r3,#1
	add r3,r5,r3
	ldr r7,[sp,#56]
	mov r5,#1
	sub r5,r7,r5
	str r5,[sp,#0]
	mov r5,#5
	str r5,[sp,#4]
	bl dfs
	mul r0,r4,r0
	add r2,r6,r0
	movw r1,#51719
	movt r1,#15258
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	str r0,[sp,#32]
.L37:
	ldr r1,[sp,#60]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	ldr r1,[sp,#56]
	mov r0,#7
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#20]
	mov r0,#126
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#16]
	mov r0,#2268
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#12]
	mov r0,#40824
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#8]
	movw r0,#13936
	movt r0,#11
	mul r0,r1,r0
	add r1,r2,r0
	movw r3,#:lower16:dp
	movt r3,#:upper16:dp
	mov r0,#4
	mla r3,r0,r1,r3
	ldr r2,[sp,#32]
	movw r1,#51719
	movt r1,#15258
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	str r0,[r3,#0]
	ldr r1,[sp,#60]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	ldr r1,[sp,#56]
	mov r0,#7
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#20]
	mov r0,#126
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#16]
	mov r0,#2268
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#12]
	mov r0,#40824
	mul r0,r1,r0
	add r2,r2,r0
	ldr r1,[sp,#8]
	movw r0,#13936
	movt r0,#11
	mul r0,r1,r0
	add r2,r2,r0
	movw r1,#:lower16:dp
	movt r1,#:upper16:dp
	mov r0,#4
	mla r1,r0,r2,r1
	ldr r0,[r1,#0]
	add sp,sp, #36
	pop {r4,r5,r6,r7,pc}
equal:
	push {lr}
	sub sp,sp, #8
.L38:
	str r0,[sp,#0]
	str r1,[sp,#4]
	ldr r1,[sp,#0]
	ldr r0,[sp,#4]
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L39
	beq .L40
.L39:
	mov r0,#1
	add sp,sp, #8
	pop {pc}
.L40:
	mov r0,#0
	add sp,sp, #8
	pop {pc}
