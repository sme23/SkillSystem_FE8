.thumb
.align

.global InitializeDynamicTileChange
.type InitializeDynamicTileChange, %function

.equ SpawnTrap, 0x0802E2B9

.macro blh to, reg=r3
    ldr \reg, =\to
    mov lr, \reg
    .short 0xF800
.endm

.align
InitializeDynamicTileChange:
@ r5 is pointer to event definition of trap
@
ldrb r0,[r5,#1]
ldrb r1,[r5,#2]
ldrb r2,[r5]
mov r3,#0
blh SpawnTrap, r4

ldrh r1,[r5,#4]
strh r1,[r0,#4]

ldr r3,=0x8037901
bx r3

.ltorg
.align

