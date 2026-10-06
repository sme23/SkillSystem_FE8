#include "global.h"
#include "bmunit.h"
#include "bmitem.h"
#include "spellassoc.h"
#include "bmbattle.h"
#include "anime.h"
#include "ekrbattle.h"
#include "efxbattle.h"
#include "constants/classes.h"
#include "constants/items.h"

#define ANIM_REF_OFFSET(off_ref_round, off_ref_pos) ((off_ref_round) * 2 + off_ref_pos)

extern u16 BattleBufferAnimsOn2[];

struct NewBattleHit // Skill System's new 8-byte long rounds data.
{
	unsigned attributes : 19;
    unsigned info       : 5;
    signed   hpChange   : 8;
	u8 pad1;
	s8 damage;
	u8 pad2[2]; // These are things, but I don't know what they are.
};

long long HPChangeOnMiss(struct Unit* anim, struct NewBattleHit* hit, int r9, int r10)
{
	//if (hit->attributes & BATTLE_HIT_ATTR_HPSTEAL)
	//{
		int is_enemy;
		int new_hp;
		
		if (hit->info & BATTLE_HIT_INFO_RETALIATION)
            is_enemy = true;
        else
            is_enemy = false;
		
		if (gBanimPositionIsEnemy[POS_L] == is_enemy)
		{
			new_hp = GetEfxHp(ANIM_REF_OFFSET(r10, POS_R)) + hit->damage;
			if (new_hp < 0)
				new_hp = 0;

			//if (hit->damage != 0) {			
				r10++;
				BattleBufferAnimsOn2[ANIM_REF_OFFSET(r10, POS_R)] = new_hp;
			//}
			
			new_hp = GetEfxHp(ANIM_REF_OFFSET(r9, POS_L)) + hit->hpChange;
            if (new_hp > gBanimMaxHP[POS_L])
            new_hp = gBanimMaxHP[POS_L];

			//if (hit->damage != 0) {
				r9++;
				BattleBufferAnimsOn2[ANIM_REF_OFFSET(r9, POS_L)] = new_hp;
			//}
		}
		else
		{
			new_hp = GetEfxHp(ANIM_REF_OFFSET(r9, POS_L)) + hit->hpChange;
			if (new_hp < 0)
				new_hp = 0;
			
			//if (hit->damage != 0) {
				r9++;
				BattleBufferAnimsOn2[ANIM_REF_OFFSET(r9, POS_L)] = new_hp;
			//}
			
			new_hp = GetEfxHp(ANIM_REF_OFFSET(r10, POS_R)) + hit->damage;
			if (new_hp > gBanimMaxHP[POS_R])
				new_hp = gBanimMaxHP[POS_R];

			//if (hit->damage != 0) {
				r10++;
				BattleBufferAnimsOn2[ANIM_REF_OFFSET(r10, POS_R)] = new_hp;
			//}
		}
	//}
	
	return (long long)r9<<32|r10;
}

