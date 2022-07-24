.arch armv7ve
.arm
.section .data
_m_global_string_const0:
	.asciz "%d%d%d%d%d"
_m_global_string_const1:
	.asciz "%f%f%f%f%f"
.global main
.section .text
.init:
.L0:
	bx lr
main:
	push {r4,r5,lr}
	vpush {s0,s1,s2,s3,s4}
	sub sp,sp,#16
	bl .init
.L1:
	mov r0,#27
	bl _sysy_starttime
	mov r0,#28
	bl _sysy_stoptime
	movw r0,#0
	movt r0,#16680
	str r0,[sp,#8]
	mov r0,#10
	str r0,[sp,#12]
	ldr r1,[sp,#12]
	ldr r2,[sp,#12]
	ldr r3,[sp,#12]
	ldr r5,[sp,#12]
	ldr r4,[sp,#12]
	movw r0,#:lower16:_m_global_string_const0
	movt r0,#:upper16:_m_global_string_const0
	str r5,[sp,#0]
	str r4,[sp,#4]
	bl putf
	vldr.32 s0,[sp,#8]
	vldr.32 s1,[sp,#8]
	vldr.32 s2,[sp,#8]
	vldr.32 s3,[sp,#8]
	vldr.32 s4,[sp,#8]
	movw r0,#:lower16:_m_global_string_const1
	movt r0,#:upper16:_m_global_string_const1
	bl putf
	mov r0,#0
	add sp,sp, #16
	vpop {s0,s1,s2,s3,s4}
	pop {r4,r5,pc}
