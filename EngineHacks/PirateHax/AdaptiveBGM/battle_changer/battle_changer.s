.thumb
.align

.global battle_changer
.type battle_changer, %function

.equ GetROMChapterStruct, 0x8034619
.equ CheckEventId, 0x8083DA9

.macro blh to, reg=r3
    ldr \reg, =\to
    mov lr, \reg
    .short 0xF800
.endm

@hook at 80726CA
battle_changer:
push {r0-r3}
ldr r0,=BossMusicActiveFlagID
ldrh r0,[r0]
blh CheckEventId
cmp r0,#0
bne RetBossMusic
pop {r0-r3}

ldr r6, =0x202BCF0 @chapter data
ldrb r0,[r6,#0xE] @chapter ID
blh GetROMChapterStruct
add r0,#28
lsl r2,r1,#25
bmi ret72704
ldrh r6,[r0,#2]
lsl r1,r1,#24
bmi retNormal
ldrh r6,[r0,#0]
b retNormal

.ltorg
.align

RetBossMusic:
pop {r0-r3}
ldr r6,=BossMusicCurrentSongID
ldr r6,[r6]
ldrh r6,[r6]

retNormal:
ldr r0,=0x80726E3
bx r0

.ltorg
.align

ret72704:
ldr r1,=0x8072705
bx r1

.ltorg
.align
