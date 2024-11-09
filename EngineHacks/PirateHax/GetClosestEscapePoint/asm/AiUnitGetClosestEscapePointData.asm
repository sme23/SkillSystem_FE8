.thumb

.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.equ gChapterData, 0x0202BCF0
.equ gActiveUnit, 0x03004E50
.equ gGreenMasterAiEscapeTable, 0x085A828C
.equ gRedMasterAiEscapeTable, 0x085A8188
.equ gMapMovement, 0x0202E4E0

.global AiUnitGetClosestEscapePointData
.type AiUnitGetClosestEscapePointData, %function


		AiUnitGetClosestEscapePointData:
		push	{r4-r7,r14}
		mov		r1, #0
		mov		r5, #0
		ldr		r6, =gChapterData
		mov		r7, #0x0E
		ldsb	r7, [r6,r7]
		
		ldr		r1, =EscapeHubC3IDLink
		ldrb	r1, [r1]
		cmp		r1, r7
		bne		PhaseCheck
		
			ldr		r0, =gActiveUnit
			ldr		r0, [r0]
			ldr		r1, =RebelRebelIDLink
			ldrb	r1, [r1]
			blh		SkillTester, r3
			cmp		r0, #0
			bne		LoadEnemyTable
			
				b		LoadNPCTable
		
		PhaseCheck:
		mov		r4, #0xFF
		ldrb	r0, [r6,#0x0F]
		cmp		r0, #0x40
		beq		LoadNPCTable
		
			cmp		r0, #0x80
			beq		LoadEnemyTable
			
				mov		r0, #0
				beq		End2
				
		LoadNPCTable:
		ldr		r1, =gGreenMasterAiEscapeTable
		b		GetChapterAiEscapeTable
		
		LoadEnemyTable:
		ldr		r1, =gRedMasterAiEscapeTable
		
		GetChapterAiEscapeTable:
		lsl		r0, r7, #2
		add		r0, r1
		ldr		r1, [r0]
		mov		r0, #0
		lsl		r0, #2
		add		r1, r0
		ldrb	r0, [r1]
		cmp		r0, #0xFF
		beq		End
		
		ldr		r0, =gMapMovement
		ldr		r3, [r0]
		mov		r2, r1
		
		EscapePointLoop:
		ldrb	r0, [r2,#1]
		lsl		r0, #2
		add		r0, r3
		ldrb	r1, [r2]
		ldr		r0, [r0]
		add		r1, r0
		ldrb	r0, [r1]
		cmp		r0, #0x78
		bhi		NextEscapePoint
		
			mov		r0, #0
			ldsb	r0, [r1,r0]
			cmp		r4, r0
			ble		NextEscapePoint
			
				ldrb	r4, [r1]
				mov		r5, r2
				
				NextEscapePoint:
				add		r2, #4
				ldrb	r0, [r2]
				cmp		r0, #0xFF
				bne		EscapePointLoop
				
		End:
		mov		r0, r5
		
		End2:
		pop		{r4-r7}
		pop		{r1}
		bx		r1
		
		.align
		.ltorg

