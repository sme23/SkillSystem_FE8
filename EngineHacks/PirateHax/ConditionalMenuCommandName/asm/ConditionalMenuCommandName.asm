.thumb

.macro blh to, reg=r3
  ldr \reg, =\to
  mov lr, \reg
  .short 0xf800
.endm

.equ String_GetFromIndex, 0x0800A240

.global ConditionalMenuCommandName
.type ConditionalMenuCommandName, %function


		ConditionalMenuCommandName:
		push	{r14}
		ldr		r3, =ConditionalMenuCommandNamePairing
		
		LoopThroughList:
		ldr		r2, [r3]
		cmp		r2, #0
		beq		NoSpecialCondition
		
			cmp		r2, r0
			beq		EntryFound
			
				add		r3, #8
				b		LoopThroughList
		
		EntryFound:
		ldr		r2, [r3,#4]
		mov		lr, r2
		.short	0xF800
		b		End
	
		NoSpecialCondition:
		blh		String_GetFromIndex, r1
		
		End:
		pop		{r1}
		bx		r1
		
		.align
		.ltorg

