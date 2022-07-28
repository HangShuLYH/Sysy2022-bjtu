.arch armv7ve
.arm
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {r4,r5,r6,r11,lr}
	sub sp,sp, #372
	sub r11,sp, #60
	bl .init
.L1:
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#0]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#4]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#8]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#12]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#16]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#40]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	mov r6,r0
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	mov r5,r0
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	mov r4,r0
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#44]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#48]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#52]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#20]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#24]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#28]
	sub sp,sp, #60
	bl getint
	add sp,sp, #60
	str r0,[r11,#32]
	ldr r0,[r11,#0]
	ldr r1,[r11,#4]
	ldr r2,[r11,#8]
	ldr r3,[r11,#12]
	ldr r0,[r11,#16]
	str r0,[sp,#0]
	ldr r0,[r11,#40]
	str r0,[sp,#4]
	str r6,[sp,#8]
	str r5,[sp,#12]
	str r4,[sp,#16]
	ldr r0,[r11,#44]
	str r0,[sp,#20]
	ldr r0,[r11,#48]
	str r0,[sp,#24]
	ldr r0,[r11,#52]
	str r0,[sp,#28]
	ldr r0,[r11,#20]
	str r0,[sp,#32]
	ldr r0,[r11,#24]
	str r0,[sp,#36]
	ldr r0,[r11,#28]
	str r0,[sp,#40]
	ldr r0,[r11,#32]
	str r0,[sp,#44]
	sub sp,sp, #60
	bl param16
	add sp,sp, #60
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
	add r2,r1,r0
	mov r0,#4
	add r1,sp, #112
	mla r0,r0,r2,r1
	ldr r2,[sp,#368]
	mov r1,#1
	sub r2,r2,r1
	mov r1,#2
	mul r2,r2,r1
	mov r1,#1
	add r3,r2,r1
	mov r2,#4
	add r1,sp, #112
	mla r1,r2,r3,r1
	ldr r2,[r1,#0]
	mov r1,#1
	sub r1,r2,r1
	str r1,[r0,#0]
	ldr r1,[sp,#368]
	mov r0,#2
	mul r1,r1,r0
	mov r0,#1
	add r2,r1,r0
	mov r0,#4
	add r1,sp, #112
	mla r0,r0,r2,r1
	ldr r2,[sp,#368]
	mov r1,#1
	sub r2,r2,r1
	mov r1,#2
	mul r2,r2,r1
	mov r1,#0
	add r3,r2,r1
	mov r2,#4
	add r1,sp, #112
	mla r1,r2,r3,r1
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
	sub sp,sp, #60
	bl param32_arr
	add sp,sp, #60
	sub sp,sp, #60
	bl putint
	add sp,sp, #60
	mov r0,#10
	sub sp,sp, #60
	bl putch
	add sp,sp, #60
	mov r0,#0
	add sp,sp, #372
	pop {r4,r5,r6,r11,pc}
param16:
	push {r4,r11,lr}
	sub sp,sp, #240
	sub r11,sp, #168
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
	ldr r0,[sp,#252]
	str r0,[sp,#192]
	ldr r0,[sp,#256]
	str r0,[sp,#196]
	ldr r0,[sp,#260]
	str r0,[sp,#200]
	ldr r0,[sp,#264]
	str r0,[sp,#204]
	ldr r0,[sp,#268]
	str r0,[sp,#208]
	ldr r0,[sp,#272]
	str r0,[sp,#212]
	ldr r0,[sp,#276]
	str r0,[sp,#216]
	ldr r0,[sp,#280]
	str r0,[sp,#220]
	ldr r0,[sp,#284]
	str r0,[sp,#224]
	ldr r0,[sp,#288]
	str r0,[sp,#228]
	ldr r0,[sp,#292]
	str r0,[sp,#232]
	ldr r0,[sp,#296]
	str r0,[sp,#236]
	add r0,sp, #176
	mov r1,#16
	sub sp,sp, #168
	bl sort
	add sp,sp, #168
	ldr r0,[sp,#176]
	ldr r1,[sp,#180]
	ldr r2,[sp,#184]
	ldr r3,[sp,#188]
	ldr r4,[sp,#192]
	str r4,[r11,#0]
	ldr r4,[sp,#196]
	str r4,[r11,#4]
	ldr r4,[sp,#200]
	str r4,[r11,#8]
	ldr r4,[sp,#204]
	str r4,[r11,#12]
	ldr r4,[sp,#208]
	str r4,[r11,#16]
	ldr r4,[sp,#212]
	str r4,[r11,#20]
	ldr r4,[sp,#216]
	str r4,[r11,#24]
	ldr r4,[sp,#220]
	str r4,[r11,#28]
	ldr r4,[sp,#224]
	str r4,[r11,#32]
	ldr r4,[sp,#228]
	str r4,[r11,#36]
	ldr r4,[sp,#232]
	str r4,[r11,#40]
	ldr r4,[sp,#236]
	str r4,[r11,#44]
	ldr r4,[sp,#112]
	str r4,[r11,#48]
	ldr r4,[sp,#116]
	str r4,[r11,#52]
	ldr r4,[sp,#120]
	str r4,[r11,#56]
	ldr r4,[sp,#124]
	str r4,[r11,#60]
	ldr r4,[sp,#252]
	str r4,[r11,#64]
	ldr r4,[sp,#256]
	str r4,[r11,#68]
	ldr r4,[sp,#260]
	str r4,[r11,#72]
	ldr r4,[sp,#264]
	str r4,[r11,#76]
	ldr r4,[sp,#268]
	str r4,[r11,#80]
	ldr r4,[sp,#272]
	str r4,[r11,#140]
	ldr r4,[sp,#276]
	str r4,[r11,#144]
	ldr r4,[sp,#280]
	str r4,[r11,#148]
	ldr r4,[sp,#284]
	str r4,[r11,#152]
	ldr r4,[sp,#288]
	str r4,[r11,#156]
	ldr r4,[sp,#292]
	str r4,[r11,#160]
	ldr r4,[sp,#296]
	str r4,[r11,#164]
	ldr r0,[r11,#0]
	str r0,[sp,#0]
	ldr r0,[r11,#4]
	str r0,[sp,#4]
	ldr r0,[r11,#8]
	str r0,[sp,#8]
	ldr r0,[r11,#12]
	str r0,[sp,#12]
	ldr r0,[r11,#16]
	str r0,[sp,#16]
	ldr r0,[r11,#20]
	str r0,[sp,#20]
	ldr r0,[r11,#24]
	str r0,[sp,#24]
	ldr r0,[r11,#28]
	str r0,[sp,#28]
	ldr r0,[r11,#32]
	str r0,[sp,#32]
	ldr r0,[r11,#36]
	str r0,[sp,#36]
	ldr r0,[r11,#40]
	str r0,[sp,#40]
	ldr r0,[r11,#44]
	str r0,[sp,#44]
	ldr r0,[r11,#48]
	str r0,[sp,#48]
	ldr r0,[r11,#52]
	str r0,[sp,#52]
	ldr r0,[r11,#56]
	str r0,[sp,#56]
	ldr r0,[r11,#60]
	str r0,[sp,#60]
	ldr r0,[r11,#64]
	str r0,[sp,#64]
	ldr r0,[r11,#68]
	str r0,[sp,#68]
	ldr r0,[r11,#72]
	str r0,[sp,#72]
	ldr r0,[r11,#76]
	str r0,[sp,#76]
	ldr r0,[r11,#80]
	str r0,[sp,#80]
	ldr r0,[r11,#140]
	str r0,[sp,#84]
	ldr r0,[r11,#144]
	str r0,[sp,#88]
	ldr r0,[r11,#148]
	str r0,[sp,#92]
	ldr r0,[r11,#152]
	str r0,[sp,#96]
	ldr r0,[r11,#156]
	str r0,[sp,#100]
	ldr r0,[r11,#160]
	str r0,[sp,#104]
	ldr r0,[r11,#164]
	str r0,[sp,#108]
	sub sp,sp, #168
	bl param32_rec
	add sp,sp, #168
	add sp,sp, #240
	pop {r4,r11,pc}
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
param32_rec:
	push {r4,r11,lr}
	sub sp,sp, #240
	sub r11,sp, #160
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
	add sp,sp, #240
	pop {r4,r11,pc}
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
	ldr r3,[sp,#252]
	ldr r4,[sp,#256]
	str r4,[r11,#0]
	ldr r4,[sp,#260]
	str r4,[r11,#4]
	ldr r4,[sp,#264]
	str r4,[r11,#8]
	ldr r4,[sp,#268]
	str r4,[r11,#12]
	ldr r4,[sp,#272]
	str r4,[r11,#16]
	ldr r4,[sp,#276]
	str r4,[r11,#20]
	ldr r4,[sp,#280]
	str r4,[r11,#24]
	ldr r4,[sp,#284]
	str r4,[r11,#28]
	ldr r4,[sp,#288]
	str r4,[r11,#32]
	ldr r4,[sp,#292]
	str r4,[r11,#36]
	ldr r4,[sp,#296]
	str r4,[r11,#40]
	ldr r4,[sp,#300]
	str r4,[r11,#44]
	ldr r4,[sp,#304]
	str r4,[r11,#48]
	ldr r4,[sp,#308]
	str r4,[r11,#52]
	ldr r4,[sp,#312]
	str r4,[r11,#56]
	ldr r4,[sp,#316]
	str r4,[r11,#60]
	ldr r4,[sp,#320]
	str r4,[r11,#64]
	ldr r4,[sp,#324]
	str r4,[r11,#68]
	ldr r4,[sp,#328]
	str r4,[r11,#72]
	ldr r4,[sp,#332]
	str r4,[r11,#76]
	ldr r4,[sp,#336]
	str r4,[r11,#132]
	ldr r4,[sp,#340]
	str r4,[r11,#136]
	ldr r4,[sp,#344]
	str r4,[r11,#140]
	ldr r4,[sp,#348]
	str r4,[r11,#144]
	ldr r4,[sp,#352]
	str r4,[r11,#148]
	ldr r4,[sp,#356]
	str r4,[r11,#152]
	ldr r4,[sp,#360]
	str r4,[r11,#156]
	ldr r0,[r11,#0]
	str r0,[sp,#0]
	ldr r0,[r11,#4]
	str r0,[sp,#4]
	ldr r0,[r11,#8]
	str r0,[sp,#8]
	ldr r0,[r11,#12]
	str r0,[sp,#12]
	ldr r0,[r11,#16]
	str r0,[sp,#16]
	ldr r0,[r11,#20]
	str r0,[sp,#20]
	ldr r0,[r11,#24]
	str r0,[sp,#24]
	ldr r0,[r11,#28]
	str r0,[sp,#28]
	ldr r0,[r11,#32]
	str r0,[sp,#32]
	ldr r0,[r11,#36]
	str r0,[sp,#36]
	ldr r0,[r11,#40]
	str r0,[sp,#40]
	ldr r0,[r11,#44]
	str r0,[sp,#44]
	ldr r0,[r11,#48]
	str r0,[sp,#48]
	ldr r0,[r11,#52]
	str r0,[sp,#52]
	ldr r0,[r11,#56]
	str r0,[sp,#56]
	ldr r0,[r11,#60]
	str r0,[sp,#60]
	ldr r0,[r11,#64]
	str r0,[sp,#64]
	ldr r0,[r11,#68]
	str r0,[sp,#68]
	ldr r0,[r11,#72]
	str r0,[sp,#72]
	ldr r0,[r11,#76]
	str r0,[sp,#76]
	ldr r0,[r11,#132]
	str r0,[sp,#80]
	ldr r0,[r11,#136]
	str r0,[sp,#84]
	ldr r0,[r11,#140]
	str r0,[sp,#88]
	ldr r0,[r11,#144]
	str r0,[sp,#92]
	ldr r0,[r11,#148]
	str r0,[sp,#96]
	ldr r0,[r11,#152]
	str r0,[sp,#100]
	ldr r0,[r11,#156]
	str r0,[sp,#104]
	mov r0,#0
	str r0,[r11,#4]
	ldr r0,[r11,#4]
	str r0,[sp,#108]
	sub sp,sp, #160
	bl param32_rec
	add sp,sp, #160
	add sp,sp, #240
	pop {r4,r11,pc}
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
