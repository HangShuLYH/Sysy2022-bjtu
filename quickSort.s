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
@ stack Size: 372
main:
	push {lr}
	vpush {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16}
	sub sp,sp, #372
	bl .init
.L1:
	add r0,sp, #112
	mov r1,#256
	bl .memset
	bl getfloat
	vmov.32 s16,s0
	bl getfloat
	vmov.32 s1,s0
	bl getfloat
	vmov.32 s2,s0
	bl getfloat
	vmov.32 s3,s0
	bl getfloat
	vmov.32 s4,s0
	bl getfloat
	vmov.32 s5,s0
	bl getfloat
	vmov.32 s6,s0
	bl getfloat
	vmov.32 s7,s0
	bl getfloat
	vmov.32 s8,s0
	bl getfloat
	vmov.32 s9,s0
	bl getfloat
	vmov.32 s10,s0
	bl getfloat
	vmov.32 s11,s0
	bl getfloat
	vmov.32 s12,s0
	bl getfloat
	vmov.32 s13,s0
	bl getfloat
	vmov.32 s14,s0
	bl getfloat
	vmov.32 s15,s0
	vmov.32 s0,s16
	bl param16
	vstr.32 s0,[sp,#112]
	movw r12,#:lower16:.f0
	movt r12,#:upper16:.f0
	vldr.32 s0,[r12,#0]
	vstr.32 s0,[sp,#116]
	movw r12,#:lower16:.f1
	movt r12,#:upper16:.f1
	vldr.32 s0,[r12,#0]
	vstr.32 s0,[sp,#368]
.L2:
	vldr.32 s1,[sp,#368]
	movw r12,#:lower16:.f2
	movt r12,#:upper16:.f2
	vldr.32 s0,[r12,#0]
	vcmpe.f32 s1,s0
	vmrs APSR_nzcv, FPSCR
	mov r0,#0
	movlt r0,#1
	cmp r0,#0
	bne .L3
	beq .L4
.L3:
	vldr.32 s0,[sp,#368]
	mov r0,#2
	mul r1,r4,r0
	mov r0,#0
	add r2,r1,r0
	mov r0,#4
	add r1,sp, #112
	mla r0,r0,r2,r1
	vldr.32 s1,[sp,#368]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s0,[r12,#0]
	vsub.f32 s0,s1,s0
	mov r1,#2
	mul r2,r4,r1
	mov r1,#1
	add r3,r2,r1
	mov r2,#4
	add r1,sp, #112
	mla r1,r2,r3,r1
	vldr.32 s1,[r1,#0]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s0,[r12,#0]
	vsub.f32 s0,s1,s0
	vstr.32 s0,[r0,#0]
	vldr.32 s0,[sp,#368]
	mov r0,#2
	mul r1,r4,r0
	mov r0,#1
	add r2,r1,r0
	mov r0,#4
	add r1,sp, #112
	mla r0,r0,r2,r1
	vldr.32 s1,[sp,#368]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s0,[r12,#0]
	vsub.f32 s0,s1,s0
	mov r1,#2
	mul r2,r4,r1
	mov r1,#0
	add r3,r2,r1
	mov r2,#4
	add r1,sp, #112
	mla r1,r2,r3,r1
	vldr.32 s1,[r1,#0]
	movw r12,#:lower16:.f4
	movt r12,#:upper16:.f4
	vldr.32 s0,[r12,#0]
	vsub.f32 s0,s1,s0
	vstr.32 s0,[r0,#0]
	vldr.32 s1,[sp,#368]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s0,[r12,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#368]
	b .L2
.L4:
	add r0,sp, #360
	str r0,[sp,#108]
	add r0,sp, #352
	str r0,[sp,#104]
	add r0,sp, #344
	str r0,[sp,#100]
	add r0,sp, #336
	str r0,[sp,#96]
	add r0,sp, #328
	str r0,[sp,#92]
	add r0,sp, #320
	str r0,[sp,#88]
	add r0,sp, #312
	str r0,[sp,#84]
	add r0,sp, #304
	str r0,[sp,#80]
	add r0,sp, #296
	str r0,[sp,#76]
	add r0,sp, #288
	str r0,[sp,#72]
	add r0,sp, #280
	str r0,[sp,#68]
	add r0,sp, #272
	str r0,[sp,#64]
	add r0,sp, #264
	str r0,[sp,#60]
	add r0,sp, #256
	str r0,[sp,#56]
	add r0,sp, #248
	str r0,[sp,#52]
	add r0,sp, #240
	str r0,[sp,#48]
	add r0,sp, #232
	str r0,[sp,#44]
	add r0,sp, #224
	str r0,[sp,#40]
	add r0,sp, #216
	str r0,[sp,#36]
	add r0,sp, #208
	str r0,[sp,#32]
	add r0,sp, #200
	str r0,[sp,#28]
	add r0,sp, #192
	str r0,[sp,#24]
	add r0,sp, #184
	str r0,[sp,#20]
	add r0,sp, #176
	str r0,[sp,#16]
	add r0,sp, #168
	str r0,[sp,#12]
	add r0,sp, #160
	str r0,[sp,#8]
	add r0,sp, #152
	str r0,[sp,#4]
	add r0,sp, #144
	str r0,[sp,#0]
	add r3,sp, #136
	add r2,sp, #128
	add r1,sp, #120
	add r0,sp, #112
	bl param32_arr
	bl putfloat
	mov r0,#10
	bl putch
	mov r0,#0
	add sp,sp, #372
	vpop {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16}
	pop {pc}
@ spilled Size: 0
@ stack Size: 128
param16:
	push {lr}
	vpush {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31}
	sub sp,sp, #128
.L5:
	vstr.32 s0,[sp,#0]
	vstr.32 s1,[sp,#4]
	vstr.32 s2,[sp,#8]
	vstr.32 s3,[sp,#12]
	vstr.32 s4,[sp,#16]
	vstr.32 s5,[sp,#20]
	vstr.32 s6,[sp,#24]
	vstr.32 s7,[sp,#28]
	vstr.32 s8,[sp,#32]
	vstr.32 s9,[sp,#36]
	vstr.32 s10,[sp,#40]
	vstr.32 s11,[sp,#44]
	vstr.32 s12,[sp,#48]
	vstr.32 s13,[sp,#52]
	vstr.32 s14,[sp,#56]
	vstr.32 s15,[sp,#60]
	add r0,sp, #64
	mov r1,#64
	bl .memset
	vldr.32 s0,[sp,#0]
	vstr.32 s0,[sp,#64]
	vldr.32 s0,[sp,#4]
	vstr.32 s0,[sp,#68]
	vldr.32 s0,[sp,#8]
	vstr.32 s0,[sp,#72]
	vldr.32 s0,[sp,#12]
	vstr.32 s0,[sp,#76]
	vldr.32 s0,[sp,#16]
	vstr.32 s0,[sp,#80]
	vldr.32 s0,[sp,#20]
	vstr.32 s0,[sp,#84]
	vldr.32 s0,[sp,#24]
	vstr.32 s0,[sp,#88]
	vldr.32 s0,[sp,#28]
	vstr.32 s0,[sp,#92]
	vldr.32 s0,[sp,#32]
	vstr.32 s0,[sp,#96]
	vldr.32 s0,[sp,#36]
	vstr.32 s0,[sp,#100]
	vldr.32 s0,[sp,#40]
	vstr.32 s0,[sp,#104]
	vldr.32 s0,[sp,#44]
	vstr.32 s0,[sp,#108]
	vldr.32 s0,[sp,#48]
	vstr.32 s0,[sp,#112]
	vldr.32 s0,[sp,#52]
	vstr.32 s0,[sp,#116]
	vldr.32 s0,[sp,#56]
	vstr.32 s0,[sp,#120]
	vldr.32 s0,[sp,#60]
	vstr.32 s0,[sp,#124]
	movw r12,#:lower16:.f1
	movt r12,#:upper16:.f1
	vldr.32 s0,[r12,#0]
	add r0,sp, #64
	bl sort
	vldr.32 s0,[sp,#64]
	vldr.32 s1,[sp,#68]
	vldr.32 s2,[sp,#72]
	vldr.32 s3,[sp,#76]
	vldr.32 s4,[sp,#80]
	vldr.32 s5,[sp,#84]
	vldr.32 s6,[sp,#88]
	vldr.32 s7,[sp,#92]
	vldr.32 s8,[sp,#96]
	vldr.32 s9,[sp,#100]
	vldr.32 s10,[sp,#104]
	vldr.32 s11,[sp,#108]
	vldr.32 s12,[sp,#112]
	vldr.32 s13,[sp,#116]
	vldr.32 s14,[sp,#120]
	vldr.32 s15,[sp,#124]
	vldr.32 s16,[sp,#0]
	vldr.32 s17,[sp,#4]
	vldr.32 s18,[sp,#8]
	vldr.32 s19,[sp,#12]
	vldr.32 s20,[sp,#16]
	vldr.32 s21,[sp,#20]
	vldr.32 s22,[sp,#24]
	vldr.32 s23,[sp,#28]
	vldr.32 s24,[sp,#32]
	vldr.32 s25,[sp,#36]
	vldr.32 s26,[sp,#40]
	vldr.32 s27,[sp,#44]
	vldr.32 s28,[sp,#48]
	vldr.32 s29,[sp,#52]
	vldr.32 s30,[sp,#56]
	vldr.32 s31,[sp,#60]
	bl param32_rec
	add sp,sp, #128
	vpop {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31}
	pop {pc}
@ spilled Size: 0
@ stack Size: 136
param32_arr:
	push {lr}
	vpush {s1}
	sub sp,sp, #136
.L6:
	str r0,[sp,#0]
	str r1,[sp,#4]
	str r2,[sp,#8]
	str r3,[sp,#12]
	ldr r0,[sp,#0]
	vldr.32 s1,[r0,#0]
	ldr r0,[sp,#0]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#4]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#4]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#8]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#8]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#12]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#12]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#144]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#144]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#148]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#148]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#152]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#152]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#156]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#156]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#160]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#160]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#164]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#164]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#168]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#168]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#172]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#172]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#176]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#176]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#180]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#180]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#184]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#184]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#188]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#188]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#192]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#192]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#196]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#196]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#200]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#200]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#204]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#204]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#208]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#208]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#212]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#212]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#216]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#216]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#220]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#220]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#224]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#224]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#228]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#228]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#232]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#232]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#236]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#236]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#240]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#240]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#244]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#244]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#248]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#248]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s1,[sp,#128]
	ldr r0,[sp,#252]
	vldr.32 s0,[r0,#0]
	vadd.f32 s1,s1,s0
	ldr r0,[sp,#252]
	add r0,r0, #4
	vldr.32 s0,[r0,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#128]
	vldr.32 s0,[sp,#128]
	add sp,sp, #136
	vpop {s1}
	pop {pc}
@ spilled Size: 0
@ stack Size: 128
param32_rec:
	push {lr}
	vpush {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31}
	sub sp,sp, #128
.L7:
	vstr.32 s0,[sp,#0]
	vstr.32 s1,[sp,#4]
	vstr.32 s2,[sp,#8]
	vstr.32 s3,[sp,#12]
	vstr.32 s4,[sp,#16]
	vstr.32 s5,[sp,#20]
	vstr.32 s6,[sp,#24]
	vstr.32 s7,[sp,#28]
	vstr.32 s8,[sp,#32]
	vstr.32 s9,[sp,#36]
	vstr.32 s10,[sp,#40]
	vstr.32 s11,[sp,#44]
	vstr.32 s12,[sp,#48]
	vstr.32 s13,[sp,#52]
	vstr.32 s14,[sp,#56]
	vstr.32 s15,[sp,#60]
	vstr.32 s16,[sp,#64]
	vstr.32 s17,[sp,#68]
	vstr.32 s18,[sp,#72]
	vstr.32 s19,[sp,#76]
	vstr.32 s20,[sp,#80]
	vstr.32 s21,[sp,#84]
	vstr.32 s22,[sp,#88]
	vstr.32 s23,[sp,#92]
	vstr.32 s24,[sp,#96]
	vstr.32 s25,[sp,#100]
	vstr.32 s26,[sp,#104]
	vstr.32 s27,[sp,#108]
	vstr.32 s28,[sp,#112]
	vstr.32 s29,[sp,#116]
	vstr.32 s30,[sp,#120]
	vstr.32 s31,[sp,#124]
	vldr.32 s1,[sp,#0]
	movw r12,#:lower16:.f0
	movt r12,#:upper16:.f0
	vldr.32 s0,[r12,#0]
	vcmpe.f32 s1,s0
	vmrs APSR_nzcv, FPSCR
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L8
	beq .L9
.L8:
	vldr.32 s0,[sp,#4]
	add sp,sp, #128
	vpop {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31}
	pop {pc}
.L9:
	vldr.32 s1,[sp,#0]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s0,[r12,#0]
	vsub.f32 s0,s1,s0
	vldr.32 s2,[sp,#4]
	vldr.32 s1,[sp,#8]
	vadd.f32 s1,s2,s1
	vldr.32 s2,[sp,#12]
	vldr.32 s3,[sp,#16]
	vldr.32 s4,[sp,#20]
	vldr.32 s5,[sp,#24]
	vldr.32 s6,[sp,#28]
	vldr.32 s7,[sp,#32]
	vldr.32 s8,[sp,#36]
	vldr.32 s9,[sp,#40]
	vldr.32 s10,[sp,#44]
	vldr.32 s11,[sp,#48]
	vldr.32 s12,[sp,#52]
	vldr.32 s13,[sp,#56]
	vldr.32 s14,[sp,#60]
	vldr.32 s15,[sp,#64]
	vldr.32 s16,[sp,#68]
	vldr.32 s17,[sp,#72]
	vldr.32 s18,[sp,#76]
	vldr.32 s19,[sp,#80]
	vldr.32 s20,[sp,#84]
	vldr.32 s21,[sp,#88]
	vldr.32 s22,[sp,#92]
	vldr.32 s23,[sp,#96]
	vldr.32 s24,[sp,#100]
	vldr.32 s25,[sp,#104]
	vldr.32 s26,[sp,#108]
	vldr.32 s27,[sp,#112]
	vldr.32 s28,[sp,#116]
	vldr.32 s29,[sp,#120]
	vldr.32 s30,[sp,#124]
	movw r12,#:lower16:.f0
	movt r12,#:upper16:.f0
	vldr.32 s31,[r12,#0]
	bl param32_rec
	add sp,sp, #128
	vpop {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31}
	pop {pc}
@ spilled Size: 0
@ stack Size: 24
sort:
	push {r4,lr}
	vpush {s1,s2}
	sub sp,sp, #24
.L10:
	str r0,[sp,#0]
	vstr.32 s0,[sp,#4]
	movw r12,#:lower16:.f0
	movt r12,#:upper16:.f0
	vldr.32 s0,[r12,#0]
	vstr.32 s0,[sp,#8]
.L11:
	vldr.32 s2,[sp,#8]
	vldr.32 s1,[sp,#4]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s0,[r12,#0]
	vsub.f32 s0,s1,s0
	vcmpe.f32 s2,s0
	vmrs APSR_nzcv, FPSCR
	mov r1,#0
	movlt r1,#1
	cmp r1,#0
	bne .L12
	beq .L18
.L12:
	vldr.32 s1,[sp,#8]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s0,[r12,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#12]
.L13:
	vldr.32 s1,[sp,#12]
	vldr.32 s0,[sp,#4]
	vcmpe.f32 s1,s0
	vmrs APSR_nzcv, FPSCR
	mov r1,#0
	movlt r1,#1
	cmp r1,#0
	bne .L14
	beq .L17
.L14:
	ldr r1,[sp,#0]
	vldr.32 s0,[sp,#8]
	mov r2,#1
	mul r3,r0,r2
	mov r2,#0
	add r3,r3,r2
	mov r2,#4
	mla r1,r2,r3,r1
	vldr.32 s1,[r1,#0]
	ldr r1,[sp,#0]
	vldr.32 s0,[sp,#12]
	mov r2,#1
	mul r3,r0,r2
	mov r2,#0
	add r3,r3,r2
	mov r2,#4
	mla r1,r2,r3,r1
	vldr.32 s0,[r1,#0]
	vcmpe.f32 s1,s0
	vmrs APSR_nzcv, FPSCR
	mov r1,#0
	movlt r1,#1
	cmp r1,#0
	bne .L15
	beq .L16
.L15:
	ldr r1,[sp,#0]
	vldr.32 s0,[sp,#8]
	mov r2,#1
	mul r3,r0,r2
	mov r2,#0
	add r3,r3,r2
	mov r2,#4
	mla r1,r2,r3,r1
	vldr.32 s0,[r1,#0]
	vstr.32 s0,[sp,#16]
	ldr r1,[sp,#0]
	vldr.32 s0,[sp,#8]
	mov r2,#1
	mul r3,r0,r2
	mov r2,#0
	add r3,r3,r2
	mov r2,#4
	mla r2,r2,r3,r1
	ldr r1,[sp,#0]
	vldr.32 s0,[sp,#12]
	mov r3,#1
	mul r4,r0,r3
	mov r3,#0
	add r4,r4,r3
	mov r3,#4
	mla r1,r3,r4,r1
	vldr.32 s0,[r1,#0]
	vstr.32 s0,[r2,#0]
	ldr r1,[sp,#0]
	vldr.32 s0,[sp,#12]
	mov r2,#1
	mul r3,r0,r2
	mov r2,#0
	add r3,r3,r2
	mov r2,#4
	mla r1,r2,r3,r1
	vldr.32 s0,[sp,#16]
	vstr.32 s0,[r1,#0]
.L16:
	vldr.32 s1,[sp,#12]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s0,[r12,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#12]
	b .L13
.L17:
	vldr.32 s1,[sp,#8]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s0,[r12,#0]
	vadd.f32 s0,s1,s0
	vstr.32 s0,[sp,#8]
	b .L11
.L18:
	add sp,sp, #24
	vpop {s1,s2}
	pop {r4,pc}
.align
.f0:
	.4byte 0
.align
.f3:
	.4byte 1065353216
.align
.f4:
	.4byte 1073741824
.align
.f1:
	.4byte 1098907648
.align
.f2:
	.4byte 1107296256
