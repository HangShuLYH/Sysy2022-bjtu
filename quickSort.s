.arch armv7ve
.arm
.section .bss
.align
__HELLO:
	.space 400
.align
N4__mE___:
	.space 1200
.align
saY_HeI10_To:
	.space 160
.align
RET:
	.space 20
.global main
.section .text
.init:
.L0:
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	mov r0,#87
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #4
	mov r0,#101
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #8
	mov r0,#108
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #12
	mov r0,#99
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #16
	mov r0,#111
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #20
	mov r0,#109
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #24
	mov r0,#101
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #28
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #32
	mov r0,#116
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #36
	mov r0,#111
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #40
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #44
	mov r0,#116
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #48
	mov r0,#104
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #52
	mov r0,#101
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #56
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #60
	mov r0,#74
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #64
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #68
	mov r0,#112
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #72
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #76
	mov r0,#114
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #80
	mov r0,#105
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #84
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #88
	mov r0,#80
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #92
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #96
	mov r0,#114
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #100
	mov r0,#107
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #104
	mov r0,#33
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #108
	mov r0,#10
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #112
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #116
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #120
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #124
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #128
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #132
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #136
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #140
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #144
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #148
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #152
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #156
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #160
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #164
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #168
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #172
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #176
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #180
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #184
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #188
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #192
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #196
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #200
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #204
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #208
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #212
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #216
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #220
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #224
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #228
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #232
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #236
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #240
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #244
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #248
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #252
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #256
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #260
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #264
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #268
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #272
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #276
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #280
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #284
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #288
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #292
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #296
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #300
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #304
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #308
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #312
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #316
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #320
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #324
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #328
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #332
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #336
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #340
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #344
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #348
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #352
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #356
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #360
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #364
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #368
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #372
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #376
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #380
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #384
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #388
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #392
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:__HELLO
	movt r1,#:upper16:__HELLO
	add r1,r1, #396
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r0,#83
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #4
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #8
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #12
	mov r0,#98
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #16
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #20
	mov r0,#114
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #24
	mov r0,#117
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #28
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #32
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #36
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #40
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #44
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #48
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #52
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #56
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #60
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #64
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #68
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #72
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #76
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #80
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #84
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #88
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #92
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #96
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #100
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #104
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #108
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #112
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #116
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #120
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #124
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #128
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #132
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #136
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #140
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #144
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #148
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #152
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #156
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #160
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #164
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #168
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #172
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #176
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #180
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #184
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #188
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #192
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #196
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #200
	mov r0,#75
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #204
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #208
	mov r0,#98
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #212
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #216
	mov r0,#110
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #220
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #224
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #228
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #232
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #236
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #240
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #244
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #248
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #252
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #256
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #260
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #264
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #268
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #272
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #276
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #280
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #284
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #288
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #292
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #296
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #300
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #304
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #308
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #312
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #316
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #320
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #324
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #328
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #332
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #336
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #340
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #344
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #348
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #352
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #356
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #360
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #364
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #368
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #372
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #376
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #380
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #384
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #388
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #392
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #396
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #400
	mov r0,#72
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #404
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #408
	mov r0,#115
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #412
	mov r0,#104
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #416
	mov r0,#105
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #420
	mov r0,#98
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #424
	mov r0,#105
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #428
	mov r0,#114
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #432
	mov r0,#111
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #436
	mov r0,#107
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #440
	mov r0,#111
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #444
	mov r0,#117
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #448
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #452
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #456
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #460
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #464
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #468
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #472
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #476
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #480
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #484
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #488
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #492
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #496
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #500
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #504
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #508
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #512
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #516
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #520
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #524
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #528
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #532
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #536
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #540
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #544
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #548
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #552
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #556
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #560
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #564
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #568
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #572
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #576
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #580
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #584
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #588
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #592
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #596
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #600
	mov r0,#65
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #604
	mov r0,#114
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #608
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #612
	mov r0,#105
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #616
	mov r0,#103
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #620
	mov r0,#117
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #624
	mov r0,#109
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #628
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #632
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #636
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #640
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #644
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #648
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #652
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #656
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #660
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #664
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #668
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #672
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #676
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #680
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #684
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #688
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #692
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #696
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #700
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #704
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #708
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #712
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #716
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #720
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #724
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #728
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #732
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #736
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #740
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #744
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #748
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #752
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #756
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #760
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #764
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #768
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #772
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #776
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #780
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #784
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #788
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #792
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #796
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #800
	mov r0,#72
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #804
	mov r0,#117
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #808
	mov r0,#110
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #812
	mov r0,#98
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #816
	mov r0,#111
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #820
	mov r0,#114
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #824
	mov r0,#117
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #828
	mov r0,#116
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #832
	mov r0,#111
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #836
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #840
	mov r0,#80
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #844
	mov r0,#101
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #848
	mov r0,#110
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #852
	mov r0,#103
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #856
	mov r0,#105
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #860
	mov r0,#110
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #864
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #868
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #872
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #876
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #880
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #884
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #888
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #892
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #896
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #900
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #904
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #908
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #912
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #916
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #920
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #924
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #928
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #932
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #936
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #940
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #944
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #948
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #952
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #956
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #960
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #964
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #968
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #972
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #976
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #980
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #984
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #988
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #992
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #996
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1000
	mov r0,#84
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1004
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1008
	mov r0,#105
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1012
	mov r0,#114
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1016
	mov r0,#105
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1020
	mov r0,#107
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1024
	mov r0,#117
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1028
	add r1,r1,r12
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1032
	add r1,r1,r12
	mov r0,#79
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1036
	add r1,r1,r12
	mov r0,#111
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1040
	mov r0,#107
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1044
	add r1,r1,r12
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1048
	add r1,r1,r12
	mov r0,#109
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1052
	add r1,r1,r12
	mov r0,#105
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1056
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1060
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1064
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1068
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1072
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1076
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1080
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1084
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1088
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1092
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1096
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1100
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1104
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1108
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1112
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1116
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1120
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1124
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1128
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1132
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1136
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1140
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1144
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1148
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1152
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1156
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1160
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1164
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1168
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1172
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1176
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1180
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	add r1,r1, #1184
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1188
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1192
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:N4__mE___
	movt r1,#:upper16:N4__mE___
	mov r12,#1196
	add r1,r1,r12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #4
	mov r0,#115
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #8
	mov r0,#97
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #12
	mov r0,#121
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #16
	mov r0,#115
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #20
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #24
	mov r0,#104
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #28
	mov r0,#101
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #32
	mov r0,#108
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #36
	mov r0,#108
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #40
	mov r0,#111
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #44
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #48
	mov r0,#116
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #52
	mov r0,#111
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #56
	mov r0,#32
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #60
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #64
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #68
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #72
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #76
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #80
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #84
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #88
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #92
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #96
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #100
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #104
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #108
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #112
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #116
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #120
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #124
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #128
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #132
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #136
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #140
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #144
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #148
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #152
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:saY_HeI10_To
	movt r1,#:upper16:saY_HeI10_To
	add r1,r1, #156
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:RET
	movt r1,#:upper16:RET
	mov r0,#10
	str r0,[r1,#0]
	movw r1,#:lower16:RET
	movt r1,#:upper16:RET
	add r1,r1, #4
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:RET
	movt r1,#:upper16:RET
	add r1,r1, #8
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:RET
	movt r1,#:upper16:RET
	add r1,r1, #12
	mov r0,#0
	str r0,[r1,#0]
	movw r1,#:lower16:RET
	movt r1,#:upper16:RET
	add r1,r1, #16
	mov r0,#0
	str r0,[r1,#0]
	bx lr
main:
	push {lr}
	sub sp,sp, #12
	bl .init
.L1:
	movw r0,#:lower16:__HELLO
	movt r0,#:upper16:__HELLO
	bl putstr
	mov r0,#0
	str r0,[sp,#0]
.L2:
.L3:
	ldr r1,[sp,#0]
	mov r0,#6
	sdiv r0,r1,r0
	str r0,[sp,#4]
	ldr r2,[sp,#0]
	mov r1,#6
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	str r0,[sp,#8]
	ldr r1,[sp,#4]
	ldr r0,[sp,#8]
	cmp r1,r0
	mov r0,#0
	movne r0,#1
	cmp r0,#0
	bne .L4
	beq .L5
.L4:
	ldr r1,[sp,#4]
	mov r0,#50
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	movw r0,#:lower16:N4__mE___
	movt r0,#:upper16:N4__mE___
	mov r1,#4
	mla r0,r1,r2,r0
	bl putstr
	movw r0,#:lower16:saY_HeI10_To
	movt r0,#:upper16:saY_HeI10_To
	bl putstr
	ldr r1,[sp,#8]
	mov r0,#50
	mul r1,r1,r0
	mov r0,#0
	add r2,r1,r0
	movw r0,#:lower16:N4__mE___
	movt r0,#:upper16:N4__mE___
	mov r1,#4
	mla r0,r1,r2,r0
	bl putstr
	movw r0,#:lower16:RET
	movt r0,#:upper16:RET
	bl putstr
.L5:
	ldr r1,[sp,#0]
	mov r0,#17
	mul r1,r1,r0
	mov r0,#23
	add r2,r1,r0
	mov r1,#32
	sdiv r0,r2,r1
	mul r0,r0,r1
	sub r0,r2,r0
	str r0,[sp,#0]
	ldr r1,[sp,#0]
	mov r0,#0
	cmp r1,r0
	mov r0,#0
	moveq r0,#1
	cmp r0,#0
	bne .L6
	beq .L2
.L6:
.L7:
	mov r0,#0
	add sp,sp, #12
	pop {pc}
putstr:
	push {lr}
	sub sp,sp, #8
.L8:
	str r0,[sp,#0]
	mov r0,#0
	str r0,[sp,#4]
.L9:
	ldr r2,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	cmp r0,#0
	bne .L10
	beq .L11
.L10:
	ldr r2,[sp,#0]
	ldr r1,[sp,#4]
	mov r0,#1
	mul r1,r1,r0
	mov r0,#0
	add r1,r1,r0
	mov r0,#4
	mla r0,r0,r1,r2
	ldr r0,[r0,#0]
	bl putch
	ldr r1,[sp,#4]
	mov r0,#1
	add r0,r1,r0
	str r0,[sp,#4]
	b .L9
.L11:
	ldr r0,[sp,#4]
	add sp,sp, #8
	pop {pc}
