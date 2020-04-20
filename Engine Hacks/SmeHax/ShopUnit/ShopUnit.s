.thumb
.align

@function prototypes :3

.global ShopUnitCommandUsability
.type ShopUnitCommandUsability, %function

.global ShopUnitCommandEffect
.type ShopUnitCommandEffect, %function


.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm


