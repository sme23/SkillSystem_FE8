.thumb
.equ UnderhandedID, SkillTester+4

push {r4-r7, lr}
mov r4, r0 @attacker
mov r5, r1 @defender

@first we check that attacker has Underhanded
ldr r0, SkillTester
mov lr, r0
mov r0, r4 @attacker data
ldr r1, UnderhandedID
.short 0xf800
cmp r0, #0
beq End

@okay now we check that attacker is at weapon triangle advantage
mov r0, #0x53
ldrb r0, [r4,r0] @this is the byte for attacker's wt hit bonus
cmp r0, #0x0
ble End @if wt hit bonus is <= 0, attacker doesn't have wta

@give crit and crit avoid
mov r0, #0x66
ldrh r1, [r4,r0]
add r1, #0x0F @add 15 crit
strh r1, [r4,r0]

mov r0, #0x68
ldrh r1, [r4,r0]
add r1, #0x1E @add 30 crit avoid
strh r1, [r4,r0]

End:
pop {r4-r7, r15}
.align
.ltorg
SkillTester:
@Poin SkillTester
@WORD UnderhandedID
