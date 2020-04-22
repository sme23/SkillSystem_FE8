.thumb
.align


.global ArriveCommandUsability
.type ArriveCommandUsability, %function

.global ArriveCommandEffect
.type ArriveCommandEffect, %function

.global EscapeCommandUsability
.type EscapeCommandUsability, %function

.global EscapeCommandEffect
.type EscapeCommandEffect, %function

.equ CheckEventId,0x8083da8


ArriveCommandUsability:
push {r4,r14}

@Check for Cantoing
ldr r4,=0x03004E50 							@active unit ptr
ldr r2,[r4] 								@unit struct ptr
ldr r0,[r2,#0x0C]							@unit status bitfield
mov r1,#0x40								@cantoing bit
and r0,r1									@check for bit
cmp r0,#0									@if 0, bit is not set
bne ArriveCommandUsability_ReturnFalse		@if set, return false

@Check for being on arrive point
ldr r1,[r4]									@unit struct ptr
ldrb r0,[r1,#0x10]							@load X coord
ldrb r1,[r1,#0x11]							@load Y coord
ldr r3,=#0x8084078							@function that gets the ID of the thing we're on
mov r14,r3									@
.short 0xF800								@blh
mov r1,#0x03								@
cmp r0,#0x19								@if ID = 0x19, it's an arrive point
bne ArriveCommandUsability_ReturnFalse		@otherwise, return false

mov r0,#1									@return true		
b ArriveCommandUsability_GoBack				@jump to go back

ArriveCommandUsability_ReturnFalse:			
mov r0,#3									@return false

ArriveCommandUsability_GoBack:
pop {r4}									@
pop {r1}									@
bx r1										@

.ltorg
.align



ArriveCommandEffect:
push {r4,r14}
ldr r4,=#0x8023021 	@seize command effect
mov r14,r4			@
.short 0xF800		@blh
pop {r4}			@
pop {r0}			@
bx r0				@

.ltorg
.align



EscapeCommandUsability:
push {r4,r14}

@Check for Cantoing
ldr r4,=0x03004E50
ldr r2,[r4]
ldr r0,[r2,#0x0C]
mov r1,#0x40
and r0,r1
cmp r0,#0
bne EscapeCommandUsability_ReturnFalse

@Check for being lord
ldr r0,[r4]
ldr r0,[r0]
ldr r0,[r0,#40]
lsl r0,r0,#16
lsr r0,r0,#24
mov r1,#0x20
and r0,r1
cmp r0,#0x20
beq EscapeCommandUsability_IsALord


@Check for being on escape point
ldr r1,[r4]
mov r0,#0x10
ldsb r0,[r1,r0]
ldrb r1,[r1,#0x11]
lsl r1,r1,#0x18
asr r1,r1,#0x18
ldr r3,=#0x8084078
mov r14,r3
.short 0xF800
mov r1,#0x03
cmp r0,#0x13
bne EscapeCommandUsability_ReturnFalse

mov r0,#1
b EscapeCommandUsability_GoBack

EscapeCommandUsability_IsALord:
@we're a lord, so check if the flag is set that will make us have to return the "gray out this menu option" thing



EscapeCommandUsability_ReturnFalse:
mov r0,#3

EscapeCommandUsability_GoBack:
pop {r4}
pop {r1}
bx r1



