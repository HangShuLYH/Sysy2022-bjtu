.arch armv7ve
.arm
.fpu neon
.text
.global main
.section .text
.memset:
	push {r5}
	mov r4,#0
	mov r5,#0
	mov r3,#8
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
	bx lr
@ spilled Size: 0
@ stack Size: 164
main:
	push {lr}
	sub sp,sp, #164
	bl .init
.L1:
	add r0,sp, #0
	mov r1,#32
	bl .memset
	add r0,sp, #128
	mov r1,#32
	bl .memset
	mov r0,#1
	str r0,[sp,#32]
	mov r0,#2
	str r0,[sp,#36]
	mov r0,#3
	str r0,[sp,#40]
	mov r0,#4
	str r0,[sp,#44]
	mov r0,#5
	str r0,[sp,#48]
	mov r0,#6
	str r0,[sp,#52]
	mov r0,#7
	str r0,[sp,#56]
	mov r0,#8
	str r0,[sp,#60]
	add r0,sp, #256
	mov r1,#32
	bl .memset
	mov r0,#1
	str r0,[sp,#64]
	mov r0,#2
	str r0,[sp,#68]
	mov r0,#3
	str r0,[sp,#72]
	mov r0,#4
	str r0,[sp,#76]
	mov r0,#5
	str r0,[sp,#80]
	mov r0,#6
	str r0,[sp,#84]
	mov r0,#7
	str r0,[sp,#88]
	mov r0,#8
	str r0,[sp,#92]
	add r0,sp, #384
	mov r1,#32
	bl .memset
	mov r0,#1
	str r0,[sp,#96]
	mov r0,#2
	str r0,[sp,#100]
	mov r0,#3
	str r0,[sp,#104]
	mov r0,#5
	str r0,[sp,#112]
	mov r0,#7
	str r0,[sp,#120]
	mov r0,#8
	str r0,[sp,#124]
	add r0,sp, #512
	mov r1,#32
	bl .memset
	ldr r0,[sp,#116]
	str r0,[sp,#128]
	ldr r0,[sp,#84]
	str r0,[sp,#132]
	mov r0,#3
	str r0,[sp,#136]
	mov r0,#4
	str r0,[sp,#140]
	mov r0,#5
	str r0,[sp,#144]
	mov r0,#6
	str r0,[sp,#148]
	mov r0,#7
	str r0,[sp,#152]
	mov r0,#8
	str r0,[sp,#156]
	ldr r1,[sp,#156]
	ldr r0,[sp,#128]
	add r1,r1,r0
	ldr r0,[sp,#132]
	add r1,r1,r0
	ldr r0,[sp,#16]
	add r0,r1,r0
	add sp,sp, #164
	pop {pc}
