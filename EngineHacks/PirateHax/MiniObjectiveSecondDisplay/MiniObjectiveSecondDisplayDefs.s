
.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.equ MiniObjectiveSecondDisplayEnd, 0x0808D46F
.equ Text_InsertString, 0x08004480
.equ String_GetFromIndex, 0x0800A240
.equ gEventCounter, 0x03000568
.equ Text_InsertNumberOr2Dashes, 0x080044A4
.equ gCurrentTextString, 0x0202A6AC
