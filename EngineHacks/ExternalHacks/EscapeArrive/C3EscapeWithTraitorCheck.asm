.thumb

.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.equ gChapterData, 0x0202BCF0
.equ gActiveUnit, 0x03004E50
.equ SetEventId, 0x08083D80
.equ GetUnit, 0x08019430
.equ gEventCounter, 0x03000568

.global C3EscapeWithTraitorCheck
.type C3EscapeWithTraitorCheck, %function


		C3EscapeWithTraitorCheck:
		push	{r14}
		ldr		r0, =gChapterData
		ldrb	r0, [r0,#0x0E]
		ldr		r1, =EscapeHubC3IDLink
		ldrb	r1, [r1]
		cmp		r0, r1
		bne		End
		
			ldr		r0, =gActiveUnit
			ldr		r0, [r0]
			ldrb	r0, [r0,#0x1B]
			cmp		r0, #0
			beq		End
			
				blh		GetUnit, r1
				ldr		r1, =RebelRebelIDLink
				ldrb	r1, [r1]
				blh		SkillTester, r3
				cmp		r0, #0
				beq		End
				
					ldr		r1, =gEventCounter
					ldrb	r0, [r1]
					add		r0, #1
					strb	r0, [r1]
					cmp		r0, #5
					blt		End
					
						mov		r0, #3
						blh		SetEventId, r1
						
		End:
		pop		{r0}
		bx		r0
		
		.align
		.ltorg

