.thumb

.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.equ gActiveUnit, 0x03004E50
.equ GetItemWType, 0x08017548
.equ GetUnitEquippedItemSlot, 0x08016B58
.equ GetItemWeight, 0x0801760C

.global IsItemStealable
.type IsItemStealable, %function


		IsItemStealable:
		push	{r4-r7,r14}
		mov		r4, r0
		mov		r5, r1
		ldr		r6, =gActiveUnit
		mov		r7, #0 @rusty hook "saves" remaining
		
		@Cannot steal weapon/tome if equipped
		blh		GetUnitEquippedItemSlot, r1
		cmp		r0, r5
		beq		RetFalse
		
		@Rusty hook check
		ldr		r0, [r6]
		blh		GetUnitEquippedItem, r1
		mov		r1, #0xFF
		and		r0, r1
		ldr		r1, =RustyHookIDLink
		ldrb	r1, [r1]
		cmp		r0, r1
		bne		SpeedCheck
		
			add		r7, #1
		
		SpeedCheck:
		mov		r2, #0x16
		ldr		r0, [r6]
		ldsb	r0, [r0,r2]
		ldsb	r1, [r4,r2]
		cmp		r0, r1
		bge		IsItemInvalidFromSpeed
		
			sub		r7, #1
			
		IsItemInvalidFromSpeed:
		cmp		r7, #0
		blt		RetFalse
		
		@Wt check (autosucceed if item)
		lsl		r0, r5, #1
		add		r0, #0x1E
		ldrh	r0, [r4,r0]
		mov		r5, r0
		blh		GetItemWType, r1
		cmp		r0, #9
		beq		RetTrue
		
			ldr		r0, [r6]
			blh		prConGetter, r1
			mov		r6, r0
			
				mov		r0, r5
				blh		GetItemWeight, r1
				cmp		r6, r0
				bge		RetTrue
				
					mov		r0, r7
					b		End
		
		RetFalse:
		mov		r0, #0
		b		End
		
		RetTrue:
		mov		r0, #1
		
		End:
		pop		{r4-r7}
		pop		{r1}
		bx		r1
		
		.align
		.ltorg

