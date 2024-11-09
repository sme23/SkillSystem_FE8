
.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.equ gpKeyState, 0x0858791C
.equ Menu_DrawHoverThing, 0x0804F0E0
.equ gChapterData, 0x0202BCF0
.equ m4aSongNumStart, 0x080D01FC
