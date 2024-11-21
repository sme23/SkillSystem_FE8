.thumb

.include "../RecoilAxeDefs.s"

.global RecoilAxePostBattle
.type RecoilAxePostBattle, %function


@-------------------------------------------
@RecoilAxePostBattle
@-------------------------------------------


		RecoilAxePostBattle:
		push	{r14}
		
		@skip if dead
		ldrb	r0, [r4,#0x13]
		cmp		r0, #0
		beq		RecoilAxePostBattle_End
		
			@skip if didn't attack
			ldrb	r0, [r6,#0x11]
			cmp		r0, #2
			bne		RecoilAxePostBattle_End
			
			ldrb	r0, [r6,#0x0C]
			ldrb	r1, [r4,#0x0B]
			cmp		r0, r1
			bne		RecoilAxePostBattle_End
			
				@check for Recoil Axe
				mov		r0, #0x4A
				ldr		r1, =gActiveBattleUnit
				ldrb	r0, [r1,r0]
				ldr		r1, =RecoilAxeIDLink
				ldrb	r1, [r1]
				cmp		r0, r1
				bne		RecoilAxePostBattle_End
				
					@Recoil if able to
					@mov		r0, r5
					@ldrb	r1, [r4,#0x10]
					@ldrb	r2, [r4,#0x11]
					
					mov		r0, r4
					ldrb	r1, [r5,#0x10]
					ldrb	r2, [r5,#0x11]
					
					blh		_prGetSmitePosition, r3
					ldrb	r0, [r4,#0x10]
					cmp		r0, r1
					bne		RecoilAxePostBattle_Effect
					
					ldrb	r0, [r4,#0x11]
					cmp		r0, r2
					beq		RecoilAxePostBattle_End
					
		@Recoil effect
		RecoilAxePostBattle_Effect:
		
		@strb	r1, [r0,#0x13]
		@strb	r2, [r0,#0x14]
		
		strb	r1, [r6,#0x0E]
		strb	r2, [r6,#0x0F]
		
		@strb	r1, [r4,#0x10]
		@strb	r2, [r4,#0x11]
		@ldr		r0, =gActiveBattleUnit
		@strb	r1, [r4,#0x10]
		@strb	r2, [r4,#0x11]
		
		blh		MU_EndAll, r0
		
		@Animation setup
		ldr		r0, =GetFacingDirection
		mov		lr, r0
		ldrb	r0, [r5,#0x10]
		ldrb	r1, [r5,#0x11]
		ldrb	r2, [r6,#0x0E]
		ldrb	r3, [r6,#0x0F]
		.short	0xF800
		mov		r1, r0
		mov		r0, r4
		blh		_p6CUnitMoveAnim_rConstruct, r2
		
		@Apply changed position
		mov		r0, r4
		ldrb	r1, [r6,#0x0E]
		ldrb	r2, [r6,#0x0F]
		strb	r1, [r4,#0x10]
		strb	r2, [r4,#0x11]
		blh		ApplyUnitMovement, r1
		blh		SMS_UpdateFromGameData, r0
		
		RecoilAxePostBattle_End:
		pop		{r0}
		bx		r0
		
		.align
		.ltorg


@-------------------------------------------
@
@-------------------------------------------
