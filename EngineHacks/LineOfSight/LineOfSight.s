.thumb
.align



.macro blh to, reg=r3
	push {\reg}
	ldr \reg,=\to
	mov r14,\reg
	pop {\reg}
	.short 0xF800
.endm

.global LineOfSight
.type LineOfSight, %function

LineOfSight:


