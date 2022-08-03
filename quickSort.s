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
@ stack Size: 16
main:
	push {lr}
	vpush {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31}
	sub sp,sp, #16
	bl .init
.L1:
	movw r12,#:lower16:.f0
	movt r12,#:upper16:.f0
	vldr.32 s0,[r12,#0]
	vstr.32 s0,[sp,#4]
	vldr.32 s0,[sp,#4]
	movw r12,#:lower16:.f32
	movt r12,#:upper16:.f32
	vldr.32 s1,[r12,#0]
	vstr.32 s1,[sp,#0]
	movw r12,#:lower16:.f31
	movt r12,#:upper16:.f31
	vldr.32 s31,[r12,#0]
	movw r12,#:lower16:.f30
	movt r12,#:upper16:.f30
	vldr.32 s30,[r12,#0]
	movw r12,#:lower16:.f29
	movt r12,#:upper16:.f29
	vldr.32 s29,[r12,#0]
	movw r12,#:lower16:.f28
	movt r12,#:upper16:.f28
	vldr.32 s28,[r12,#0]
	movw r12,#:lower16:.f27
	movt r12,#:upper16:.f27
	vldr.32 s27,[r12,#0]
	movw r12,#:lower16:.f26
	movt r12,#:upper16:.f26
	vldr.32 s26,[r12,#0]
	movw r12,#:lower16:.f25
	movt r12,#:upper16:.f25
	vldr.32 s25,[r12,#0]
	movw r12,#:lower16:.f24
	movt r12,#:upper16:.f24
	vldr.32 s24,[r12,#0]
	movw r12,#:lower16:.f23
	movt r12,#:upper16:.f23
	vldr.32 s23,[r12,#0]
	movw r12,#:lower16:.f22
	movt r12,#:upper16:.f22
	vldr.32 s22,[r12,#0]
	movw r12,#:lower16:.f21
	movt r12,#:upper16:.f21
	vldr.32 s21,[r12,#0]
	movw r12,#:lower16:.f20
	movt r12,#:upper16:.f20
	vldr.32 s20,[r12,#0]
	movw r12,#:lower16:.f19
	movt r12,#:upper16:.f19
	vldr.32 s19,[r12,#0]
	movw r12,#:lower16:.f18
	movt r12,#:upper16:.f18
	vldr.32 s18,[r12,#0]
	movw r12,#:lower16:.f17
	movt r12,#:upper16:.f17
	vldr.32 s17,[r12,#0]
	movw r12,#:lower16:.f16
	movt r12,#:upper16:.f16
	vldr.32 s16,[r12,#0]
	movw r12,#:lower16:.f15
	movt r12,#:upper16:.f15
	vldr.32 s15,[r12,#0]
	movw r12,#:lower16:.f14
	movt r12,#:upper16:.f14
	vldr.32 s14,[r12,#0]
	movw r12,#:lower16:.f13
	movt r12,#:upper16:.f13
	vldr.32 s13,[r12,#0]
	movw r12,#:lower16:.f12
	movt r12,#:upper16:.f12
	vldr.32 s12,[r12,#0]
	movw r12,#:lower16:.f11
	movt r12,#:upper16:.f11
	vldr.32 s11,[r12,#0]
	movw r12,#:lower16:.f10
	movt r12,#:upper16:.f10
	vldr.32 s10,[r12,#0]
	movw r12,#:lower16:.f9
	movt r12,#:upper16:.f9
	vldr.32 s9,[r12,#0]
	movw r12,#:lower16:.f8
	movt r12,#:upper16:.f8
	vldr.32 s8,[r12,#0]
	movw r12,#:lower16:.f7
	movt r12,#:upper16:.f7
	vldr.32 s7,[r12,#0]
	movw r12,#:lower16:.f6
	movt r12,#:upper16:.f6
	vldr.32 s6,[r12,#0]
	movw r12,#:lower16:.f5
	movt r12,#:upper16:.f5
	vldr.32 s5,[r12,#0]
	movw r12,#:lower16:.f4
	movt r12,#:upper16:.f4
	vldr.32 s4,[r12,#0]
	movw r12,#:lower16:.f3
	movt r12,#:upper16:.f3
	vldr.32 s3,[r12,#0]
	movw r12,#:lower16:.f2
	movt r12,#:upper16:.f2
	vldr.32 s2,[r12,#0]
	movw r12,#:lower16:.f1
	movt r12,#:upper16:.f1
	vldr.32 s1,[r12,#0]
	bl f
	vstr.32 s0,[sp,#8]
	vldr.32 s0,[sp,#8]
	vcvt.s32.f32 s0,s0
	vmov r0,s0
	add sp,sp, #16
	vpop {s1,s2,s3,s4,s5,s6,s7,s8,s9,s10,s11,s12,s13,s14,s15,s16,s17,s18,s19,s20,s21,s22,s23,s24,s25,s26,s27,s28,s29,s30,s31}
	pop {pc}
@ spilled Size: 0
@ stack Size: 136
f:
	push {lr}
	vpush {s1}
	sub sp,sp, #136
.L2:
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
	vldr.32 s0,[sp,#4]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#8]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#12]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#16]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#20]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#24]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#28]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#32]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#36]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#40]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#44]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#48]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#52]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#56]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#60]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#64]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#68]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#72]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#76]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#80]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#84]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#88]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#92]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#96]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#100]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#104]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#108]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#112]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#116]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#120]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#124]
	vadd.f32 s1,s1,s0
	vldr.32 s0,[sp,#144]
	vadd.f32 s0,s1,s0
	add sp,sp, #136
	vpop {s1}
	pop {pc}
.align
.f1:
	.4byte 1073741824
.align
.f2:
	.4byte 1077936128
.align
.f3:
	.4byte 1082130432
.align
.f4:
	.4byte 1084227584
.align
.f5:
	.4byte 1086324736
.align
.f6:
	.4byte 1088421888
.align
.f7:
	.4byte 1090519040
.align
.f8:
	.4byte 1091567616
.align
.f9:
	.4byte 1092616192
.align
.f0:
	.4byte 1093140480
.align
.f10:
	.4byte 1093664768
.align
.f11:
	.4byte 1094713344
.align
.f12:
	.4byte 1095761920
.align
.f13:
	.4byte 1096810496
.align
.f14:
	.4byte 1097859072
.align
.f15:
	.4byte 1098907648
.align
.f16:
	.4byte 1099431936
.align
.f17:
	.4byte 1099956224
.align
.f18:
	.4byte 1100480512
.align
.f19:
	.4byte 1101004800
.align
.f20:
	.4byte 1101529088
.align
.f21:
	.4byte 1102053376
.align
.f22:
	.4byte 1102577664
.align
.f23:
	.4byte 1103101952
.align
.f24:
	.4byte 1103626240
.align
.f25:
	.4byte 1104150528
.align
.f26:
	.4byte 1104674816
.align
.f27:
	.4byte 1105199104
.align
.f28:
	.4byte 1105723392
.align
.f29:
	.4byte 1106247680
.align
.f30:
	.4byte 1106771968
.align
.f31:
	.4byte 1107296256
.align
.f32:
	.4byte 1107558400
