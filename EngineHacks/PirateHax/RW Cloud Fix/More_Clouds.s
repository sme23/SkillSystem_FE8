.thumb
.align

.macro blh to, reg=r3
    ldr \reg, =\to
    mov lr, \reg
    .short 0xF800
.endm

.equ SetupOAMSpliceForWeather, 0x80301F5
.equ Decompress, 0x8012F51
.equ CopyToPaletteBuffer, 0x8000DB9

.equ ChapterDataStruct, 0x202BCF0

@overwrites function @ 8030A58

.global NewSetupCloudGFX
.type NewSetupCloudGFX, %function

NewSetupCloudGFX:

push {r4,r14}

mov r0,#0
blh SetupOAMSpliceForWeather

@now get our gfx based on current chapter's ID
ldr r0, =ChapterDataStruct
ldrb r0,[r0,#0xE] @chapter ID

ldr r1, =ChapterCloudTable
lsl r0,r0,#3 @multiply by 8
add r1,r0 @r1 = table entry addr
mov r4,r1 @r4 = table entry addr

ldr r0,[r4]
ldr r1,=#0x20027DC @loc to decompress to
blh Decompress

ldr r0,[r4,#4]
mov r1,#0xD0
lsl r1,r1,#2
mov r2,#0x20
blh CopyToPaletteBuffer

pop {r4}
pop {r0}
bx r0

.ltorg
.align

