.thumb

.include "../MucuDefs.s"

.global MucuCannotIfCanto_RerunAndHit
.type MucuCannotIfCanto_RerunAndHit, %function

.global MucuTargetGiveTakeAllegiancesConditional
.type MucuTargetGiveTakeAllegiancesConditional, %function

.global MucuCannotIfRebelRebelTraveler
.type MucuCannotIfRebelRebelTraveler, %function

.global MucuTargetNewStealSpeedItem
.type MucuTargetNewStealSpeedItem, %function


@--------------------------------------------
@MucuCannotIfCanto_RerunAndHit
@--------------------------------------------


		MucuCannotIfCanto_RerunAndHit:
		push	{r14}
		ldr		r1, [r0,#0x0C]
		mov		r2, #0x40
		tst		r1, r2
		beq		MucuCannotIfCanto_RerunAndHit_CanUse
		
			ldr		r1, =RerunAndHitIDLink
			ldrb	r1, [r1]
			blh		SkillTester, r3
			cmp		r0, #0
			bne		MucuCannotIfCanto_RerunAndHit_CanUse
			
				mov		r0, #0
				b		MucuCannotIfCanto_RerunAndHit_End
		
		MucuCannotIfCanto_RerunAndHit_CanUse:
		mov		r0, #1
		
		MucuCannotIfCanto_RerunAndHit_End:
		pop		{r1}
		bx		r1
		
		.align
		.ltorg


@--------------------------------------------
@MucuTargetGiveTakeAllegiancesConditional
@--------------------------------------------

@r0 = acting unit
@r1 = target


		MucuTargetGiveTakeAllegiancesConditional:
		push	{r4,r14}
		ldr		r2, =gChapterData
		ldrb	r2, [r2,#0x0E]
		
		ldr		r4, =MucuTargetGiveTakeAllegiancesConditionalList
		
		MucuTargetGiveTakeAllegiancesConditional_Loop:
		ldr		r3, [r4]
		cmp		r3, #0
		beq		MucuTargetGiveTakeAllegiancesConditional_LoadCheck
		
			cmp		r2, r3
			beq		MucuTargetGiveTakeAllegiancesConditional_LoadCheck
			
				add		r4, #8
				b		MucuTargetGiveTakeAllegiancesConditional_Loop
		MucuTargetGiveTakeAllegiancesConditional_LoadCheck:
		ldr		r2, [r4,#4]
		mov		lr, r2
		.short	0xF800
		pop		{r4}
		pop		{r1}
		bx		r1
		
		.align
		.ltorg


@--------------------------------------------
@MucuCannotIfRebelRebelTraveler
@--------------------------------------------


		MucuCannotIfRebelRebelTraveler:
		push	{r14}
		ldrb	r0, [r0,#0x1B]
		cmp		r0, #0
		beq		MucuCannotIfRebelRebelTraveler_CanUse
		
			blh		GetUnit, r1
			ldr		r1, =RebelRebelIDLink
			ldrb	r1, [r1]
			blh		SkillTester
			cmp		r0, #0
			beq		MucuCannotIfRebelRebelTraveler_CanUse
			
				mov		r0, #0
				b		MucuCannotIfRebelRebelTraveler_End
				
		MucuCannotIfRebelRebelTraveler_CanUse:
		mov		r0, #1
		
		MucuCannotIfRebelRebelTraveler_End:
		pop		{r1}
		bx		r1
		
		.align
		.ltorg


@--------------------------------------------
@
@--------------------------------------------
