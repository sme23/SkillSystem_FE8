.thumb
.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm
.equ MaxHpGetter, 0x8019190
.equ CurrHPGetter, 0x8019150
.equ ResoluteSacrificeID, SkillTester+4
.equ LiveToServeID, SkillTester+8

@hook at 802ebd4
@r5 is amount to heal
@r4 is the action struct
@193a4 heals the unit in r0 by the amount in r1

@ Store uncapped heal value in battle buffer round +0x6
ldr	r2,=0x802ec18
ldr	r2,[r2]		@203a608 - battle buffer pointer
ldr	r2,[r2]
strh r5, [r2, #0x6]

@calculate amount healed:
ldrb	r0,[r4, #0xd]	@target number
blh	0x8019430	@get target data
blh	CurrHPGetter
mov	r1,r0

push	{r1}
ldrb	r0,[r4, #0xd]	@target number
blh	0x8019430	@get target data
blh	MaxHpGetter
mov	r2,r0
pop	{r1}
add	r1,r5		@final hp without Resolute Sacrifice

push {r6,r7}
mov  r6, r1
mov  r7, r2
@check for Resolute Sacrifice
ldrb	r0,[r4,#0xc]
blh	0x8019430
ldr	r1,ResoluteSacrificeID
ldr	r3,SkillTester
mov	lr,r3
.short 0xf800
cmp	r0,#0
beq	AfterResoluteSacrifice

@calculate razvan's missing hp
ldrb	r0,[r4,#0xc]
blh	0x8019430
blh	MaxHpGetter
mov r3, r0
ldrb r0,[r4,#0xc]
push {r3}
blh	0x8019430
blh	CurrHPGetter
pop {r3}
sub r3, r0
add r6, r3 @adds result to final heal

AfterResoluteSacrifice:
mov r1, r6
mov r2, r7
pop {r6,r7}
cmp	r1,r2
ble	NoCap
mov	r1,r2

NoCap:
push	{r1}
ldrb	r0,[r4, #0xd]	@target number
blh	0x8019430	@get target data
blh	CurrHPGetter
mov	r2,r0
pop	{r1}
sub	r1,r2		@final hp - current = healed ammount
mov	r5,r1
ldrb	r0,[r4,#0xd]	@target number
blh	0x8019430	@get target data
mov	r1,r5
blh	0x80193a4	@heal ally

@now check for the skill
ldrb	r0,[r4,#0xc]
blh	0x8019430
ldr	r1,LiveToServeID
ldr	r3,SkillTester
mov	lr,r3
.short 0xf800
cmp	r0,#0
beq	AfterLiveToServe

@now heal self
ldrb	r0,[r4,#0xc]
blh	0x8019430
mov	r1,r5
blh	0x80193a4

@now cap off hp of self (healer).
@and write amount to heal to healer.
ldrb	r0,[r4,#0xc]
blh	0x8019430
blh	0x8019150
ldr	r2,=0x802ec18
ldr	r2,[r2]		@203a608 - battle buffer pointer
ldr	r2,[r2]
ldr	r1,=0x203a4ec @attacker
ldrb  r1, [r1, #0x13]
sub   r1, r0, r1  @post-battle hp - current hp.
strb	r1, [r2,#5]

@and again for the ally, and fetch currhp
ldrb	r0,[r4,#0xd]
blh	0x8019430
blh	0x8019150
ldr	r2,=0x802ec18
ldr	r2,[r2]		@203a608 - battle buffer pointer
ldr	r2,[r2]
ldr	r5,=0x203a56c
ldrb	r1,[r5,#0x13]
sub	r1,r0		@current hp - post-battle hp. This one needs to be negative.
strb	r1,[r2,#3]

@set the heal flag
ldr     r3,[r2]
lsl     r1,r3,#0xD                @ 0802B42C 0351     
lsr     r1,r1,#0xD                @ 0802B42E 0B49     
mov     r0,#0x1
lsl     r0,#8           @0x100, update attacker hp
orr     r1,r0
ldr     r0,=#0xFFF80000                @ 0802B434 4804     
and     r0,r3                @ 0802B436 4010     
orr     r0,r1                @ 0802B438 4308
str     r0,[r2]
@finish up by updating the attacker/defender
ldrb	r0,[r4, #0xd]
blh	0x8019430
blh	0x8019150
strb	r0,[r5,#0x13]
ldr	r5,=0x203a4ec @attacker
ldrb	r0,[r4,#0xc]
blh	0x8019430
blh	0x8019150
strb	r0,[r5,#0x13]

ldr r0, =0x802ec03
bx r0

AfterLiveToServe:
ldr r0,=0x802ebe1
bx r0 

.align
.ltorg
SkillTester:
@POIN SkillTester
@WORD LiveToServeID
