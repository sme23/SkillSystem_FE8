.thumb

.include "../EarlyLeaveDefs.s"

.global DrawSemiTransparentMenuBg
.type DrawSemiTransparentMenuBg, %function


		DrawSemiTransparentMenuBg:
		push	{r4,r14}
		add		sp, #-0x04
		
		blh		ClearBG0BG1, r0
		ldr		r2, =gLCDIOBuffer
		ldrb	r0, [r2,#1]
		mov		r1, #0x1F
		orr		r0, r1
		strb	r0, [r2,#1]
		
		mov		r0, #1
		mov		r1, #0x0B
		mov		r2, #4
		mov		r3, #0
		blh		SetColorEffectsParameters, r4
		
		mov		r0, #0
		str		r0, [sp]
		mov		r1, #1
		mov		r2, #1
		mov		r3, #0
		blh		SetColorEffectsFirstTarget, r4
		mov		r0, #0
		blh		SetColorEffectBackdropFirstTarget, r1
		
		mov		r0, #1
		str		r0, [sp]
		mov		r0, #0
		mov		r1, #0
		mov		r2, #0
		mov		r3, #1
		blh		SetColorEffectsSecondTarget, r4
		mov		r0, #1
		blh		SetColorEffectBackdropSecondTarget, r1
		
		mov		r0, #0
		blh		Text_SetFont, r1
		blh		Font_LoadForUI, r0
		blh		LoadNewUIGraphics, r0
		
		add		sp, #0x04
		pop		{r4}
		pop		{r0}
		bx		r0
		
		.align
		.ltorg

