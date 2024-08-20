.thumb
.macro blh to, reg
    ldr \reg, =\to
    mov lr, \reg
    .short 0xF800
.endm

.equ CheckEventId,0x8083da8
.equ SetEventId, 0x8083D81
.equ UnsetEventId, 0x8083D95

push {r4-r5, lr}
mov  r4, r0
mov  r5, r1

ldr r0,=ReverseFlagLink
ldrh r0,[r0]
ldr r1,=CheckEventId
mov r14,r1
.short 0xF800
cmp r0,#0
bne UnsetFlag

ldr r0,=ReverseFlagLink @ sets the flag if it's not currently set
ldrh r0,[r0]
ldr r1,=SetEventId
mov r14,r1
.short 0xF800
b End

UnsetFlag:
ldr r0,=ReverseFlagLink @ unsets the flag if it's currently set
ldrh r0,[r0]
ldr r1,=UnsetEventId
mov r14,r1
.short 0xF800

End:
mov  r0, r4
mov  r1, r5
blh 0x08022861, r2
mov r0, #0x6
pop {r4-r5}
pop {r1}
bx r1
