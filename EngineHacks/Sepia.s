.thumb
.align

.global GlobalColorModifier
.type GlobalColorModifier, %function

@r0=pointer to palette, r1 = palette bank offset, r2 = number of bytes to copy

GlobalColorModifier:
push	{r4-r6,r14}
mov		r4,r0
asr		r5,r1,#1
lsl		r5,#1
ldr		r6,=#0x20228A8
add		r5,r6
lsr		r6,r2,#1
Loop1:
ldrh	r0,[r4]
bl		GetSepia
strh	r0,[r5]
add		r4,#2
add		r5,#2
sub		r6,#1
cmp		r6,#0
bgt		Loop1
ldr		r0,=#0x300000E
mov		r1,#1
strb	r1,[r0]
pop		{r4-r6}
pop		{r0}
bx		r0

.ltorg

@sepia
@r = r*101/256 + g*197/256 + b*97/512
@g = r*179/512 + g*176/256 + b*11/64
@b = b*35/128 + g*137/256 + b*17/128

@grayscale
@Y = 0.299 R + 0.587 G + 0.114 B
@0.3 = 39/128 
@0.587 = 75/128
@0.114 = 15/128

@r = r*39/128
@g = g*75/128
@b = b*15/128


GetSepia:
push	{r4-r7,r14}
lsl		r4,r0,#27
lsr		r4,#27			@red
lsl		r5,r0,#22
lsr		r5,#27			@green
lsl		r6,r0,#17
lsr		r6,#27			@blue
mov		r7,#0			@new number

@average rgb and triplicate
@(r4 + r5 + r6) / 3

add r4,r5
add r0,r4,r6
mov r1,#3
swi #6

lsl r1,r0,#5
lsl r2,r0,#10
orr r0,r1
orr r0,r2

pop {r4-r7}
pop {r1}
bx r1

.ltorg
.align

@new red
mov		r0,#39
mul		r0,r4
lsr		r0,#7 @/128

cmp		r0,#31
ble		Label1
mov		r0,#31

Label1:
mov		r7,r0 			@red done

@new blue
mov		r0,#15
mul		r0,r4
lsr		r0,#7 @/128

cmp		r0,#31
ble		Label2
mov		r0,#31

Label2:
lsl		r0,#5
orr		r7,r0			@blue done

@new green
mov		r0,#75
mul		r0,r4
lsr		r0,#7 @/128

cmp		r0,#31
ble		Label3
mov		r0,#31

Label3:
lsl		r0,#10
orr		r0,r7			@new color

pop		{r4-r7}
pop		{r1}
bx		r1

.ltorg
.align

