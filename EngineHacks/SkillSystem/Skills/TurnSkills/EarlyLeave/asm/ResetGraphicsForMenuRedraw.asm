@taken from 7743's ShowMenu asm

.thumb

.include "../EarlyLeaveDefs.s"

.global ResetGraphicsForMenuRedraw
.type ResetGraphicsForMenuRedraw, %function


		ResetGraphicsForMenuRedraw:
		push	{r14}
		blh		ClearBG0BG1, r0
		ldr		r0, =gBg2MapBuffer
		mov		r1, #0
		blh		FillBgMap, r2
		mov		r0, #4
		blh		EnableBgSyncByMask, r1
		blh		Text_ResetTileAllocation, r0
		pop		{r0}
		bx		r0
		
		.align
		.ltorg

