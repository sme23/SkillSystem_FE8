#include "PreBattleSkills.h"

/*
	A few style notes:
	
	- The structure of each function can be expressed in the form of a sentence.
	  This is laid out mostly literally in the form of comments before each check and
	  effect involved in each skill function. This code is a source of learning for
	  newcoming hackers, so having these comments ensures it's very clear what each
	  section of the code is doing.

	- The last check done before applying a skill's effect should be the SkillTester
	  call wherever possible. SkillTester has a lot of overhead to each call, so
	  exiting the function before calling it is a small optimization.
	
	
	
*/



// Air Raid: Grants +5 or +15 on a stat when on a tile enemy cannot enter
void AirRaidAtk(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if ( 
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and the defender cannot pass the tile the attacker is standing on
		&& !CanUnitCrossTerrain(bunitB, bunitA.terrainId)
		//and the attacker has the skill
		&& SkillTester(bunitA, AirRaidAtkID_Link)
	) {
		//increase stat by 5
		bunitA.battleAttack += 5;
	}
}

void AirRaidSpd(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if ( 
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and the defender cannot pass the tile the attacker is standing on
		&& !CanUnitCrossTerrain(bunitB, bunitA.terrainId)
		//and the attacker has the skill
		&& SkillTester(bunitA, AirRaidSpdID_Link)
	) {
		//increase attacker's stat by 5
		bunitA.battleSpeed += 5;
	}
}

void AirRaidDef(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if ( 
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and the defender cannot pass the tile the attacker is standing on
		&& !CanUnitCrossTerrain(bunitB, bunitA.terrainId)
		//and the attacker has the skill
		&& SkillTester(bunitA, AirRaidDefID_Link)
	) {
		//if the attacker isn't dealing magic damage
		if (!(bunitA->weaponAttributes & IA_MAGICDAMAGE|IA_MAGIC)) {
			
			//increase stat by 5
			bunitA.battleDefense += 5;
		}
	}
}

void AirRaidCri(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if ( 
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and the defender cannot pass the tile the attacker is standing on
		&& !CanUnitCrossTerrain(bunitB, bunitA.terrainId)
		//and the attacker has the skill
		&& SkillTester(bunitA, AirRaidCriID_Link)
	) {
		//increase stat by 15
		bunitA.battleCritRate += 15;
	}
}

void AirRaidHit(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if ( 
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and the defender cannot pass the tile the attacker is standing on
		&& !CanUnitCrossTerrain(bunitB, bunitA.terrainId)
		//and the attacker has the skill
		&& SkillTester(bunitA, AirRaidHitID_Link)
	) {
		//increase stat by 15
		bunitA.battleHitRate += 15;
	}
}

void AirRaidAvo(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if ( 
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and the defender cannot pass the tile the attacker is standing on
		&& !CanUnitCrossTerrain(bunitB, bunitA.terrainId)
		//and the attacker has the skill
		&& SkillTester(bunitA, AirRaidAvoID_Link)
	) {
		//increase stat by 15
		bunitA.battleAvoidRate += 15;
	}
}

void AirRaidRes(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if ( 
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and the defender cannot pass the tile the attacker is standing on
		&& !CanUnitCrossTerrain(bunitB, bunitA.terrainId)
		//and the attacker has the skill
		&& SkillTester(bunitA, AirRaidResID_Link)
	) {
		//if the attacker is dealing magic damage
		if (GetItemAttributes(bunitA->weapon) & IA_MAGICDAMAGE|IA_MAGIC) {
			
			//increase stat by 5
			bunitA.battleDefense += 5;
		}
	}
}


// Analytic: +10 attack if speed is less than opponent's by 4 points or more. 
// If between 1-3 points, then +5 attack.
void Analytic(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		// if our speed is less than our opponent's
		bunitA.battleSpeed < bunitB.battleSpeed
		// and we have the skill
		&& SkillTester(bunitA, AnalyticID_Link)
	) {
		// increase attack by 5
		bunitA.battleAttack += 5;
		
		// if our speed is at least 4 points less than our opponent's
		if ((bunitB.battleSpeed - bunitA.battleSpeed) >= 4) {
			// increase attack by 5
			bunitA.battleAttack += 5;
		}
	}	
}

