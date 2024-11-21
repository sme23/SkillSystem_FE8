.thumb
.macro blh to, reg=r3
  ldr \reg, \to
  mov lr, \reg
  .short 0xf800
.endm
.equ BashID, SkillTester+4
.equ DidUnitBreak, BashID+4
.equ d100Result, 0x802a52c
.equ recurse_round, 0x802b83c

@ r0 is attacker, r1 is defender, r2 is current buffer, r3 is battle data
push {r4-r7,lr}
mov r4, r0 @attacker
mov r5, r1 @defender
mov r6, r2 @battle buffer
mov r7, r3 @battle data
ldr     r0,[r2]           @r0 = battle buffer                @ 0802B40A 6800     
lsl     r0,r0,#0xD                @ 0802B40C 0340     
lsr     r0,r0,#0xD        @Without damage data                @ 0802B40E 0B40     
mov r1, #0xC0 @skill flag
lsl r1, #8 @0xC000
add r1, #2 @miss @@@@OR BRAVE??????
tst r0, r1
bne End
@if another skill already activated, don't do anything

@check if we're already in astra
ldrb r0, [r2, #4] @active skill
@make sure no other skill is active
cmp r0, #0
bne End

@check for Adept proc
ldr r0, SkillTester
mov lr, r0
mov r0, r4 @attacker data
ldr r1, BashID
.short 0xf800
cmp r0, #0
beq End


@Don't work if we're defending
ldr r0,=0x203a56c
cmp r0,r4
beq End

@ Don't work if we're not breaking
blh DidUnitBreak
cmp r0, #0
beq End		@ if no break, no effect



@@if we proc, set the brave effect flag for the NEXT hit
@ldrb r1, BashID @first mark Adept active
@strb r1, [r6,#4]

@add     r6, #8 @double width battle buffer   
@mov     r0, #0x40
@lsl     r0, #8  
@str     r0,[r6]                @ 0802B43A 6018  
@ldrb r0, BashID
@strb r0, [r6,#4] @save the skill ID at byte #4

@@now add the number of rounds - 
@ldr r1, RoundCountRAM
@ldr r0, [r1]	@ loads what's at round count ram (number of hits)
@add r0, #1	@ adds one round
@str r0, [r1]	@ stores it at round count ram (hopefully)



@if we proc, set the offensive skill and poison flag
ldr     r2,[r6]    
lsl     r1,r2,#0xD                @ 0802B42C 0351     
lsr     r1,r1,#0xD                @ 0802B42E 0B49     
mov     r0, #0x40
lsl     r0, #8           @0x4000, attacker skill activated
@add   r0,#0x40      @poison
orr     r1, r0
ldr     r0,=#0xFFF80000                @ 0802B434 4804     
and     r0,r2                @ 0802B436 4010     
orr     r0,r1                @ 0802B438 4308     
str     r0,[r6]                @ 0802B43A 6018  

ldrb  r0, BashID
strb  r0, [r6,#4]


WriteStatus:
mov   r0,#0x22  @sleep ID
mov   r1,#0x6F
strb  r0,[r5,r1]

End:
pop {r4-r7}
pop {r15}

.align
.ltorg
SkillTester:
@POIN SkillTester
@WORD BashID
