
#include "gbafe.h"

typedef struct NewBattleHit NewBattleHit;

struct NewBattleHit // Skill System's new 8-byte long rounds data.
{
	unsigned attributes : 19;
    unsigned info       : 5;
    signed   hpChange   : 8;
	u8 skillID;
	s8 damage;
	u8 pad2[2]; // These are things, but I don't know what they are.
};

extern struct NewBattleHit NewBattleHitArray[];

#define BATTLE_HIT_ATTR_ISATTACKER BATTLE_HIT_ATTR_17
#define BATTLE_HIT_ATTR_ISDEFENDER BATTLE_HIT_ATTR_18


bool IsFollowupAttack(NewBattleHit* battleHit) {
	
	 return (&NewBattleHitArray[0] != battleHit);
}		

			