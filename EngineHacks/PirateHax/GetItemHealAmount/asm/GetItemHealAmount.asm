.thumb

.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.global GetItemHealAmount
.type GetItemHealAmount, %function


		GetItemHealAmount:
		push	{r4,r14}
		mov		r4, #0
		
		mov		r2, #0xFF
		and		r1, r2
		ldr		r3, =StaffHealingList
		
		GetItemHealAmount_Loop:
		ldrb	r2, [r3]
		cmp		r2, #0
		beq		GetItemHealAmount_End
		
			cmp		r1, r2
			beq		GetItemHealAmount_EntryFound
			
				add		r3, #2
				b		GetItemHealAmount_Loop
		
		GetItemHealAmount_EntryFound:
		ldrb	r4, [r3,#1]
		blh		prGotoMagGetter, r1
		add		r4, r0
		cmp		r4, #80
		ble		GetItemHealAmount_End
		
			mov		r4, #80
		
		GetItemHealAmount_End:
		mov		r0, r4
		pop		{r4}
		pop		{r1}
		bx		r1
		
		.align
		.ltorg

