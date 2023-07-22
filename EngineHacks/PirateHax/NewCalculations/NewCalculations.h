bool CanBattleUnitGainExp(BattleUnit* actor, BattleUnit* target);
bool CanBattleUnitGainLevels(BattleUnit* battleUnit);
int GetLevelDifference(BattleUnit* actor, BattleUnit* target);
int GetNPCStatIncrease(int growth);

#define CA_NO_EXP CA_NEGATE_LETHALITY

#define D_RANK 51
#define C_RANK 101
#define B_RANK 151
#define A_RANK 201

struct CharacterMagicData {
	/* 00 */ s8 baseMag;
	/* 01 */ s8 growthMag;
};

struct ClassMagicData {
	/* 00 */ s8 baseMag;
	/* 01 */ s8 growthMag;
	/* 02 */ s8 maxMag;
	/* 03 */ u8 promotionMag; 
};

extern const struct ClassMagicData MagClassTable[];
extern const struct CharacterMagicData MagCharTable[];