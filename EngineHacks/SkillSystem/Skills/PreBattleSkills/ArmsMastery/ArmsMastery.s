.thumb
.equ ArmsMasteryID, SkillTester+4

push {r4-r7, lr}
mov r4, r0 @attacker
mov r5, r1 @defender

@first we check that attacker has Weapon Insight
ldr r0, SkillTester
mov lr, r0
mov r0, r4 @Attacker data
ldr r1, ArmsMasteryID
.short 0xf800
cmp r0, #0
beq End

@now we check the weapon ranks of attacker and defender
mov r0, #0x48
ldrh r0, [r4,r0] @get attacker's equipped weapon
blh =0x080176b8 @get weapon rank
push {r0} @save this cause it won't be preserved

mov r0, #0x48
ldrh r0, [r5,r0] @get defender's equipped weapon
blh =0x080176b8 @get weapon rank
pop {r1}

@now compare the weapon ranks to see if attacker gets boost
cmp r0,r1
ble End @if attacker's weapon rank is less than or equal to defender, no boost for us

@make attacker's attack brave
mov r0, #0x4c
ldr r1, [r4,r0]
mov r2, #0x20 @brave bit
orr r1,r2
str r1, [r4,r0]

End:
pop {r4-r7}
pop {r0}
bx r0

.ltorg
.align

SkillTester:
@POIN SkillTester
@WORD ArmsMasteryID
