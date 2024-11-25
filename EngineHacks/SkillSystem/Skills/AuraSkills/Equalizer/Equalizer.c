#include "gbafe.h"

extern bool NewAuraSkillCheck(Unit* unit, int skillID, int allyOption, int maxRange);

extern u8 EqualizerID_Link;
extern u8 EqualizerRange_Link;

void Equalizer(BattleUnit* bunitA, BattleUnit* bunitB) {

	if (gBattleStats.config & (BATTLE_CONFIG_REAL | BATTLE_CONFIG_SIMULATE))
	{

	}
	else
	{
		return; //return if not a real battle
	}


	int atkA = bunitA->battleAttack;
	int atkB = bunitB->battleAttack;


	int meanAtk;
	if (atkA == atkB)
	{
		meanAtk = atkA;
	}
	else
	{
		meanAtk = (atkA + atkB) / 2;
	}
	if(NewAuraSkillCheck(&bunitA->unit, EqualizerID_Link, 0x0, EqualizerRange_Link)) { //does an ally check for equalizer skill
		if(atkA < atkB && (bunitB->canCounter == true))
		{	//if equalizer unit's damage is less than enemy's damage
			bunitA->battleAttack = meanAtk;
			bunitB->battleAttack = meanAtk;
		}	//add the difference between meanDamage and opponent battle Def to attack
	}
	if(NewAuraSkillCheck(&bunitB->unit, EqualizerID_Link, 0x0, EqualizerRange_Link)) { //does an ally check for equalizer skill
		if(atkB < atkA && (bunitA->canCounter == true))
		{	//if equalizer unit's damage is less than enemy's damage
			bunitA->battleAttack = meanAtk;
			bunitB->battleAttack = meanAtk;
		}	//add the difference between meanDamage to attack
	}
}
