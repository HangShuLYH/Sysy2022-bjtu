.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {r4,r5,r6,lr}
	sub sp,sp,#20
	bl .init
.L1:
	bl getint
	str r0,[sp,#12]
	ldr r0,[sp,#12]
	mov r1,#2
	mov r2,#3
	mov r3,#4
	mov r4,#5
	str r4,[sp,#0]
	mov r5,#6
	str r5,[sp,#4]
	mov r6,#7
	str r6,[sp,#8]
	bl add2
	ldr r0,[sp,#12]
	str r0,[sp,#16]
	mov r0,#14
	bl _sysy_starttime
	mov r0,#15
	bl _sysy_stoptime
	mov r0,#0
	add sp,sp, #20
	pop {r4,r5,r6,pc}
add3:
	push {lr}
	sub sp,sp,#32
.L2:
	str r0,[sp,#0]
	str r1,[sp,#4]
	str r2,[sp,#8]
	str r3,[sp,#12]
	mov r0,#0
	add sp,sp, #32
	pop {pc}
add2:
	push {r4,r5,r6,lr}
	sub sp,sp,#48
.L3:
	str r0,[sp,#12]
	str r1,[sp,#16]
	str r2,[sp,#20]
	str r3,[sp,#24]
	ldr r2,[sp,#12]
	ldr r1,[sp,#16]
	add r2,r2,r1
	ldr r1,[sp,#20]
	add r2,r2,r1
	ldr r1,[sp,#24]
	add r2,r2,r1
	ldr r1,[sp,#60]
	add r2,r2,r1
	ldr r1,[sp,#64]
	add r2,r2,r1
	ldr r1,[sp,#68]
	add r1,r2,r1
	str r1,[sp,#40]
	ldr r0,[sp,#40]
	mov r1,#0
	mov r2,#0
	mov r3,#0
	mov r4,#0
	str r4,[sp,#0]
	mov r5,#0
	str r5,[sp,#4]
	mov r6,#0
	str r6,[sp,#8]
	bl add2
	str r0,[sp,#44]
	ldr r1,[sp,#44]
	add sp,sp, #48
	pop {r4,r5,r6,pc}
