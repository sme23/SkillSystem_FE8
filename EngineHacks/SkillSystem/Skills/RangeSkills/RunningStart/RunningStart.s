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

push 	{lr}
add 	sp, #-0x4
str 	r2, [sp]
mov 	r0, r1

@check that unit is wielding a bow
_blh GetWeaponType
cmp 	r0, #0x3 @bow
bne End

@get number of spaces moved, divide by 3 for range bonus
ldr r0,=0x203a968
ldrb r0,[r0]
mov r1, #0x3
swi #0x6 @stores quotient in r0
mov r3, r0

@this is a vanilla bug, if range bonus is over 3 we have to set it to 0
cmp r3, #0x3
blt GiveRange
mov r3, #0x0

GiveRange:
mov 	r2, sp
ldrh 	r0, [r2]
add 	r0, r3

@prevent the maximum range from going over 15
cmp 	r0, #0xF
bls NotOverMax
mov 	r0, #0xF
NotOverMax:
strh 	r0, [r2]

End:
ldr 	r0, [sp]
add 	sp, #0x4
pop 	{r3}
bx 	r3
.ltorg
.align
