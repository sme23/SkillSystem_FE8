@ Str > Spd

.equ ShiftID, SkillTester+4
.thumb
.org 0
push {r4-r7,lr}
ldr r0,=0x3004e50
ldr r4,[r0] @save active unit in r4
ldr r1,[r4,#0xc]
mov r0, #0x40 @has not moved...
and r0,r1
cmp r0,#0
bne False

@check if active unit has the skill
mov r0, r4 @test
ldr r1, ShiftID
ldr r2, SkillTester
mov lr, r2
.short 0xf800 @test if unit has the skill
cmp r0, #0
bne True
b False

True:
@check if Str > Spd
mov r0, r4
mov r3, #0x16
ldrb  r1, [r0,r3]
mov r3, #0x14
ldrb  r2, [r0,r3]
cmp r1, r2
ble False

mov r0,#1
b End

False:
mov r0,#3
End:
pop {r4-r7}
pop {r1}
bx r1

.align
.ltorg
SkillTester:
@POIN SkillTester
@WORD ShiftID
