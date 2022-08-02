.arch armv7ve
.arm
.fpu neon
.text
.global main
.section .bss
.align
s:
	.space 4
.section .text
.memset:
	push {r4}
	mov r2,#0
	mov r3,#0
	mov r4,#8
.memset8:
	sub r1,r1,#8
	cmp r1,#0
	blt .memset4
	strd r2,r3,[r0],r4
	bne .memset8
	b .memset_end
.memset4:
	str r2,[r0],#4
.memset_end:
	pop {r4}
	bx lr
.init:
.L0:
	mov r1,#0
	movw r0,#:lower16:s
	movt r0,#:upper16:s
	str r1,[r0,#0]
	bx lr
@ spilled Size: 0
@ stack Size: 20
main:
	push {lr}
	sub sp,sp, #20
	bl .init
.L1:
	movw r2,#0
	movt r2,#32768
	movw r1,#0
	movt r1,#32768
	mov r0,#0
	bl get_ans
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	movw r2,#1
	movt r2,#32768
	movw r1,#1
	movt r1,#32768
	bl get_ans
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	movw r2,#0
	movt r2,#32768
	movw r1,#0
	movt r1,#32768
	bl get_ans
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	movw r2,#65535
	movt r2,#32767
	movw r1,#0
	movt r1,#32768
	bl get_ans
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	movw r2,#1
	movt r2,#49152
	movw r1,#0
	movt r1,#49152
	bl get_ans
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	movw r2,#0
	movt r2,#32768
	movw r1,#0
	movt r1,#32768
	bl get_ans
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	movw r2,#65535
	movt r2,#32767
	movw r1,#0
	movt r1,#32768
	bl get_ans
	str r0,[sp,#0]
	movw r2,#65535
	movt r2,#32767
	movw r1,#1
	movt r1,#32768
	mov r0,#0
	bl get_ans
	str r0,[sp,#4]
	ldr r0,[sp,#4]
	movw r2,#65534
	movt r2,#32767
	movw r1,#1
	movt r1,#32768
	bl get_ans
	str r0,[sp,#4]
	ldr r0,[sp,#4]
	movw r2,#65534
	movt r2,#32767
	movw r1,#65535
	movt r1,#32767
	bl get_ans
	str r0,[sp,#4]
	ldr r0,[sp,#4]
	movw r2,#0
	movt r2,#49152
	movw r1,#0
	movt r1,#49152
	bl get_ans
	str r0,[sp,#4]
	movw r2,#0
	movt r2,#32768
	movw r1,#0
	movt r1,#32768
	mov r0,#0
	bl get_ans_se
	str r0,[sp,#8]
	ldr r0,[sp,#8]
	movw r2,#1
	movt r2,#32768
	movw r1,#1
	movt r1,#32768
	bl get_ans_se
	str r0,[sp,#8]
	ldr r0,[sp,#8]
	movw r2,#0
	movt r2,#32768
	movw r1,#0
	movt r1,#32768
	bl get_ans_se
	str r0,[sp,#8]
	ldr r0,[sp,#8]
	movw r2,#65535
	movt r2,#32767
	movw r1,#0
	movt r1,#32768
	bl get_ans_se
	str r0,[sp,#8]
	ldr r0,[sp,#8]
	movw r2,#1
	movt r2,#49152
	movw r1,#0
	movt r1,#49152
	bl get_ans_se
	str r0,[sp,#8]
	ldr r0,[sp,#8]
	movw r2,#0
	movt r2,#32768
	movw r1,#0
	movt r1,#32768
	bl get_ans_se
	str r0,[sp,#8]
	ldr r0,[sp,#8]
	movw r2,#65535
	movt r2,#32767
	movw r1,#0
	movt r1,#32768
	bl get_ans_se
	str r0,[sp,#8]
	movw r2,#65535
	movt r2,#32767
	movw r1,#1
	movt r1,#32768
	mov r0,#0
	bl get_ans_se
	str r0,[sp,#12]
	ldr r0,[sp,#12]
	movw r2,#65534
	movt r2,#32767
	movw r1,#1
	movt r1,#32768
	bl get_ans_se
	str r0,[sp,#12]
	ldr r0,[sp,#12]
	movw r2,#65534
	movt r2,#32767
	movw r1,#65535
	movt r1,#32767
	bl get_ans_se
	str r0,[sp,#12]
	ldr r0,[sp,#12]
	movw r2,#0
	movt r2,#49152
	movw r1,#0
	movt r1,#49152
	bl get_ans_se
	str r0,[sp,#12]
	ldr r1,[sp,#0]
	ldr r0,[sp,#4]
	add r1,r1,r0
	ldr r0,[sp,#8]
	add r1,r1,r0
	ldr r0,[sp,#12]
	add r0,r1,r0
	add sp,sp, #20
	pop {pc}
@ spilled Size: 0
@ stack Size: 20
get_ans:
	push {lr}
	sub sp,sp, #20
.L2:
	str r0,[sp,#0]
	str r1,[sp,#4]
	str r2,[sp,#8]
	mov r0,#0
	str r0,[sp,#12]
	ldr r1,[sp,#4]
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L3
	beq .L4
.L3:
	mov r0,#1
	str r0,[sp,#12]
.L4:
	ldr r1,[sp,#0]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#0]
	ldr r1,[sp,#0]
	ldr r0,[sp,#12]
	add r0,r1,r0
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	add sp,sp, #20
	pop {pc}
@ spilled Size: 0
@ stack Size: 20
get_ans_se:
	push {lr}
	sub sp,sp, #20
.L5:
	str r0,[sp,#0]
	str r1,[sp,#4]
	str r2,[sp,#8]
	mov r0,#0
	str r0,[sp,#12]
	ldr r1,[sp,#4]
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L6
	beq .L7
.L6:
	mov r0,#1
	str r0,[sp,#12]
.L7:
	ldr r1,[sp,#0]
	mov r0,#2
	mul r0,r1,r0
	str r0,[sp,#0]
	ldr r1,[sp,#0]
	ldr r0,[sp,#12]
	add r0,r1,r0
	str r0,[sp,#0]
	movw r0,#:lower16:s
	movt r0,#:upper16:s
	ldr r1,[r0,#0]
	ldr r0,[sp,#0]
	add r1,r1,r0
	movw r0,#:lower16:s
	movt r0,#:upper16:s
	str r1,[r0,#0]
	ldr r0,[sp,#0]
	add sp,sp, #20
	pop {pc}
