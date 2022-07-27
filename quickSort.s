.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {r4,r5,lr}
	sub sp,sp, #112
	bl .init
.L1:
	bl getint
	str r0,[sp,#0]
.L2:
	ldr r1,[sp,#0]
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	movgt r0,#1
	cmp r0,#0
	bne .L3
	beq .L13
.L3:
	mov r0,#0
	str r0,[sp,#104]
.L4:
	ldr r1,[sp,#104]
	mov r0,#5
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L5
	beq .L9
.L5:
	mov r0,#0
	str r0,[sp,#108]
.L6:
	ldr r1,[sp,#108]
	mov r0,#5
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L7
	beq .L8
.L7:
	ldr r1,[sp,#108]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	ldr r1,[sp,#104]
	mov r0,#5
	mul r0,r1,r0
	add r1,r2,r0
	mov r0,#4
	add r4,sp, #4
	mla r5,r0,r1,r4
	bl getint
	str r0,[r5,#0]
	ldr r1,[sp,#108]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#108]
	b .L6
.L8:
	ldr r1,[sp,#104]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#104]
	b .L4
.L9:
	add r0,r4, #0
	bl model
	cmp r0,#0
	bne .L10
	beq .L11
.L10:
	mov r0,#99
	bl putch
	mov r0,#97
	bl putch
	mov r0,#116
	bl putch
	mov r0,#10
	bl putch
	b .L12
.L11:
	mov r0,#100
	bl putch
	mov r0,#111
	bl putch
	mov r0,#103
	bl putch
	mov r0,#10
	bl putch
.L12:
	ldr r1,[sp,#0]
	mov r0,#1
	sub r0,r1,r0
	str r0,[sp,#0]
	b .L2
.L13:
	mov r0,#0
	add sp,sp, #112
	pop {r4,r5,pc}
model:
	push {r4,lr}
	sub sp,sp, #4
.L14:
	str r0,[sp,#0]
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mov r0,#85
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mov r0,#23
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mvn r0,#81
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mvn r0,#102
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mvn r0,#122
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mov r0,#64
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mvn r0,#119
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mov r0,#50
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mvn r0,#58
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mov r0,#47
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mvn r0,#110
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mvn r0,#66
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mvn r0,#105
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mvn r0,#74
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mvn r0,#101
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mov r0,#34
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mvn r0,#38
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mov r0,#65
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mov r0,#47
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mov r0,#113
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mov r0,#110
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mov r0,#47
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mvn r0,#3
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mov r0,#80
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mov r0,#46
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mov r1,#39
	mul r4,r0,r1
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mvn r0,#105
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mov r0,#126
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mvn r0,#17
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mvn r0,#30
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mvn r0,#7
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mov r0,#47
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mvn r0,#3
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mov r0,#67
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mvn r0,#93
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mvn r0,#120
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mov r0,#7
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mvn r0,#20
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mvn r0,#59
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mvn r0,#42
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mov r0,#105
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mvn r0,#41
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mov r0,#87
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mov r0,#29
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mvn r0,#105
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mvn r0,#30
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mvn r0,#109
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mvn r0,#99
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mvn r0,#21
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mvn r0,#74
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mvn r0,#124
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mov r1,#77
	mul r0,r0,r1
	add r4,r4,r0
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mov r0,#26
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mov r0,#76
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mvn r0,#69
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mov r0,#29
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mvn r0,#94
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mov r0,#96
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mov r0,#52
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mvn r0,#67
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mvn r0,#4
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mov r0,#34
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mvn r0,#33
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mov r0,#102
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mov r0,#6
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mvn r0,#37
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mov r0,#27
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mov r0,#110
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mov r0,#116
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mov r0,#39
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mvn r0,#62
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mvn r0,#98
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mov r0,#65
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mov r0,#120
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mvn r0,#38
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mvn r0,#5
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mov r0,#94
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mov r1,#127
	mul r0,r0,r1
	add r4,r4,r0
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mvn r0,#22
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mvn r0,#62
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mov r0,#49
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mov r0,#50
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mov r0,#72
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mov r0,#85
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mvn r0,#29
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mov r0,#12
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mov r0,#125
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mvn r0,#116
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mvn r0,#64
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mvn r0,#66
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mov r0,#125
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mov r0,#110
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mvn r0,#30
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mvn r0,#122
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mov r0,#83
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mov r0,#122
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mov r0,#11
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mvn r0,#22
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mvn r0,#46
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mvn r0,#31
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mvn r0,#116
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mov r0,#95
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mov r0,#118
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mvn r1,#105
	mul r0,r0,r1
	add r4,r4,r0
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mov r0,#8
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mov r0,#82
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mvn r0,#103
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mov r0,#101
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mvn r0,#115
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mvn r0,#62
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mvn r0,#15
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mvn r0,#69
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mov r0,#125
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mov r0,#75
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mov r0,#66
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mvn r0,#95
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mvn r0,#100
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mvn r0,#113
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mov r0,#59
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mov r0,#12
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mov r0,#5
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mvn r0,#94
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mov r0,#116
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mvn r0,#92
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mov r0,#15
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mov r0,#79
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mov r0,#3
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mov r0,#49
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mvn r0,#123
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mvn r1,#2
	mul r0,r0,r1
	add r4,r4,r0
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mov r0,#81
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mov r0,#68
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mvn r0,#101
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mvn r0,#73
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mov r0,#121
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mvn r0,#14
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mov r0,#55
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mov r0,#101
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mvn r0,#12
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mvn r0,#61
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mov r0,#64
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mov r0,#114
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mov r0,#38
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mvn r0,#20
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mov r0,#112
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mov r0,#114
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mov r0,#112
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mvn r0,#9
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mvn r0,#15
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mvn r0,#49
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mvn r0,#111
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mvn r0,#115
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mvn r0,#53
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mov r0,#82
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mvn r0,#71
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mov r1,#32
	mul r0,r0,r1
	add r4,r4,r0
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mov r0,#15
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mvn r0,#76
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mov r0,#66
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mvn r0,#89
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mvn r0,#5
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mvn r0,#29
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mvn r0,#7
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mov r0,#81
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mov r0,#2
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mvn r0,#109
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mvn r0,#94
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mov r0,#59
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mov r0,#52
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mov r0,#15
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mov r0,#55
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mvn r0,#32
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mov r0,#14
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mov r0,#58
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mov r0,#67
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mov r0,#86
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mvn r0,#78
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mov r0,#48
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mvn r0,#12
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mvn r0,#14
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mov r0,#66
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mvn r1,#94
	mul r0,r0,r1
	add r4,r4,r0
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mov r0,#33
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mov r0,#82
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mov r0,#67
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mov r0,#30
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mvn r0,#1
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mov r0,#65
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mov r0,#120
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mvn r0,#12
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mov r0,#18
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mov r0,#5
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mov r0,#104
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mvn r0,#118
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mvn r0,#6
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mov r0,#71
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mov r0,#107
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mov r0,#24
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mov r0,#82
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mvn r0,#95
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mvn r0,#103
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mvn r0,#120
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mov r0,#65
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mov r0,#97
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mov r0,#83
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mov r0,#46
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mvn r0,#83
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mvn r1,#49
	mul r0,r0,r1
	add r4,r4,r0
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mvn r0,#28
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mov r0,#7
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mvn r0,#69
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mov r0,#38
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mvn r0,#89
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mvn r0,#14
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mvn r0,#31
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mov r0,#37
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mov r0,#36
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mvn r0,#61
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mvn r0,#124
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mvn r0,#45
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mvn r0,#69
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mov r0,#37
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mvn r0,#72
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mvn r0,#33
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mvn r0,#86
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mvn r0,#74
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mov r0,#71
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mvn r0,#76
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mov r0,#53
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mov r0,#37
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mvn r0,#102
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mvn r0,#12
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mvn r0,#113
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mvn r1,#22
	mul r0,r0,r1
	add r4,r4,r0
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	mov r0,#67
	mul r2,r1,r0
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r1,[r0,#0]
	mov r0,#42
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #8
	ldr r1,[r0,#0]
	mov r0,#41
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #12
	ldr r1,[r0,#0]
	mvn r0,#122
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #16
	ldr r1,[r0,#0]
	mvn r0,#91
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #20
	ldr r1,[r0,#0]
	mov r0,#10
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #24
	ldr r1,[r0,#0]
	mvn r0,#76
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #28
	ldr r1,[r0,#0]
	mov r0,#75
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #32
	ldr r1,[r0,#0]
	mov r0,#96
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #36
	ldr r1,[r0,#0]
	mvn r0,#50
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #40
	ldr r1,[r0,#0]
	mov r0,#109
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #44
	ldr r1,[r0,#0]
	mvn r0,#73
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #48
	ldr r1,[r0,#0]
	mvn r0,#6
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #52
	ldr r1,[r0,#0]
	mvn r0,#121
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #56
	ldr r1,[r0,#0]
	mov r0,#67
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #60
	ldr r1,[r0,#0]
	mov r0,#47
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #64
	ldr r1,[r0,#0]
	mov r0,#22
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #68
	ldr r1,[r0,#0]
	mvn r0,#67
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #72
	ldr r1,[r0,#0]
	mov r0,#38
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #76
	ldr r1,[r0,#0]
	mov r0,#29
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #80
	ldr r1,[r0,#0]
	mov r0,#115
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #84
	ldr r1,[r0,#0]
	mvn r0,#120
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #88
	ldr r1,[r0,#0]
	mov r0,#36
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #92
	ldr r1,[r0,#0]
	mvn r0,#48
	mul r0,r1,r0
	add r2,r2,r0
	ldr r0,[sp,#0]
	add r0,r0, #96
	ldr r1,[r0,#0]
	mov r0,#85
	mul r0,r1,r0
	add r0,r2,r0
	bl relu_reg
	mov r1,#46
	mul r0,r0,r1
	add r1,r4,r0
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	movgt r0,#1
	cmp r0,#0
	bne .L15
	beq .L16
.L15:
	mov r0,#1
	add sp,sp, #4
	pop {r4,pc}
.L16:
	mov r0,#0
	add sp,sp, #4
	pop {r4,pc}
relu_reg:
	push {lr}
	sub sp,sp, #4
.L17:
	str r0,[sp,#0]
	ldr r1,[sp,#0]
	mov r0,#127
	cmp r1,r0
	mov r0,#0
	movgt r0,#1
	cmp r0,#0
	bne .L18
	beq .L19
.L18:
	mov r0,#127
	add sp,sp, #4
	pop {pc}
.L19:
	ldr r1,[sp,#0]
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L20
	beq .L21
.L20:
	mov r0,#0
	add sp,sp, #4
	pop {pc}
.L21:
	ldr r0,[sp,#0]
	add sp,sp, #4
	pop {pc}
