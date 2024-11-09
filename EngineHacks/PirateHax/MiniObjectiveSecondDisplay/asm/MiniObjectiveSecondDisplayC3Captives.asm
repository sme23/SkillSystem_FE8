.thumb

.include "../MiniObjectiveSecondDisplayDefs.s"

.global MiniObjectiveSecondDisplayC3Captives
.type MiniObjectiveSecondDisplayC3Captives, %function


		MiniObjectiveSecondDisplayC3Captives:
		mov		r4, r6
		add		r4, #0x34
		
		@Display text
		ldr		r7, =SecondDisplayC3CaptivesParameters
		ldrh	r0, [r7]
		blh		String_GetFromIndex, r1
		mov		r3, r0
		mov		r0, r4
		mov		r1, #0
		mov		r2, #0
		blh		Text_InsertString, r5
		
		@Current amount escorted so far
		ldr		r3, =gEventCounter
		ldrb	r3, [r3]
		mov		r0, r4
		mov		r1, #0x28
		mov		r2, #2
		blh		Text_InsertNumberOr2Dashes, r5
		
		@Slash symbol
		ldr		r3, =gCurrentTextString
		mov		r0, #0x2F
		strh	r0, [r3]
		mov		r0, r4
		mov		r1, #0x30
		mov		r2, #0
		blh		Text_InsertString, r5
		
		@Total needed to win
		ldrb	r3, [r7,#2]
		mov		r0, r4
		mov		r1, #0x38
		mov		r2, #2
		blh		Text_InsertNumberOr2Dashes, r5
		
		ldr		r0, =MiniObjectiveSecondDisplayEnd
		bx		r0
		
		.align
		.ltorg