void StartBattleAnimResireHitEffects(struct Anim * anim, int type)
{
    int val1, val2, off;
    struct Anim * animR7, * animR5, * animR8;

    if (GetAnimPosition(anim) == EKR_POS_L) {
        animR7 = gAnims[2];
        animR5 = gAnims[0];
        animR8 = gAnims[1];
    } else {
        animR7 = gAnims[0];
        animR5 = gAnims[2];
        animR8 = gAnims[3];
    }

    val1 = gEfxHpLutOff[GetAnimPosition(animR5)];
    val2 = gEfxHpLutOff[GetAnimPosition(animR5)];
    val2++;

    {
        val1 = GetEfxHp(val1 * 2 + GetAnimPosition(animR5));
        val2 = GetEfxHp(val2 * 2 + GetAnimPosition(animR5));
    }

    switch (type) {
    case EKR_HITTED:
        if (val1 != val2) {
            NewEfxHpBarResire(animR5);

            if (CheckRoundCrit(animR7) == 1)
                NewEfxHitQuake(animR5, animR7, 4);
            else
                NewEfxHitQuake(animR5, animR7, 3);
            
            NewEfxFlashHPBar(animR5, 0, 5);
            NewEfxFlashUnit(animR5, 0, 8, 0);
        } else {
            gEfxHpBarResireFlag = 2;
            NewEfxNoDamage(animR5, animR8, 1);
        }
        break;

    case EKR_MISS:
		val1 = gEfxHpLutOff[GetAnimPosition(animR7)];
        val2 = gEfxHpLutOff[GetAnimPosition(animR7)];
        val2++;
    
        val1 = GetEfxHp(val1 * 2 + GetAnimPosition(animR7));
        val2 = GetEfxHp(val2 * 2 + GetAnimPosition(animR7));
		
		
        if (val1 != val2) {
			NewEfxHpBar(animR7);
		}
		NewEfxAvoid(animR5);
    }
}

void StartBattleAnimHitEffects(struct Anim *anim, int type, int a, int b)
{
    struct Anim *animr7, *animr9, *animr5, *animr8;
    int val1, val2;
    s16 roundt1, roundt2;

    if (GetAnimPosition(anim) == EKR_POS_L) {
        animr7 = gAnims[2];
        animr9 = gAnims[3];
        animr5 = gAnims[0];
        animr8 = gAnims[1];
    } else {
        animr7 = gAnims[0];
        animr9 = gAnims[1];
        animr5 = gAnims[2];
        animr8 = gAnims[3];
    }

    switch (type) {
    case EKR_HITTED:
        roundt1 = GetRoundFlagByAnim(animr7);
        roundt2 = GetRoundFlagByAnim(animr5);

        if (roundt1 & ANIM_ROUND_POISON) {
            if (GetUnitEfxDebuff(animr7) == UNIT_STATUS_NONE)
                SetUnitEfxDebuff(animr7, UNIT_STATUS_POISON);
        }

        if (roundt2 & ANIM_ROUND_POISON) {
            if (GetUnitEfxDebuff(animr5) == UNIT_STATUS_NONE)
                SetUnitEfxDebuff(animr5, UNIT_STATUS_POISON);
        }

        if (roundt1 & ANIM_ROUND_DEVIL || roundt2 & ANIM_ROUND_DEVIL) {
            struct Anim *tmp;
            tmp = animr5;
            animr5 = animr7;
            animr7 = tmp;
            animr8 = animr9;
        }

        val1 = gEfxHpLutOff[GetAnimPosition(animr5)];
        val2 = gEfxHpLutOff[GetAnimPosition(animr5)];
        val2++;
    
        val1 = GetEfxHp(val1 * 2 + GetAnimPosition(animr5));
        val2 = GetEfxHp(val2 * 2 + GetAnimPosition(animr5));

        if (val1 != val2) {
            NewEfxHpBar(animr5);

            if (CheckRoundCrit(animr7) == 1)
                NewEfxHitQuake(animr5, animr7, b);
            else
                NewEfxHitQuake(animr5, animr7, a);
            
            NewEfxFlashHPBar(animr5, 0, 5);
            NewEfxFlashUnit(animr5, 0, 8, 0);
        } else {
            NewEfxNoDamage(animr5, animr8, 0);
        }
        break;

    case EKR_MISS:
		val1 = gEfxHpLutOff[GetAnimPosition(animr7)];
        val2 = gEfxHpLutOff[GetAnimPosition(animr7)];
        val2++;
    
        val1 = GetEfxHp(val1 * 2 + GetAnimPosition(animr7));
        val2 = GetEfxHp(val2 * 2 + GetAnimPosition(animr7));
		
		
        if (val1 != val2) {
			NewEfxHpBar(animr7);
		}
		NewEfxAvoid(animr5);
        break;
    }
}