// Arcane Blade: When initiating battle at 1 range: Add 3+(Mag/2) to Hit and Crit.
void ArcaneBlade(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we initiated the battle
		&& bunitA = &gBattleActor
		//and we are at 1 range
		&& gBattleStats.range == 1
		//and we have the skill
		&& SkillTester(bunitA, ArcaneBladeID_Link)
	) {
		// add 3+(Mag/2) to Hit
		bunitA.battleHitRate += 3+(bunitA._u3A/2);
		// add 3+(Mag/2) to Crit
		bunitA.battleCritRate += 3+(bunitA._u3A/2);
	}
}


// Assassinate: When initiating battle at 1 range: 
// +2 Damage, double attacks occur before counter.
// This function only handles the +2 damage.
void AssassinateDamageBonus(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we initiated the battle
		&& bunitA == &gBattleActor
		//and we are at 1 range
		&& gBattleStats.range == 1
		//and we have the skill
		&& SkillTester(bunitA, AssassinateID_Link)
	) {
		// add 2 damage
		bunitA.battleAttack += 2;
	}
}


// Axefaith: Axes can't lose durability, 
// and grants +Luck*1.5 Hit when wielding axes.
// This function only handles the +luck*1.5 hit.
void AxeFaith(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if our weapon is an axe
		bunitA.weaponType == ITYPE_AXE
		//and we have the skill
		&& SkillTester(bunitA, AxeFaithID_Link)
	) {
		// add luck*1.5 to hit
		// it isn't directly multiplied by 1.5 because the GBA can't handle floats
		bunitA.battleHitRate += (bunitA.unit.lck * 3) / 2;
		
	}
}

// Battle Veteran: Gain +1 damage and +5% Hit per 10 levels unit has.
void BattleVeteran(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, BattleVeteranID_Link)
	) {
		//get our current level
		int level = bunitA.unit.level;
		//if we are promoted
		if (UNIT_CATTRIBUTES(bunitA) & CA_PROMOTED) {
			//add 20 to level
			level += 20;
		}
		//get levels/10
		level /= 10;
		
		//add value to damage
		bunitA.battleAttack += level;
		
		//add value*5 to hit
		bunitA.battleHitRate += level*5;
	}
}


void DuelistsBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we have the skill
		&& SkillTester(bUnitA, DuelistsBlowID_Link)
	) {
		//add 30 to avoid
		bunitA.battleAvoidRate += 30;
	}
}

void DeathBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we have the skill
		&& SkillTester(bUnitA, DeathBlowID_Link)
	) {
		//add 20 to crit
		bunitA.battleCritRate += 20;
	}
}

void DartingBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we have the skill
		&& SkillTester(bUnitA, DartingBlowID_Link)
	) {
		//add 5 to attack speed
		bunitA->battleSpeed += 5;
	}
}

void WardingBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we have the skill
		&& SkillTester(bUnitA, WardingBlowID_Link)
	) {
		//if the defender is dealing magic damage
		if (bunitB->weaponAttributes & IA_MAGICDAMAGE|IA_MAGIC) {
			
			//increase battle defense by 20
			bunitA->battleDefense += 20;
		}
	}
}

void CertainBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we have the skill
		&& SkillTester(bUnitA, CertainBlowID_Link)
	) {
		//add 40 to hit
		bunitA->battleHitRate += 40;
	}
}

void ArmoredBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we have the skill
		&& SkillTester(bUnitA, ArmoredBlowID_Link)
	) {
		//if the defender isn't dealing magic damage
		if (!(bunitB->weaponAttributes & IA_MAGICDAMAGE|IA_MAGIC)) {
			
			//increase battle defense by 10
			bunitA->battleDefense += 10;
		}
	}
}

void QuickDraw(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we have the skill
		&& SkillTester(bUnitA, QuickDrawID_Link)
	) {
		//increase attack by 4
		bunitA->battleAttack += 4;
	}
}

