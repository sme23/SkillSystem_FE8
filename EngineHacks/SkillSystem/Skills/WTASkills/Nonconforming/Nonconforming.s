.thumb
.equ NonconformingID, SkillTester+4
.equ CheckEventId,0x8083da8

push {r4-r7, lr}
mov r4, r0 @attacker
mov r5, r1 @defender

@first we check if attacker is nonconforming
ldr r0, SkillTester
mov lr, r0
mov r0, r4 @attacker data
ldr r1, NonconformingID
.short 0xf800
push {r0} @to preserve through next function call

@then we check if defender is nonconforming
ldr r0, SkillTester
mov lr, r0
mov r0, r5 @defender data
ldr r1, NonconformingID
.short 0xf800
pop {r1}
eor r0, r1 @we need to move on if either attacker or defender has Nonconforming, but not both
cmp r0, #0x0
beq End

@ one more thing - check a flag to see if we're reversing or not
ldr r0,=ReverseFlagLink
ldrh r0,[r0]
ldr r1,=CheckEventId
mov r14,r1
.short 0xF800
cmp r0,#0
beq End 		@ if it's not set, then end

@now we invert WT for attacker
mov r0, #0x53
ldsb r1, [r4,r0]
neg r1,r1
strb r1, [r4,r0]
mov r0, #0x54
ldsb r1, [r4,r0]
neg r1,r1
strb r1, [r4,r0]

@and then do so for defender
mov r0, #0x53
ldsb r1, [r5,r0]
neg r1,r1
strb r1, [r5,r0]
mov r0, #0x54
ldsb r1, [r5,r0]
neg r1,r1
strb r1, [r5,r0]

End:
pop {r4-r7, r15}
.align
.ltorg
SkillTester:
@Poin SkillTester
@WORD NonconformingID
