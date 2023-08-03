
# make -C EngineHacks/SkillSystem/Skills/RoundsSkills/EyeForAnEye

all: EyeForAnEye.lyn.event

.PHONY: all

# we do what we have to do
LYN ?= ../../../../../EventAssembler/Tools/lyn

AS := arm-none-eabi-as

%.lyn.event: %.o
	$(LYN) $< > $@ || rm $@

%.o: %.s
	$(AS) $< -o $@
