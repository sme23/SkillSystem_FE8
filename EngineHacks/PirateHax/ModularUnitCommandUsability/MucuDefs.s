
.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.equ gActiveUnit, 0x03004E50
.equ GetItemAttributes, 0x0801756C
.equ CanUnitUseWeapon, 0x08016750
.equ MakeTargetListForWeapon, 0x080251B4
.equ GetTargetListSize, 0x0804FD28

.equ gUnitSubject, 0x02033F3C
.equ AddTarget, 0x0804F8BC
.equ gGameState, 0x0202BCB0
.equ MakeGiveTargetList, 0x08025594
.equ MakeTakeTargetList, 0x080254E0
.equ AreAllegiancesAllied, 0x08024D8C
.equ AreAllegiancesEqual, 0x08024DA4
.equ GetUnit, 0x08019430
.equ CanUnitRescue, 0x0801831C

.equ gChapterData, 0x0202BCF0
.equ GetItemWType, 0x08017548
.equ CanUnitUseItem, 0x08028870
.equ CanUnitNotUseMagic, 0x08018D08

.equ IsItemStealable, 0x08017054
.equ GetItemWType, 0x08017548
.equ GetUnitEquippedItemSlot, 0x08016B58
.equ GetItemWeight, 0x0801760C
