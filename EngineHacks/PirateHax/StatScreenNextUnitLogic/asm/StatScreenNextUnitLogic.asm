.thumb

.macro blh to, reg=r5
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.equ GetUnit, 0x08019430
.equ gSomeUnitId, 0x0203E764

.global StatScreenNextUnitLogic
.type StatScreenNextUnitLogic, %function


		StatScreenNextUnitLogic:
		push	{r4-r7,r14}
		mov		r7, r1
		ldrb	r0, [r0,#0x0B]
		lsl		r0, #0x18
		asr		r0, #0x18
		mov		r6, #0xC0
		and		r6, r0
		mov		r4, r0
		
		StatScreenNextUnitLogic_Loop:
		add		r4, r7
		mov		r0, #0x3F
		and		r4, r0
		add		r0, r6, r4
		blh		GetUnit, r1
		
			@Valid unit
			mov		r5, r0
			cmp		r5, #0
			beq		StatScreenNextUnitLogic_Loop
			
				ldr		r0, [r5]
				cmp		r0, #0
				beq		StatScreenNextUnitLogic_Loop
				
			@Dead unit state check
			ldr		r0, =gSomeUnitId
			ldrh	r3, [r0,#2]
			mov		r0, #1
			tst		r0, r3
			@beq		UndeployedStateCheck
			beq		EarlyLeaveDeployedCheck
			
				ldr		r0, [r5,#0x0C]
				mov		r1, #4
				tst		r0, r1
				bne		StatScreenNextUnitLogic_Loop
				
			EarlyLeaveDeployedCheck:
			mov		r0, #0x40
			tst		r0, r3
			beq		UndeployedStateCheck
			
				ldr		r0, [r5,#0x0C]
				mov		r1, #8
				tst		r0, r1
				beq		StatScreenNextUnitLogic_Loop
				
					push	{r3}
					mov		r0, r5
					blh		IsUnitOnEarlyLeaveReplacementList, r1
					pop		{r3}
					cmp		r0, #0
					beq		StatScreenNextUnitLogic_Loop
				
			UndeployedStateCheck:
			mov		r0, #2
			tst		r0, r3
			beq		LinkArenaHideUnitsCheck
			
				ldr		r0, [r5,#0x0C]
				mov		r1, #8
				tst		r0, r1
				bne		StatScreenNextUnitLogic_Loop
				
			LinkArenaHideUnitsCheck:
			mov		r0, #4
			tst		r0, r3
			beq		RoofCheck
			
				ldr		r0, [r5,#0x0C]
				mov		r1, #0x80
				lsl		r1, #2
				tst		r0, r1
				bne		StatScreenNextUnitLogic_Loop
				
			RoofCheck:
			mov		r0, #8
			tst		r0, r3
			beq		REMUCheck
			
				ldr		r0, [r5,#0x0C]
				mov		r1, #0x80
				tst		r0, r1
				bne		StatScreenNextUnitLogic_Loop
				
			REMUCheck:
			mov		r0, #0x10
			tst		r0, r3
			beq		SupplyCheck
			
				ldr		r0, [r5,#0x0C]
				mov		r1, #0x80
				lsl		r1, #9
				tst		r0, r1
				bne		StatScreenNextUnitLogic_Loop
				
			SupplyCheck:
			mov		r0, #0x20
			and		r0, r3
			ldr		r3, [r5,#4]
			cmp		r0, #0
			beq		GorgonEggCheck
			
				ldr		r0, [r5]
				ldr		r0, [r0,#0x28]
				ldr		r1, [r3,#0x28]
				orr		r0, r1
				mov		r1, #0x80
				lsl		r1, #2
				tst		r0, r1
				bne		StatScreenNextUnitLogic_Loop
				
			GorgonEggCheck:
			ldrb	r0, [r3,#4]
			cmp		r0, #0x62
			beq		StatScreenNextUnitLogic_Loop
			
				cmp		r0, #0x34
				beq		StatScreenNextUnitLogic_Loop
		
		mov		r0, r5
		pop		{r4-r7}
		pop		{r1}
		bx		r1
		
		.align
		.ltorg

