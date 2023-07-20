@ vantage replace 802af7c
.equ VantageID, SkillTester+4

.thumb
push {r4-r7,r14}
ldr r4, =0x203a4ec @atr
ldr r5, =0x203a56c @dfr
mov r6, r0 @place to store attacker
mov r7, r1 @place to store defender
@check for Vantage

ldr r0, SkillTester
mov lr, r0
mov r0, r5 @defender data
ldr r1, VantageID
.short 0xf800
cmp r0, #0
beq Normal

eor r4,r5
eor r5,r4 @ does some switching so vantage doesn't happen
eor r4,r5


Normal:
str r4, [r6]
str r5, [r7]

pop {r4-r7,r15}

.align
.ltorg
SkillTester:
@POIN SkillTester
@WORD VantageID
