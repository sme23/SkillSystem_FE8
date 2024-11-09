
.macro blh to, reg=r3
	ldr \reg, =\to
	mov lr, \reg
	.short 0xf800
.endm

.equ gActiveBattleUnit, 0x0203A4EC
.equ gActionData, 0x0203A958
.equ GetUnit, 0x08019430
.equ MU_EndAll, 0x080790A4
.equ GetFacingDirection, 0x0807B9B8
.equ ApplyUnitMovement, 0x0801849C
.equ SMS_UpdateFromGameData, 0x080271A0
