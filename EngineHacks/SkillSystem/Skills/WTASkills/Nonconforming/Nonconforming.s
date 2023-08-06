.thumb
.equ NonconformingID, SkillTester+4

push {r4-r7, lr}
mov r4, r0 @attacker
mov r5, r1 @defender

@first we check if defender is nonconforming
ldr r0, SkillTester
mov lr, r0
mov r0, r5 @defender data
ldr r1, NonconformingID
.short 0xf800
push {r0} @to preserve through next function call

@and then we check if attacker is nonconforming
CheckAttacker:
ldr r0, SkillTester
mov lr, r0
mov r0, r4 @attacker data
ldr r1, NonconformingID
.short 0xf800
pop {r1}
eor r0, r1 @we need to move on if either attacker or defender has Nonconforming, but not both
cmp r0, #0x0
beq End

@now we invert WT for attacker
mov r0,r4
add r0,#0x53
ldrb r1,[r0]
neg r1,r1
strb r1,[r0]
add r0,#1
ldrb r1,[r0]
neg r1,r1
strb r1,[r0]

@and then do so for defender
mov r0,r5
add r0,#0x53
ldrb r1,[r0]
neg r1,r1
strb r1,[r0]
add r0,#1
ldrb r1,[r0]
neg r1,r1
strb r1,[r0]

End:
pop {r4-r7, r15}
.align
.ltorg
SkillTester:
@Poin SkillTester
@WORD NonconformingID
