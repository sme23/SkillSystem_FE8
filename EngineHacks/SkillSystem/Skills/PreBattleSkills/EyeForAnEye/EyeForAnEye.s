.thumb
.align

.equ EyeForAnEyeID,SkillTester+4

push {r4-r5,lr}
@goes in the battle loop.
@r0 is the attacker
@r1 is the defender
mov r4, r0
mov r5, r1

ldr r0, SkillTester
mov lr, r0
mov r0, r4
ldr r1, EyeForAnEyeID
.short 0xf800
cmp r0, #0
beq GoBack

mov r0, r4
add r0,#0x37 	
ldrb r3,[r0]	@ the last support byte where eye for an eye damage is stored

mov r0, r4
add r0, #0x5A
ldrb r2, [r0] @ gets the attack of the unit
add r2, r3
strb r2, [r0] @ adds the support byte to attack byte to increase damage by eye for an eye


GoBack:
pop {r4-r5}
pop {r0}
bx r0

.align
.ltorg 
SkillTester:
@POIN SkillTester
@WORD EyeForAnEyeID