// Chivalry: When foe is at full HP, attack and def/res +2.
void Chivalry(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and the defender has full HP
		&& (bunitB->unit.maxHP == bunitB->unit.curHP)
		//and we have the skill
		&& SkillTester(bUnitA, ChivalryID_Link)
	) {
		//add 2 to attack and defense
		bunitA->battleAttack += 2;
		bunitA->battleDefense += 2;
	}
}

// Pragmatic: When foe is not at full HP, attack +3 and def/res+1.
void Pragmatic(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and the defender does not have full HP
		&& (bunitB->unit.maxHP > bunitB->unit.curHP)
		//and we have the skill
		&& SkillTester(bUnitA, PragmaticID_Link)
	) {
		//add 3 to attack and 1 to defense
		bunitA->battleAttack += 3;
		bunitA->battleDefense += 1;
	}
}

void HeroesDeathBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are the attacker
		bunitA == &gBattleActor
		//and we aren't in a simulated battle
		&& !(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and we have the skill
		&& SkillTester(bUnitA, HeroesDeathBlowID_Link)
	) {
		//add 6 to attack 
		bunitA.battleAttack += 6;
	}
}

// Blue Flame: Attack +2. If adjacent to an ally, Attack +4.
// This function only handles the base +2 to attack.
void BlueFlame(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, BlueFlameID_Link)
	) {
		//add 2 to attack
		bunitA.battleAttack += 2;
	}
}

void Swordbreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if defender's weapon is a sword
		bunitB->weaponType == ITYPE_SWORD
		//and we have the skill
		&& SkillTester(bunitA, SwordbreakerID_Link)
	) {
		//add 50 to hit and avoid
		bunitA->battleHitRate += 50;
		bunitA->battleAvoidRate += 50;
	}
}

void Lancebreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if defender's weapon is a lance
		bunitB->weaponType == ITYPE_LANCE
		//and we have the skill
		&& SkillTester(bunitA, LancebreakerID_Link)
	) {
		//add 50 to hit and avoid
		bunitA->battleHitRate += 50;
		bunitA->battleAvoidRate += 50;
	}
}

void Axebreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if defender's weapon is an axe
		bunitB->weaponType == ITYPE_AXE
		//and we have the skill
		&& SkillTester(bunitA, AxebreakerID_Link)
	) {
		//add 50 to hit and avoid
		bunitA->battleHitRate += 50;
		bunitA->battleAvoidRate += 50;
	}
}

void Bowbreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if defender's weapon is a bow
		bunitB->weaponType == ITYPE_BOW
		//and we have the skill
		&& SkillTester(bunitA, BowbreakerID_Link)
	) {
		//add 50 to hit and avoid
		bunitA->battleHitRate += 50;
		bunitA->battleAvoidRate += 50;
	}
}

void Tomebreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if defender's weapon is a staff
		bunitB->weaponType == ITYPE_STAFF
		//or defender's weapon is an anima tome
		|| bunitB->weaponType == ITYPE_ANIMA
		//or defender's weapon is a light tome
		|| bunitB->weaponType == ITYPE_LIGHT
		//or defender's weapon is a dark tome
		|| bunitB->weaponType == ITYPE_DARK
		//and we have the skill
		&& SkillTester(bunitA, TomebreakerID_Link)
	) {
		//add 50 to hit and avoid
		bunitA->battleHitRate += 50;
		bunitA->battleAvoidRate += 50;
	}
}
// Catching Up: If foe doubles unit, unit's damage increases 
// by the amount foe is above the doubling threshold.
void CatchingUp(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	
	if (
		//if foe doubles unit
		(bunitB->battleSpeed - bunitA->battleSpeed) > BATTLE_FOLLOWUP_SPEED_THRESHOLD
		//and unit has the skill
		&& SkillTester(bunitA, CatchingUpID_Link)
	) {
		//increase attack by amount foe is above threshold
		int bonus = (bunitB->battleSpeed - bunitA->battleSpeed) - BATTLE_FOLLOWUP_SPEED_THRESHOLD;
		bunitA.battleAttack += bonus;
	}
}

