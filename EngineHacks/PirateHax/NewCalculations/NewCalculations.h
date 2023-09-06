bool CanBattleUnitGainExp(BattleUnit* actor, BattleUnit* target);
bool CanBattleUnitGainLevels(BattleUnit* battleUnit);
int GetLevelDifference(BattleUnit* actor, BattleUnit* target);
int GetNPCStatIncrease(int growth);

#define CA_NO_EXP CA_NEGATE_LETHALITY

#define NO_WEXP 0
#define D_WEXP 51
#define C_WEXP 76
#define B_WEXP 116
#define A_WEXP 176
#define S_WEXP 251

#define NO_RANK 0
#define D_RANK 2
#define C_RANK 3
#define B_RANK 4
#define A_RANK 5
#define S_RANK 6


void SetUnitLeaderCharId(struct Unit* unit, int charId);

struct ChapterEventGroup
{
    /* 00 */ void *turnBasedEvents;
    /* 04 */ void *characterBasedEvents; // must be 32-Aligned?
    /* 08 */ void *locationBasedEvents;
    /* 0C */ void *miscBasedEvents;

    // select unit -> select destination -> move unit to destination
    /* 10 */ void *specialEventsWhenUnitSelected;
    /* 14 */ void *specialEventsWhenDestSelected;
    /* 18 */ void *specialEventsAfterUnitMoved;

    /* 1C */ void *tutorialEvents;

    /* 20 */ void *traps;
    /* 24 */ void *extraTrapsInHard;

    /* 28 */ void *playerUnitsInNormal;
    /* 2C */ void *playerUnitsInHard;

    /* 30 */ void *playerUnitsChoice1InEncounter;
    /* 34 */ void *playerUnitsChoice2InEncounter;
    /* 38 */ void *playerUnitsChoice3InEncounter;

    /* 3C */ void *enemyUnitsChoice1InEncounter;
    /* 40 */ void *enemyUnitsChoice2InEncounter;
    /* 44 */ void *enemyUnitsChoice3InEncounter;

    /* 48 */ void *beginningSceneEvents;
    /* 4C */ void *endingSceneEvents;
};

const struct ChapterEventGroup* GetChapterEventDataPointer(unsigned chIndex);

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

enum
{
    CHAPTER_FLAG_0          = (1 << 0),
    CHAPTER_FLAG_1          = (1 << 1),
    CHAPTER_FLAG_POSTGAME   = (1 << 2),
    CHAPTER_FLAG_3          = (1 << 3),
    CHAPTER_FLAG_PREPSCREEN = (1 << 4),
    CHAPTER_FLAG_5          = (1 << 5),
    CHAPTER_FLAG_DIFFICULT  = (1 << 6),
    CHAPTER_FLAG_7          = (1 << 7)
};

s8 ActionSteal(Proc* proc);
void BattleApplyStealAction(struct Proc* proc, int item);
void BattleApplyStealActionExpGains(int item);
void ApplyStealFatigueValue(int item);
int GetStealExpValue(int item);
void UpdateActorFromBattle(void);
void BeginMapAnimForSteal(void);
void BattleInitItemEffect(struct Unit* actor, int itemSlot);
void InitBattleUnit(struct BattleUnit* bUnit, struct Unit* unit);
void CheckBattleUnitLevelUp(struct BattleUnit* bu);

static const struct ProcInstruction sProcScr_BattleAnimSimpleLock[] = {
    PROC_SLEEP(1),
    PROC_CALL_ROUTINE(UpdateActorFromBattle),
    PROC_END
};

int GenUnitDefinitionFinalPosition(const struct UnitDefinition* uDef, s8* xOut, s8* yOut, s8 findNearest);
void SetUnitAiFromDefinition(struct Unit* unit, const struct UnitDefinition* uDef);

int ReturnNumberOfHubChaptersVisited();

int GetBattleMapType(void);

enum ChapterData_chapterStateBits {
    PLAY_FLAG_STATSCREENPAGE0 = (1 << 0),
    PLAY_FLAG_STATSCREENPAGE1 = (1 << 1),
    PLAY_FLAG_POSTGAME        = (1 << 2),
    PLAY_FLAG_TUTORIAL        = (1 << 3),
    PLAY_FLAG_PREPSCREEN      = (1 << 4),
    PLAY_FLAG_COMPLETE        = (1 << 5),
    PLAY_FLAG_HARD            = (1 << 6),
    PLAY_FLAG_7               = (1 << 7),

    PLAY_FLAG_STATSCREENPAGE_SHIFT = 0,
    PLAY_FLAG_STATSCREENPAGE_MASK = PLAY_FLAG_STATSCREENPAGE0 | PLAY_FLAG_STATSCREENPAGE1,
};

s8 IsUnitEnemyWithActiveUnit(struct Unit* unit);

s8 AreUnitsAllied(int left, int right);

extern u8 A3LogIDLink;

bool LuaIsInHub(Unit* unit);