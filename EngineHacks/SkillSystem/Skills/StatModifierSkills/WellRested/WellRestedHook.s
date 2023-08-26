.thumb
.align

.global WellRestedHook
.type WellRestedHook, %function

WellRestedHook:
@hooks at 0x957F8
push {r14}
mov r0,r4
bl PrePrep_WellRestedBonus
mov r0,#0
pop {r1}
bx r1

.ltorg
.align
