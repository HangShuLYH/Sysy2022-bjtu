.arch armv7ve
.arm
.fpu neon
.text
.global main
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
	bx lr
@ spilled Size: 0
@ stack Size: 112
main:
	push {r4,lr}
	sub sp,sp, #112
	bl .init
.L1:
	mov r0,#3
	str r0,[sp,#0]
	mov r0,#7
	str r0,[sp,#4]
	mov r0,#5
	str r0,[sp,#8]
	mov r0,#6
	str r0,[sp,#12]
	mov r0,#1
	str r0,[sp,#16]
	mov r0,#0
	str r0,[sp,#20]
	mov r0,#3
	str r0,[sp,#24]
	mov r0,#5
	str r0,[sp,#28]
	mov r0,#4
	str r0,[sp,#32]
	mov r0,#2
	str r0,[sp,#36]
	mov r0,#7
	str r0,[sp,#40]
	mov r0,#9
	str r0,[sp,#44]
	mov r0,#8
	str r0,[sp,#48]
	mov r0,#1
	str r0,[sp,#52]
	mov r0,#4
	str r0,[sp,#56]
	mov r0,#6
	str r0,[sp,#60]
	ldr r1,[sp,#0]
	ldr r0,[sp,#4]
	add r1,r1,r0
	ldr r0,[sp,#8]
	add r1,r1,r0
	ldr r0,[sp,#12]
	add r1,r1,r0
	ldr r0,[sp,#16]
	add r1,r1,r0
	ldr r0,[sp,#20]
	add r1,r1,r0
	ldr r0,[sp,#24]
	add r1,r1,r0
	ldr r0,[sp,#28]
	add r0,r1,r0
	str r0,[sp,#64]
	ldr r1,[sp,#32]
	ldr r0,[sp,#36]
	add r1,r1,r0
	ldr r0,[sp,#40]
	add r1,r1,r0
	ldr r0,[sp,#44]
	add r1,r1,r0
	ldr r0,[sp,#48]
	add r1,r1,r0
	ldr r0,[sp,#52]
	add r1,r1,r0
	ldr r0,[sp,#56]
	add r1,r1,r0
	ldr r0,[sp,#60]
	add r0,r1,r0
	str r0,[sp,#68]
	ldr r4,[sp,#64]
	bl foo
	add r0,r4,r0
	str r0,[sp,#64]
	mov r0,#4
	str r0,[sp,#72]
	mov r0,#7
	str r0,[sp,#76]
	mov r0,#2
	str r0,[sp,#80]
	mov r0,#5
	str r0,[sp,#84]
	mov r0,#8
	str r0,[sp,#88]
	mov r0,#0
	str r0,[sp,#92]
	mov r0,#6
	str r0,[sp,#96]
	mov r0,#3
	str r0,[sp,#100]
	ldr r4,[sp,#68]
	bl foo
	add r0,r4,r0
	str r0,[sp,#68]
	ldr r0,[sp,#32]
	str r0,[sp,#0]
	ldr r0,[sp,#36]
	str r0,[sp,#4]
	ldr r0,[sp,#40]
	str r0,[sp,#8]
	ldr r0,[sp,#44]
	str r0,[sp,#12]
	ldr r0,[sp,#48]
	str r0,[sp,#16]
	ldr r0,[sp,#52]
	str r0,[sp,#20]
	ldr r0,[sp,#56]
	str r0,[sp,#24]
	ldr r0,[sp,#60]
	str r0,[sp,#28]
	ldr r1,[sp,#72]
	ldr r0,[sp,#76]
	add r1,r1,r0
	ldr r0,[sp,#80]
	add r1,r1,r0
	ldr r0,[sp,#84]
	add r1,r1,r0
	ldr r0,[sp,#88]
	add r1,r1,r0
	ldr r0,[sp,#92]
	add r1,r1,r0
	ldr r0,[sp,#96]
	add r1,r1,r0
	ldr r0,[sp,#100]
	add r0,r1,r0
	str r0,[sp,#104]
	ldr r1,[sp,#64]
	ldr r0,[sp,#68]
	add r1,r1,r0
	ldr r0,[sp,#104]
	add r0,r1,r0
	str r0,[sp,#108]
	ldr r0,[sp,#108]
	bl putint
	mov r0,#10
	bl putch
	mov r0,#0
	add sp,sp, #112
	pop {r4,pc}
@ spilled Size: 0
@ stack Size: 140
foo:
	push {lr}
	sub sp,sp, #140
.L2:
	add r0,sp, #0
	mov r1,#64
	bl .memset
	mov r0,#0
	str r0,[sp,#0]
	mov r0,#1
	str r0,[sp,#4]
	mov r0,#2
	str r0,[sp,#8]
	mov r0,#3
	str r0,[sp,#12]
	mov r0,#0
	str r0,[sp,#16]
	mov r0,#1
	str r0,[sp,#20]
	mov r0,#2
	str r0,[sp,#24]
	mov r0,#3
	str r0,[sp,#28]
	mov r0,#0
	str r0,[sp,#32]
	mov r0,#1
	str r0,[sp,#36]
	mov r0,#2
	str r0,[sp,#40]
	mov r0,#3
	str r0,[sp,#44]
	mov r0,#0
	str r0,[sp,#48]
	mov r0,#1
	str r0,[sp,#52]
	mov r0,#2
	str r0,[sp,#56]
	mov r0,#3
	str r0,[sp,#60]
	mov r0,#3
	str r0,[sp,#64]
	mov r0,#7
	str r0,[sp,#68]
	mov r0,#5
	str r0,[sp,#72]
	mov r0,#6
	str r0,[sp,#76]
	mov r0,#1
	str r0,[sp,#80]
	mov r0,#0
	str r0,[sp,#84]
	mov r0,#3
	str r0,[sp,#88]
	mov r0,#5
	str r0,[sp,#92]
	mov r0,#4
	str r0,[sp,#96]
	mov r0,#2
	str r0,[sp,#100]
	mov r0,#7
	str r0,[sp,#104]
	mov r0,#9
	str r0,[sp,#108]
	mov r0,#8
	str r0,[sp,#112]
	mov r0,#1
	str r0,[sp,#116]
	mov r0,#4
	str r0,[sp,#120]
	mov r0,#6
	str r0,[sp,#124]
	ldr r1,[sp,#64]
	ldr r0,[sp,#68]
	add r1,r1,r0
	ldr r0,[sp,#72]
	add r1,r1,r0
	ldr r0,[sp,#76]
	add r1,r1,r0
	ldr r0,[sp,#80]
	add r1,r1,r0
	ldr r0,[sp,#84]
	add r1,r1,r0
	ldr r0,[sp,#88]
	add r1,r1,r0
	ldr r0,[sp,#92]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#96]
	ldr r0,[sp,#100]
	add r1,r1,r0
	ldr r0,[sp,#104]
	add r1,r1,r0
	ldr r0,[sp,#108]
	add r1,r1,r0
	ldr r0,[sp,#112]
	add r1,r1,r0
	ldr r0,[sp,#116]
	add r1,r1,r0
	ldr r0,[sp,#120]
	add r1,r1,r0
	ldr r0,[sp,#124]
	add r0,r1,r0
	str r0,[sp,#132]
	ldr r1,[sp,#128]
	ldr r0,[sp,#132]
	add r3,r1,r0
	ldr r1,[sp,#64]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	mov r1,#4
	add r0,sp, #0
	mla r0,r1,r2,r0
	ldr r0,[r0,#0]
	add r0,r3,r0
	add sp,sp, #140
	pop {pc}