// Chaos Style: AS +3 during combat with a physical 
// weapon against a foe armed with magic or vice versa.
void ChaosStyle(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we do not have the same weapon type (physical, magic)
		(bunitA->weaponAttributes & IA_MAGICDAMAGE|IA_MAGIC) != (bunitB->weaponAttributes & IA_MAGICDAMAGE|IA_MAGIC)
		//and we have the skill
		&& SkillTester(bunitA, ChaosStyleID_Link)
	) {
		//add 3 to attack speed
		bunitA->battleSpeed += 3;
	}
}

// Charge: Gain +1 damage for every two squares moved.
// Bonus disappears on enemy phase.
void Charge(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, ChargeID_Link)
	) {
		//add squares moved /2 to attack
		bunitA->battleAttack += ( gActionData.moveCount / 2 );
	}
}

// Charge+: If unit has used up all movement, gain brave effect.
void ChargePlus(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have used all movement
		//(battle units have the full move stat stored in movBonus)
		bunitA->unit.movBonus <= gActionData.moveCount
		//and we have the skill
		&& SkillTester(bunitA, ChargePlusID_Link)
	) {
		//apply brave effect
		bunitA->weaponAttributes &= IA_BRAVE;
	}
}

//Critical Pierce: Nullify the enemy's crit avoid rate.
void CriticalPierce(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, CriticalPierceID_Link)
	) {
		//nullify the enemy's crit avoid
		bunitB->battleDodgeRate = 0;
	}
}

//Critical Force: Base critical is Skl * 1.5.
void CriticalForce(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, CriticalForceID_Link)
	) {
		//add skill to crit
		bunitA->battleCritRate += bunitA->unit.skl;
	}
}

//Killing Machine: Total critical rate is doubled.
void KillingMachine(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, KillingMachineID_Link)
	) {
		//double crit rate
		bunitA->battleCritRate *= 2;
	}
}

//Crit Boost: +15 critical rate.
void CritUp(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, CritUpID_Link)
	) {
		//add 15 to crit rate
		bunitA->battleCritRate += 15;
	}
}

// Cultured: If attacking next to a unit with Nice Thighs, move again.
// -50 hit against units with Nice Thighs.
// This function only handles the -50 hit.
void Cultured(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, CulturedID_Link)
		//and our opponent has Nice Thighs
		&& SkillTester(bunitB, NiceThighsID_Link)
	) {
		//subtract 50 from hit
		bunitA->battleHitRate -= 50;
	}	
}

// Dancing Blade: +4 Attack Speed/-2 Damage 
// when unit's Con is lower than the enemy.
void DancingBlade(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if our con is lower than the enemy's
		//(battle units store their full con in conBonus)
		bunitA->unit.conBonus < bunitB->unit.conBonus
		//and we have the skill
		&& SkillTester(bunitA, DancingBladeID_Link)
	) {
		//+4 attack speed
		bunitA->battleSpeed += 4;
		//-2 damage
		bunitA->battleDefense += 2;
	}
}

// Deadeye: Doubles hit rate.
// Skill% chance to inflict sleep.
// This function only handles the doubled hit rate.
void Deadeye(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, DeadeyeID_Link)
	) {
		//double hit rate
		bunitA->battleHitRate *= 2;
	}
}

// Decapitator: Grants Atk = foe's missing HP at start of combat. 
// If foe is below 50% HP, grants Hit/Crit +80.
void Decapitator(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, DecapitatorID_Link)
	) {
		//add foe's missing HP to attack
		bunitA->battleAttack += ( bunitB->unit.maxHP - bunitB->unit.curHP ) ;
		//if foe is below 50% hp
		if (bunitB->unit.curHP < bunitB->unit.maxHP/2) {
			//hit/crit +80
			bunitA->battleHitRate += 80;
			bunitA->battleCritRate += 80;
		}
	}
}

// Strong Riposte: When under attack, damage +3.
void StrongRiposte(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are defending
		bunitA == &gBattleTarget
		//and we have the skill
		&& SkillTester(bunitA, StrongRiposteID_Link)
	) {
		//damage +3
		bunitA->battleAttack += 3;
	}
}

