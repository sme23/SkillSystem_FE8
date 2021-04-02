.thumb
.align

.macro blh to,reg=r3
	push {\reg}
	ldr \reg,=\to
	mov r14,\reg
	pop {\reg}
	.short 0xF800
.endm

.equ CommandPointsRamLoc,0x0203F107 @hopefully not used by anything else but we'll see
.equ ChapterDataStruct,0x202BCF0
.equ GetChapterAllyUnitCount,0x8012345

.global GetCommandPoints
.type GetCommandPoints, %function

.global SetCommandPoints
.type SetCommandPoints, %function

.global GenerateCommandPoints
.type GenerateCommandPoints, %function

.global SetCommandPointsForTurn
.type SetCommandPointsForTurn, %function

.global AlreadyMovedMoveDebuff
.type AlreadyMovedMoveDebuff, %function


GetCommandPoints: @no arguments, returns command points in r0
ldr r0,=CommandPointsRamLoc
ldrb r0,[r0]
bx r14

.ltorg
.align


SetCommandPoints: @r0 = new command points value, no return value
ldr r1,=CommandPointsRamLoc
strb r0,[r1]
bx r14

.ltorg
.align


GenerateCommandPoints: @no arguments, returns command points in r0

@for any given turn, command points are equal to # of deployed units + turn count - 1
push {r4,r14}

blh GetChapterAllyUnitCount
mov r4,r0

ldr r0,=ChapterDataStruct
ldrb r0,[r0,#0x10]
add r4,r0

sub r4,#1
mov r0,r4

pop {r4}
pop {r1}
bx r1

.ltorg
.align


SetCommandPointsForTurn: @r0 = parent proc, no return value
push {r4,r14}
mov r4,r0

@this will get run every phase but we only want it to work on player phase
@so check current phase
ldr r0,=ChapterDataStruct
ldrb r0,[r0,#0xF]
cmp r0,#0
bne SetCommandPointsForTurn_GoBack

mov r0,r4
bl GenerateCommandPoints
bl SetCommandPoints

SetCommandPointsForTurn_GoBack:
pop {r4}
pop {r0}
bx r0

.ltorg
.align

AlreadyMovedMoveDebuff: @goes in stat getters
push {r4-r6, r14}
mov r4, r0 @stat
mov r5, r1 @unit

ldr r0,[r5,#0xC]
mov r1,#0x40
and r0,r1
cmp r0,#0
beq AlreadyMovedMoveDebuff_GoBack

lsr r4,r4,#2 @/4

AlreadyMovedMoveDebuff_GoBack:
mov r0,r4
mov r1,r5
pop {r4-r6}
pop {r2}
bx r2


