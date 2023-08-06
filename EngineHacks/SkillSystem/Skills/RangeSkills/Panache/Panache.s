.thumb

.macro _blh to, reg=r3
	ldr \reg, =\to
	mov lr, \reg
	.short 0xF800
.endm

@arguments:
	@r0: unit pointer
	@r1: item id
	@r2: min max range word
@retuns
	@r0: updated min max range word
.set GetWeaponType, 0x8017548
.set BonusWeaponType, 0x7 @Guns

push 	{lr}
add 	sp, #-0x4
str 	r2, [sp]

ldr r3, =0x202bcff @current phase
ldrb r3, [r3]
cmp r3, #0x0 @check if player phase
bne End

mov 	r0, r1
_blh GetWeaponType
cmp 	r0, #BonusWeaponType	@check if item is matching weapon type
bne End
mov 	r0, #0x1
mov 	r1, sp
strh 	r0, [r1,#0x2]

End:
ldr 	r0, [sp]
add 	sp, #0x4
pop 	{r3}
bx 	r3
.ltorg
.align
