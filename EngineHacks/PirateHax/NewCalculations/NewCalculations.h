bool CanBattleUnitGainExp(BattleUnit* actor, BattleUnit* target);
bool CanBattleUnitGainLevels(BattleUnit* battleUnit);
int GetLevelDifference(BattleUnit* actor, BattleUnit* target);
int GetNPCStatIncrease(int growth);

#define CA_NO_EXP CA_NEGATE_LETHALITY

#define NO_WEXP 0
#define D_WEXP 51
#define C_WEXP 101
#define B_WEXP 151
#define A_WEXP 201
#define S_WEXP 251

#define NO_RANK 0
#define D_RANK 2
#define C_RANK 3
#define B_RANK 4
#define A_RANK 5
#define S_RANK 6



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