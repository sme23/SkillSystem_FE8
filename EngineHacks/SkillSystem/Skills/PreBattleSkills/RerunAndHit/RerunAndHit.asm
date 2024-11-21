.thumb

.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.global RerunAndHit
.type RerunAndHit, %function


		RerunAndHit:
		push	{r4,r14}
		mov		r4, r0
		
		@If viewing during stat screen (defender has no class pointer), skip
		ldr		r1, [r1,#4]
		cmp		r1, #0
		beq		End
		
			@If not Cantoing, skip
			ldr		r1, [r0,#0x0C]
			mov		r2, #0x40
			tst		r1, r2
			beq		End
			
				ldr		r1, =RerunAndHitIDLink
				ldrb	r1, [r1]
				blh		SkillTester, r3
				cmp		r0, #0
				beq		End
				
					@Lower Atk by 10
					mov		r1, #0x5A
					ldrh	r0, [r4,r1]
					sub		r0, #10
					cmp		r0, #0
					bge		StoreAtk
					
						mov		r0, #0
						
						StoreAtk:
						strh	r0, [r4,r1]
						
						@Lower AS by 10
						mov		r1, #0x5E
						ldrh	r0, [r4,r1]
						sub		r0, #10
						cmp		r0, #0
						bge		StoreAS
						
							mov		r0, #0
							
							StoreAS:
							strh	r0, [r4,r1]
						
		End:
		pop		{r4}
		pop		{r0}
		bx		r0
		
		.align
		.ltorg

