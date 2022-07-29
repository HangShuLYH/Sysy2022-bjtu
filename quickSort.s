.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
@ spilled Size: 40
@ stack Size: 412
main:
	push {r4,r5,r8,r9,r10,r11,lr}
	sub sp,sp, #412
	bl .init
.L1:
	bl getint
	str r0,[sp,#372]
	bl getint
	str r0,[sp,#376]
	bl getint
	mov r11,r0
	bl getint
	mov r10,r0
	bl getint
	mov r9,r0
	bl getint
	mov r8,r0
	bl getint
	str r0,[sp,#404]
	bl getint
	str r0,[sp,#408]
	bl getint
	mov r5,r0
	bl getint
	mov r4,r0
	bl getint
	str r0,[sp,#380]
	bl getint
	str r0,[sp,#384]
	bl getint
	str r0,[sp,#388]
	bl getint
	str r0,[sp,#392]
	bl getint
	str r0,[sp,#396]
	bl getint
	str r0,[sp,#400]
	ldr r0,[sp,#372]
	ldr r1,[sp,#376]
	mov r2,r11
	mov r3,r10
	str r9,[sp,#0]
	str r8,[sp,#4]
	ldr r0,[sp,#404]
	str r0,[sp,#8]
	ldr r0,[sp,#408]
	str r0,[sp,#12]
	str r5,[sp,#16]
	str r4,[sp,#20]
	ldr r0,[sp,#380]
	str r0,[sp,#24]
	ldr r0,[sp,#384]
	str r0,[sp,#28]
	ldr r0,[sp,#388]
	str r0,[sp,#32]
	ldr r0,[sp,#392]
	str r0,[sp,#36]
	ldr r0,[sp,#396]
	str r0,[sp,#40]
	ldr r0,[sp,#400]
	str r0,[sp,#44]
	bl param16
	str r0,[sp,#112]
	mov r0,#8848
	str r0,[sp,#116]
	mov r0,#0
	str r0,[sp,#120]
	mov r0,#0
	str r0,[sp,#124]
	mov r0,#0
	str r0,[sp,#128]
	mov r0,#0
	str r0,[sp,#132]
	mov r0,#0
	str r0,[sp,#136]
	mov r0,#0
	str r0,[sp,#140]
	mov r0,#0
	str r0,[sp,#144]
	mov r0,#0
	str r0,[sp,#148]
	mov r0,#0
	str r0,[sp,#152]
	mov r0,#0
	str r0,[sp,#156]
	mov r0,#0
	str r0,[sp,#160]
	mov r0,#0
	str r0,[sp,#164]
	mov r0,#0
	str r0,[sp,#168]
	mov r0,#0
	str r0,[sp,#172]
	mov r0,#0
	str r0,[sp,#176]
	mov r0,#0
	str r0,[sp,#180]
	mov r0,#0
	str r0,[sp,#184]
	mov r0,#0
	str r0,[sp,#188]
	mov r0,#0
	str r0,[sp,#192]
	mov r0,#0
	str r0,[sp,#196]
	mov r0,#0
	str r0,[sp,#200]
	mov r0,#0
	str r0,[sp,#204]
	mov r0,#0
	str r0,[sp,#208]
	mov r0,#0
	str r0,[sp,#212]
	mov r0,#0
	str r0,[sp,#216]
	mov r0,#0
	str r0,[sp,#220]
	mov r0,#0
	str r0,[sp,#224]
	mov r0,#0
	str r0,[sp,#228]
	mov r0,#0
	str r0,[sp,#232]
	mov r0,#0
	str r0,[sp,#236]
	mov r0,#0
	str r0,[sp,#240]
	mov r0,#0
	str r0,[sp,#244]
	mov r0,#0
	str r0,[sp,#248]
	mov r0,#0
	str r0,[sp,#252]
	mov r0,#0
	str r0,[sp,#256]
	mov r0,#0
	str r0,[sp,#260]
	mov r0,#0
	str r0,[sp,#264]
	mov r0,#0
	str r0,[sp,#268]
	mov r0,#0
	str r0,[sp,#272]
	mov r0,#0
	str r0,[sp,#276]
	mov r0,#0
	str r0,[sp,#280]
	mov r0,#0
	str r0,[sp,#284]
	mov r0,#0
	str r0,[sp,#288]
	mov r0,#0
	str r0,[sp,#292]
	mov r0,#0
	str r0,[sp,#296]
	mov r0,#0
	str r0,[sp,#300]
	mov r0,#0
	str r0,[sp,#304]
	mov r0,#0
	str r0,[sp,#308]
	mov r0,#0
	str r0,[sp,#312]
	mov r0,#0
	str r0,[sp,#316]
	mov r0,#0
	str r0,[sp,#320]
	mov r0,#0
	str r0,[sp,#324]
	mov r0,#0
	str r0,[sp,#328]
	mov r0,#0
	str r0,[sp,#332]
	mov r0,#0
	str r0,[sp,#336]
	mov r0,#0
	str r0,[sp,#340]
	mov r0,#0
	str r0,[sp,#344]
	mov r0,#0
	str r0,[sp,#348]
	mov r0,#0
	str r0,[sp,#352]
	mov r0,#0
	str r0,[sp,#356]
	mov r0,#0
	str r0,[sp,#360]
	mov r0,#0
	str r0,[sp,#364]
	mov r0,#1
	str r0,[sp,#368]
.L2:
	ldr r1,[sp,#368]
	mov r0,#32
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L3
	beq .L4
.L3:
	ldr r1,[sp,#368]
	mov r0,#2
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	add r3,sp, #112
	mla r0,r0,r1,r3
	ldr r2,[sp,#368]
	mov r1,#1
	sub r2,r2,r1
	mov r1,#2
	mul r2,r2,r1
	mov r1,#1
	add r2,r2,r1
	mov r1,#4
	add r3,sp, #112
	mla r1,r1,r2,r3
	ldr r2,[r1,#0]
	mov r1,#1
	sub r1,r2,r1
	str r1,[r0,#0]
	ldr r1,[sp,#368]
	mov r0,#2
	mul r1,r1,r0
	mov r0,#1
	add r1,r1,r0
	mov r0,#4
	add r3,sp, #112
	mla r0,r0,r1,r3
	ldr r2,[sp,#368]
	mov r1,#1
	sub r2,r2,r1
	mov r1,#2
	mul r2,r2,r1
	mov r1,#0
	add r2,r2,r1
	mov r1,#4
	add r3,sp, #112
	mla r1,r1,r2,r3
	ldr r2,[r1,#0]
	mov r1,#2
	sub r1,r2,r1
	str r1,[r0,#0]
	ldr r1,[sp,#368]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#368]
	b .L2
.L4:
	add r0,sp, #112
	add r1,sp, #120
	add r2,sp, #128
	add r3,sp, #136
	add r0,sp, #144
	str r0,[sp,#0]
	add r0,sp, #152
	str r0,[sp,#4]
	add r0,sp, #160
	str r0,[sp,#8]
	add r0,sp, #168
	str r0,[sp,#12]
	add r0,sp, #176
	str r0,[sp,#16]
	add r0,sp, #184
	str r0,[sp,#20]
	add r0,sp, #192
	str r0,[sp,#24]
	add r0,sp, #200
	str r0,[sp,#28]
	add r0,sp, #208
	str r0,[sp,#32]
	add r0,sp, #216
	str r0,[sp,#36]
	add r0,sp, #224
	str r0,[sp,#40]
	add r0,sp, #232
	str r0,[sp,#44]
	add r0,sp, #240
	str r0,[sp,#48]
	add r0,sp, #248
	str r0,[sp,#52]
	add r0,sp, #256
	str r0,[sp,#56]
	add r0,sp, #264
	str r0,[sp,#60]
	add r0,sp, #272
	str r0,[sp,#64]
	add r0,sp, #280
	str r0,[sp,#68]
	add r0,sp, #288
	str r0,[sp,#72]
	add r0,sp, #296
	str r0,[sp,#76]
	add r0,sp, #304
	str r0,[sp,#80]
	add r0,sp, #312
	str r0,[sp,#84]
	add r0,sp, #320
	str r0,[sp,#88]
	add r0,sp, #328
	str r0,[sp,#92]
	add r0,sp, #336
	str r0,[sp,#96]
	add r0,sp, #344
	str r0,[sp,#100]
	add r0,sp, #352
	str r0,[sp,#104]
	add r0,sp, #360
	str r0,[sp,#108]
	bl param32_arr
	bl putint
	mov r0,#10
	bl putch
	mov r0,#0
	add sp,sp, #412
	pop {r4,r5,r8,r9,r10,r11,pc}
@ spilled Size: 160
@ stack Size: 400
param16:
	push {r4,lr}
	sub sp,sp, #400
.L5:
	str r0,[sp,#112]
	str r1,[sp,#116]
	str r2,[sp,#120]
	str r3,[sp,#124]
	ldr r0,[sp,#112]
	str r0,[sp,#176]
	ldr r0,[sp,#116]
	str r0,[sp,#180]
	ldr r0,[sp,#120]
	str r0,[sp,#184]
	ldr r0,[sp,#124]
	str r0,[sp,#188]
	ldr r0,[sp,#408]
	str r0,[sp,#192]
	ldr r0,[sp,#412]
	str r0,[sp,#196]
	ldr r0,[sp,#416]
	str r0,[sp,#200]
	ldr r0,[sp,#420]
	str r0,[sp,#204]
	ldr r0,[sp,#424]
	str r0,[sp,#208]
	ldr r0,[sp,#428]
	str r0,[sp,#212]
	ldr r0,[sp,#432]
	str r0,[sp,#216]
	ldr r0,[sp,#436]
	str r0,[sp,#220]
	ldr r0,[sp,#440]
	str r0,[sp,#224]
	ldr r0,[sp,#444]
	str r0,[sp,#228]
	ldr r0,[sp,#448]
	str r0,[sp,#232]
	ldr r0,[sp,#452]
	str r0,[sp,#236]
	add r0,sp, #176
	mov r1,#16
	bl sort
	ldr r0,[sp,#176]
	ldr r1,[sp,#180]
	ldr r2,[sp,#184]
	ldr r3,[sp,#188]
	ldr r4,[sp,#192]
	str r4,[sp,#240]
	ldr r4,[sp,#196]
	str r4,[sp,#244]
	ldr r4,[sp,#200]
	str r4,[sp,#248]
	ldr r4,[sp,#204]
	str r4,[sp,#252]
	ldr r4,[sp,#208]
	str r4,[sp,#256]
	ldr r4,[sp,#212]
	str r4,[sp,#260]
	ldr r4,[sp,#216]
	str r4,[sp,#264]
	ldr r4,[sp,#220]
	str r4,[sp,#268]
	ldr r4,[sp,#224]
	str r4,[sp,#272]
	ldr r4,[sp,#228]
	str r4,[sp,#276]
	ldr r4,[sp,#232]
	str r4,[sp,#280]
	ldr r4,[sp,#236]
	str r4,[sp,#284]
	ldr r4,[sp,#112]
	str r4,[sp,#288]
	ldr r4,[sp,#116]
	str r4,[sp,#292]
	ldr r4,[sp,#120]
	str r4,[sp,#296]
	ldr r4,[sp,#124]
	str r4,[sp,#300]
	ldr r4,[sp,#408]
	str r4,[sp,#304]
	ldr r4,[sp,#412]
	str r4,[sp,#308]
	ldr r4,[sp,#416]
	str r4,[sp,#312]
	ldr r4,[sp,#420]
	str r4,[sp,#316]
	ldr r4,[sp,#424]
	str r4,[sp,#368]
	ldr r4,[sp,#428]
	str r4,[sp,#372]
	ldr r4,[sp,#432]
	str r4,[sp,#376]
	ldr r4,[sp,#436]
	str r4,[sp,#380]
	ldr r4,[sp,#440]
	str r4,[sp,#384]
	ldr r4,[sp,#444]
	str r4,[sp,#388]
	ldr r4,[sp,#448]
	str r4,[sp,#392]
	ldr r4,[sp,#452]
	str r4,[sp,#396]
	ldr r0,[sp,#240]
	str r0,[sp,#0]
	ldr r0,[sp,#244]
	str r0,[sp,#4]
	ldr r0,[sp,#248]
	str r0,[sp,#8]
	ldr r0,[sp,#252]
	str r0,[sp,#12]
	ldr r0,[sp,#256]
	str r0,[sp,#16]
	ldr r0,[sp,#260]
	str r0,[sp,#20]
	ldr r0,[sp,#264]
	str r0,[sp,#24]
	ldr r0,[sp,#268]
	str r0,[sp,#28]
	ldr r0,[sp,#272]
	str r0,[sp,#32]
	ldr r0,[sp,#276]
	str r0,[sp,#36]
	ldr r0,[sp,#280]
	str r0,[sp,#40]
	ldr r0,[sp,#284]
	str r0,[sp,#44]
	ldr r0,[sp,#288]
	str r0,[sp,#48]
	ldr r0,[sp,#292]
	str r0,[sp,#52]
	ldr r0,[sp,#296]
	str r0,[sp,#56]
	ldr r0,[sp,#300]
	str r0,[sp,#60]
	ldr r0,[sp,#304]
	str r0,[sp,#64]
	ldr r0,[sp,#308]
	str r0,[sp,#68]
	ldr r0,[sp,#312]
	str r0,[sp,#72]
	ldr r0,[sp,#316]
	str r0,[sp,#76]
	ldr r0,[sp,#368]
	str r0,[sp,#80]
	ldr r0,[sp,#372]
	str r0,[sp,#84]
	ldr r0,[sp,#376]
	str r0,[sp,#88]
	ldr r0,[sp,#380]
	str r0,[sp,#92]
	ldr r0,[sp,#384]
	str r0,[sp,#96]
	ldr r0,[sp,#388]
	str r0,[sp,#100]
	ldr r0,[sp,#392]
	str r0,[sp,#104]
	ldr r0,[sp,#396]
	str r0,[sp,#108]
	bl param32_rec
	add sp,sp, #400
	pop {r4,pc}
@ spilled Size: 0
@ stack Size: 132
param32_arr:
	push {lr}
	sub sp,sp, #132
.L6:
	str r0,[sp,#0]
	str r1,[sp,#4]
	str r2,[sp,#8]
	str r3,[sp,#12]
	ldr r0,[sp,#0]
	ldr r1,[r0,#0]
	ldr r0,[sp,#0]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#4]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#4]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#8]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#8]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#12]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#12]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#136]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#136]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#140]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#140]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#144]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#144]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#148]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#148]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#152]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#152]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#156]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#156]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#160]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#160]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#164]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#164]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#168]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#168]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#172]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#172]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#176]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#176]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#180]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#180]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#184]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#184]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#188]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#188]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#192]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#192]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#196]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#196]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#200]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#200]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#204]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#204]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#208]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#208]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#212]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#212]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#216]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#216]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#220]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#220]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#224]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#224]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#228]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#228]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#232]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#232]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#236]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#236]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#240]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#240]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r1,[sp,#128]
	ldr r0,[sp,#244]
	ldr r0,[r0,#0]
	add r1,r1,r0
	ldr r0,[sp,#244]
	add r0,r0, #4
	ldr r0,[r0,#0]
	add r0,r1,r0
	str r0,[sp,#128]
	ldr r0,[sp,#128]
	add sp,sp, #132
	pop {pc}
@ spilled Size: 152
@ stack Size: 392
param32_rec:
	push {r4,lr}
	sub sp,sp, #392
.L7:
	str r0,[sp,#112]
	str r1,[sp,#116]
	str r2,[sp,#120]
	str r3,[sp,#124]
	ldr r1,[sp,#112]
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L8
	beq .L9
.L8:
	ldr r0,[sp,#116]
	add sp,sp, #392
	pop {r4,pc}
.L9:
	ldr r1,[sp,#112]
	mov r0,#1
	sub r0,r1,r0
	ldr r2,[sp,#116]
	ldr r1,[sp,#120]
	add r3,r2,r1
	movw r2,#1
	movt r2,#15232
	sdiv r1,r3,r2
	mul r1,r1,r2
	sub r1,r3,r1
	ldr r2,[sp,#124]
	ldr r3,[sp,#400]
	ldr r4,[sp,#404]
	str r4,[sp,#240]
	ldr r4,[sp,#408]
	str r4,[sp,#244]
	ldr r4,[sp,#412]
	str r4,[sp,#248]
	ldr r4,[sp,#416]
	str r4,[sp,#252]
	ldr r4,[sp,#420]
	str r4,[sp,#256]
	ldr r4,[sp,#424]
	str r4,[sp,#260]
	ldr r4,[sp,#428]
	str r4,[sp,#264]
	ldr r4,[sp,#432]
	str r4,[sp,#268]
	ldr r4,[sp,#436]
	str r4,[sp,#272]
	ldr r4,[sp,#440]
	str r4,[sp,#276]
	ldr r4,[sp,#444]
	str r4,[sp,#280]
	ldr r4,[sp,#448]
	str r4,[sp,#284]
	ldr r4,[sp,#452]
	str r4,[sp,#288]
	ldr r4,[sp,#456]
	str r4,[sp,#292]
	ldr r4,[sp,#460]
	str r4,[sp,#296]
	ldr r4,[sp,#464]
	str r4,[sp,#300]
	ldr r4,[sp,#468]
	str r4,[sp,#304]
	ldr r4,[sp,#472]
	str r4,[sp,#308]
	ldr r4,[sp,#476]
	str r4,[sp,#312]
	ldr r4,[sp,#480]
	str r4,[sp,#360]
	ldr r4,[sp,#484]
	str r4,[sp,#364]
	ldr r4,[sp,#488]
	str r4,[sp,#368]
	ldr r4,[sp,#492]
	str r4,[sp,#372]
	ldr r4,[sp,#496]
	str r4,[sp,#376]
	ldr r4,[sp,#500]
	str r4,[sp,#380]
	ldr r4,[sp,#504]
	str r4,[sp,#384]
	ldr r4,[sp,#508]
	str r4,[sp,#388]
	ldr r0,[sp,#240]
	str r0,[sp,#0]
	ldr r0,[sp,#244]
	str r0,[sp,#4]
	ldr r0,[sp,#248]
	str r0,[sp,#8]
	ldr r0,[sp,#252]
	str r0,[sp,#12]
	ldr r0,[sp,#256]
	str r0,[sp,#16]
	ldr r0,[sp,#260]
	str r0,[sp,#20]
	ldr r0,[sp,#264]
	str r0,[sp,#24]
	ldr r0,[sp,#268]
	str r0,[sp,#28]
	ldr r0,[sp,#272]
	str r0,[sp,#32]
	ldr r0,[sp,#276]
	str r0,[sp,#36]
	ldr r0,[sp,#280]
	str r0,[sp,#40]
	ldr r0,[sp,#284]
	str r0,[sp,#44]
	ldr r0,[sp,#288]
	str r0,[sp,#48]
	ldr r0,[sp,#292]
	str r0,[sp,#52]
	ldr r0,[sp,#296]
	str r0,[sp,#56]
	ldr r0,[sp,#300]
	str r0,[sp,#60]
	ldr r0,[sp,#304]
	str r0,[sp,#64]
	ldr r0,[sp,#308]
	str r0,[sp,#68]
	ldr r0,[sp,#312]
	str r0,[sp,#72]
	ldr r0,[sp,#360]
	str r0,[sp,#76]
	ldr r0,[sp,#364]
	str r0,[sp,#80]
	ldr r0,[sp,#368]
	str r0,[sp,#84]
	ldr r0,[sp,#372]
	str r0,[sp,#88]
	ldr r0,[sp,#376]
	str r0,[sp,#92]
	ldr r0,[sp,#380]
	str r0,[sp,#96]
	ldr r0,[sp,#384]
	str r0,[sp,#100]
	ldr r0,[sp,#388]
	str r0,[sp,#104]
	mov r0,#0
	str r0,[sp,#244]
	ldr r0,[sp,#244]
	str r0,[sp,#108]
	bl param32_rec
	add sp,sp, #392
	pop {r4,pc}
@ spilled Size: 0
@ stack Size: 20
sort:
	push {lr}
	sub sp,sp, #20
.L10:
	str r0,[sp,#0]
	str r1,[sp,#4]
	mov r0,#0
	str r0,[sp,#8]
.L11:
	ldr r2,[sp,#8]
	ldr r1,[sp,#4]
	mov r0,#1
	sub r0,r1,r0
	cmp r2,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L12
	beq .L18
.L12:
	ldr r1,[sp,#8]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#12]
.L13:
	ldr r1,[sp,#12]
	ldr r0,[sp,#4]
	cmp r1,r0
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L14
	beq .L17
.L14:
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
	movlt r0,#1
	cmp r0,#0
	bne .L15
	beq .L16
.L15:
	ldr r2,[sp,#0]
	ldr r1,[sp,#8]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	str r0,[sp,#16]
	ldr r2,[sp,#0]
	ldr r1,[sp,#8]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r3,r0,r1,r2
	ldr r2,[sp,#0]
	ldr r1,[sp,#12]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	str r0,[r3,#0]
	ldr r2,[sp,#0]
	ldr r1,[sp,#12]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r1,r0,r1,r2
	ldr r0,[sp,#16]
	str r0,[r1,#0]
.L16:
	ldr r1,[sp,#12]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#12]
	b .L13
.L17:
	ldr r1,[sp,#8]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#8]
	b .L11
.L18:
	add sp,sp, #20
	pop {pc}