// Patience: When under attack, avoid +10.
void Patience(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are defending
		bunitA == &gBattleTarget
		//and we have the skill
		&& SkillTester(bunitA, PatienceID_Link)
	) {
		//avoid +10
		bunitA->battleAvoidRate += 10;
	}
}

// Pursuit: When under attack, attack speed +2.
void Pursuit(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are defending
		bunitA == &gBattleTarget
		//and we have the skill
		&& SkillTester(bunitA, PursuitID_Link)
	) {
		//attack speed +2
		bunitA->battleSpeed += 2;
	}
}

// Deviant Avoid: When HP is 25% or lower, gain +30 Avoid.
void DefiantAvo(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if HP is 25% or lower
		bunitA->unit.curHP <= bunitA->unit.maxHP/4
		//and we have the skill
		&& SkillTester(bunitA, DefiantAvoID_Link)
	) {
		//+30 avoid
		bunitA->battleAvoidRate += 30;
	}
}

// Defiant Crit: When HP is 25% or lower, gain +30 Crit.
void DefiantCrit(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if HP is 25% or lower
		bunitA->unit.curCP <= bunitA->unit.maxHP/4
		//and we have the skill
		&& SkillTester(bunitA, DefiantCritID_Link)
	) {
		//+30 crit
		bunitA->battleCritRate += 30;
	}
}

// Detonate: Destroy equipped weapon to deal remaining uses as damage.
void Detonate(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if attack type is detonate
		gDebuffTable.attackType == AT_DETONATE
		//and we are the attacker
		&& bunitA == &gBattleActor
	) {
		//set attack to weapon uses before battle
		bunitA->battleAttack = ITEM_USES(bunitA->weaponBefore);
		//set weapon after battle's uses to 0
		bunitA->weapon = ITEM_INDEX(bunitA->weapon);
	}
}

bool IsUnitIndoors(struct BattleUnit* bunit) {
	//get terrain unit is standing on
	u8 terrain = GetTrueTerrainAt(bunit->unit.xPos, bunit->unit.yPos);
	u8* terrainList = &IndoorTerrainList;
	while (true) {
		if (*terrainList == 0) break;
		if (*terrainList == terrain) return true;
		terrainList++;
	}
	return false;
}

// Indoor Fighter: +10 Hit and Avo when fighting indoors.
void IndoorFighter(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are indoors
		IsUnitIndoors(bunitA)
		//and we have the skill
		&& SkillTester(bunitA, IndoorFighterID_Link)
	) {
		//+10 hit and avo
		bunitA.battleHitRate += 10;
		bunitA.battleAvoidRate += 10;
	}
}

// Outdoor Fighter: +10 Hit and Avo when fighting outdoors.
void OutdoorFighter(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we are not indoors
		!IsUnitIndoors(bunitA)
		//and we have the skill
		&& SkillTester(bunitA, OutdoorFighterID_Link)
	) {
		//+10 hit and avo
		bunitA.battleHitRate += 10;
		bunitA.battleAvoidRate += 10;
	}
}

// Double Lion: All weapons are treated as brave.
void DoubleLion(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	if (
		//if we have the skill
		SkillTester(bunitA, DoubleLionID_Link)
	) {
		//apply brave effect
		bunitA->weaponAttributes &= IA_BRAVE;
	}
}

// Dragonskin: Halves damage taken.
void Dragonskin(struct BattleUnit* bunitA, struct BattleUnit* bunitB) {
	int damage = (bunitB->battleAttack - bunitA->battleDefense);
	if (
		//if we aren't in a simulated battle
		!(gBattleStats.config & BATTLE_CONFIG_SIMULATE)
		//and a nonzero amount of damage is being dealt
		&& damage > 0
		//and we have the skill
		&& SkillTester(bunitA, DragonskinID_Link)
	) {
		//halve damage taken
		bunitA->battleDefense = 0;
		bunitB->battleAttack = damage/2;
	}
}




