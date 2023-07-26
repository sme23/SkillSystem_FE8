@Suppressive Fire: Allies ignore foe's avoid when foe is in unit's attacking range.
.equ SuppressiveFireID, SkillTester+4
.equ AuraSkillCheck, SkillTester+8
.equ GetUnitsInRange, SkillTester+12
.thumb
push {r4-r7,lr}
@goes in the battle loop.
@r0 is the attacker
@r1 is the defender
mov r4, r0
mov r5, r1

@okay this is unintuitive but since lua herself can't get the skill effect we jump to the end if any combatant has the skill
ldr r0, SkillTester
mov lr, r0
mov r0, r4 @attacker
ldr r1, SuppressiveFireID
.short 0xf800
cmp r0, #0
bne End @usually beq but we want to skip if unit has skill

@if there's a more eloquent way to do this it's beyond me
ldr r0, SkillTester
mov lr, r0
mov r0, r5 @usually r4 for attacker but we want to check defender
ldr r1, SuppressiveFireID
.short 0xf800
cmp r0, #0
bne End @usually beq but we want to skip if unit has skill

@now we need to get lua's attack range to pass to the aura skill check
mov r0, #0x1 @disgusting hardcoded unit id, should be replaced later
ldr r3, =0x0801829D @returns unit struct in r0
mov lr, r3
.short 0xF800

@ everything here is supposed to be a replacement for the hardcoded unit check but it freezes when trying to open a unit's status screen.
/*
@then we check all units on the map to see which of them has Suppressive Fire
ldr r0, GetUnitsInRange
mov lr, r0
mov r0, r4
mov r2, #0x0 @check for same allegiance
mov r3, #0xFF @essentially whole map range
.short 0xF800 @returns list of unit ids in r0

@now that we've got our list of units in r0, loop until we find an instance of Suppressive Fire
mov r2, #0x0
Loop:
ldrb r1, [r0,r2] @get unit id from list
push {r0,r2} @we need to preserve these values for later
ldr r3, =0x0801829D 
mov lr, r3
.short 0xF800 @get character struct for unit id in list
ldr r3, SkillTester 
mov lr, r3
ldr r1, SuppressiveFireID
.short 0xf800 @test character struct for Suppressive Fire
cmp r0, #0
bne HasSkill @if unit has skill, we exit the loop and move on with our lives
pop {r0,r2} @bring back the list of unit ids and our current position
add r2, #0x1 @advance list by one unit
b Loop

HasSkill:
pop {r0,r2} 
*/

mov r1, #0x1e @first item in unit's inventory
ldrb r0, [r0,r1]
ldr r3, =0x08017684 @max range getter
mov lr, r3
.short 0xF800
push {r0} @preserve the range cause we need it for later

@now we check enemies in skill holder's attack range
ldr r0, AuraSkillCheck
mov lr, r0
mov r0, r4
ldr r1, SuppressiveFireID
mov r2, #3 @are enemies
pop {r3} @put range back here for max aura radius
.short 0xf800
cmp r0, #0
beq End

@set attacker's avoid to 0
mov r0, #0x62
ldrh r1, [r4,r0]
sub r1, r1
strh r1, [r4,r0]

End:
pop {r4-r7}
pop {r0}
bx r0
.align
.ltorg
SkillTester:
@ POIN SkillTester
@ WORD SuppressiveFireID
@ POIN AuraSkillCheck
@ POIN GetUnitsInRange
