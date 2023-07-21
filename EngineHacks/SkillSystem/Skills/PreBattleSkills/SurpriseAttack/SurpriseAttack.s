.equ SurpriseAttackID, SkillTester+4
.thumb
push {r4-r7,lr}
@goes in the battle loop.
@r0 is the attacker
@r1 is the defender
mov r4, r0
mov r5, r1

@check for skill
ldr r0, SkillTester
mov lr, r0
mov r0, r4
ldr r1, SurpriseAttackID
.short 0xf800
cmp r0, #0
beq End

@check if defender can counter
mov r1, #0x52
ldrb r0, [r5, r1]
cmp r0, #0x1
beq End

@set the luna bit in attacker's weapon ability word
mov r1, #0x4C
ldr r0, [r4, r1]
mov r2, #0x2
lsl r2, #0x10 @ 0x020000 negate defenses
orr r0, r2
str r0, [r4, r1]

End:
pop {r4-r7}
pop {r0}
bx r0

.ltorg
.align

SkillTester:
@POIN SkillTester
@WORD SurpriseAttackID
