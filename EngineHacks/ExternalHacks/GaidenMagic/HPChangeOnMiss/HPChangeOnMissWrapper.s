.thumb

.macro blh to, reg=r3
    ldr \reg, =\to
    mov lr, \reg
    .short 0xF800
.endm

.global HPChangeOnMissWrapper
.type HPChangeOnMissWrapper, %function

.equ UnitHasMagicRank, 0x8018A59

HPChangeOnMissWrapper: @nop @ 805849A, then hook this

mov r0,r6
mov r1,r7
mov r2,r9
mov r3,r10
bl HPChangeOnMiss
mov r9,r1
mov r10,r0

mov r0,r6
blh UnitHasMagicRank
cmp r0, #0
bne RetMagicRank
ldr r0,=#0x80DAE96 @this is vanilla, not random magic numbers
b RetNoMagicRank

RetMagicRank:
ldr r0,=#0x80DAEBE @same as above, dunno why they did it like this
RetNoMagicRank:
ldr r1,=#0x80584B7
bx r1

.ltorg
.align

