.thumb
.equ HangoverID, SkillTester+4

push {r4-r5, lr}
mov	r4, r0 @attacker

@check if we're past turn 2
ldr	r5,=#0x202BCF0
ldrh	r5, [r5,#0x10]
cmp	r5, #0x02 @turn number to not give "bonuses" past
bhi	End

@check if attacker is hungover
ldr	r0, SkillTester
mov	lr, r0
mov	r0, r4
ldr	r1, HangoverID
.short	0xf800
cmp	r0, #0
beq	End

@subtract 15 from hit and avoid
mov	r0, #0x60 			@load attacker hit
ldrh	r1, [r4,r0]
sub r1, #0x0F 			@value to subtract by
strh	r1, [r4,r0] 	@store attacker hit

mov	r0, #0x62			@load attacker avoid
ldrh	r1, [r4,r0]		
sub r1, #0x0F 			@value to subtract by
strh	r1, [r4,r0] 	@store attacker avoid

End:
pop	{r4-r5, r15}
.align
.ltorg
SkillTester:
@Poin SkillTester
@WORD HangoverID
