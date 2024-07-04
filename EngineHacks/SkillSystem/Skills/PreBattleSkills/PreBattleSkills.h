#include "bmunit.h"
#include "bmbattle.h"
#include "bmitem.h"
#include "bmmap.h"
#include "types.h"
#include "variables.h"
#include "sio.h"

// debuff table 0-entry data structure
struct ExternData {
	u8 unk_00;
	u8 attackType;
};
extern ExternData gDebuffTable;

// attack type definitions
enum {
	AT_ATTACK = 0,
	AT_RESCUE,
	AT_PAIRUP,
	AT_LUNGE,
	AT_MERCY,
	AT_GAMBLE,
	AT_ADEPT_CA,
	AT_AETHER_CA,
	AT_DRAGONFANG_CA,
	AT_GLACIES_CA,
	AT_IGNIS_CA,
	AT_LUNA_CA,
	AT_SOL_CA,
	AT_SURESHOT_CA,
	
	AT_DETONATE = 17
};

// skill ID links
extern u8 AirRaidAtkID_Link;
extern u8 AirRaidSpdID_Link;
extern u8 AirRaidDefID_Link;
extern u8 AirRaidCriID_Link;
extern u8 AirRaidHitID_Link;
extern u8 AirRaidAvoID_Link;
extern u8 AirRaidResID_Link;
extern u8 AnalyticID_Link;
extern u8 ArcaneBladeID_Link;
extern u8 AssassinateID_Link;
extern u8 AxeFaithID_Link;
extern u8 BattleVeteranID_Link;
extern u8 DuelistsBlowID_Link;
extern u8 DeathBlowID_Link;
extern u8 DartingBlowID_Link;
extern u8 WardingBlowID_Link;
extern u8 CertainBlowID_Link;
extern u8 ArmoredBlowID_Link;
extern u8 QuickDrawID_Link;
extern u8 ChivalryID_Link;
extern u8 PragmaticID_Link;
extern u8 HeroesDeathBlowID_Link;
extern u8 BlueFlameID_Link;
extern u8 SwordbreakerID_Link;
extern u8 LancebreakerID_Link;
extern u8 AxebreakerID_Link;
extern u8 BowbreakerID_Link;
extern u8 TomebreakerID_Link;
extern u8 CatchingUpID_Link;
extern u8 ChaosStyleID_Link;
extern u8 ChargeID_Link;
extern u8 ChargePlusID_Link;
extern u8 CriticalPierceID_Link;
extern u8 CriticalForceID_Link;
extern u8 KillingMachineID_Link;
extern u8 CritUpID_Link;
extern u8 CulturedID_Link;
extern u8 DancingBladeID_Link;
extern u8 DeadeyeID_Link;
extern u8 DecapitatorID_Link;
extern u8 StrongRiposteID_Link;
extern u8 PatienceID_Link;
extern u8 PursuitID_Link;
extern u8 DefiantAvoID_Link;
extern u8 DefiantCritID_Link;
extern u8 DetonateID_Link;
extern u8 IndoorFighterID_Link;
extern u8 OutdoorFighterID_Link;
extern u8 DoubleLionID_Link;
extern u8 DragonskinID_Link;
extern u8 ElbowRoomID_Link;
extern u8 EarthBoostID_Link;
extern u8 FireBoostID_Link;
extern u8 WaterBoostID_Link;
extern u8 WindBoostID_Link;
extern u8 EvenRhythmID_Link;
extern u8 SwordfaireID_Link;
extern u8 LancefaireID_Link;
extern u8 AxefaireID_Link;
extern u8 BowfaireID_Link;
extern u8 TomefaireID_Link;
extern u8 FieryBloodID_Link;
extern u8 FlankID_Link;
extern u8 SwarmID_Link;
extern u8 MultiscaleID_Link;
extern u8 ForeignPrincessID_Link;
extern u8 FortuneID_Link;
extern u8 FrenzyID_Link;
extern u8 GambleID_Link;
extern u8 HawkeyeID_Link;
extern u8 HeavyBladeID_Link;
extern u8 HeavyStrikesID_Link;
extern u8 HolyAuraID_Link;
extern u8 InsightID_Link;
extern u8 KeenFighterID_Link;
extern u8 KnightAspirantID_Link;
extern u8 LadyBladeID_Link;
extern u8 LethalityID_Link;
extern u8 LifeAndDeathID_Link;
extern u8 LightWeightID_Link;
extern u8 LoyaltyID_Link;
extern u8 LuckySevenID_Link;
extern u8 LunarBraceID_Link;
extern u8 MageSlayerID_Link;
extern u8 MercilessID_Link;
extern u8 NaturalCoverID_Link;
extern u8 NoGuardID_Link;
extern u8 OddRhythmID_Link;
extern u8 OpportunistID_Link;
extern u8 OutriderID_Link;
extern u8 PerfectionistID_Link;
extern u8 PrescienceID_Link;
extern u8 PuissanceID_Link;
extern u8 PursuerID_Link;
extern u8 QuickBurnID_Link;
extern u8 Roll12ID_Link;
extern u8 SandRushID_Link;
extern u8 ShortShieldID_Link;
extern u8 SilentPrideID_Link;
extern u8 SlowBurnID_Link;
extern u8 SlushRushID_Link;
extern u8 SolarPowerID_Link;
extern u8 BracingStanceID_Link;
extern u8 DartingStanceID_Link;
extern u8 FierceStanceID_Link;
extern u8 KestrelStanceID_Link;
extern u8 MirrorStanceID_Link;
extern u8 ReadyStanceID_Link;
extern u8 SteadyStanceID_Link;
extern u8 SturdyStanceID_Link;
extern u8 SwiftStanceID_Link;
extern u8 WardingStanceID_Link;
extern u8 SpectrumStanceID_Link;
extern u8 AlertStanceID_Link;
extern u8 AlertStancePlusID_Link;
extern u8 StoneBodyID_Link;
extern u8 StunningSmileID_Link;
extern u8 SuperLuckID_Link;
extern u8 SwiftSwimID_Link;
extern u8 TechnicianID_Link;
extern u8 ThighdeologyID_Link;
extern u8 ThotslayerID_Link;
extern u8 ThunderstormID_Link;
extern u8 TowerShieldID_Link;
extern u8 TowerShieldPlusID_Link;
extern u8 TraceID_Link;
extern u8 TrampleID_Link;
extern u8 TrueStrikeID_Link;
extern u8 VanityID_Link;
extern u8 VigilanceID_Link;
extern u8 WindDiscipleID_Link;
extern u8 WonderGuardID_Link;
extern u8 WrathID_Link;
extern u8 NiceThighsID_Link;
extern u8 PersonalityID_Link;

//FlankSwarmScale transplants
extern int SwarmBonusDamagePercent; 
extern int FlankBonusDamagePercent; 
extern int FlankRequiresSkill_Link; 

//extern data
extern u8 IndoorTerrainList;

// extern functions
extern bool SkillTester(struct BattleUnit* unit, u8 skillID);
extern bool NewAuraSkillCheck(struct Unit* unit, u8 skillID, int allyOption, int maxRange);


// function prototypes
void AirRaidAtk(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void AirRaidSpd(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void AirRaidDef(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void AirRaidCri(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void AirRaidHit(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void AirRaidAvo(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void AirRaidRes(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Analytic(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void ArcaneBlade(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void AssassinateDamageBonus(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void AxeFaith(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void BattleVeteran(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void DuelistsBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void DeathBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void DartingBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void WardingBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void CertainBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void ArmoredBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void QuickDraw(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Chivalry(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Pragmatic(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void HeroesDeathBlow(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void BlueFlame(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Swordbreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Lancebreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Axebreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Bowbreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Tomebreaker(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void CatchingUp(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void ChaosStyle(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Charge(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void ChargePlus(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void CriticalPierce(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void CriticalForce(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void KillingMachine(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void CritUp(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Cultured(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void DancingBlade(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Deadeye(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Decapitator(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void StrongRiposte(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Patience(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Pursuit(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void DefiantAvo(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void DefiantCrit(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Detonate(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
bool IsUnitIndoors(struct BattleUnit* bunit);
void IndoorFighter(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void OutdoorFighter(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void DoubleLion(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Dragonskin(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void ElbowRoom(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void EarthBoost(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void FireBoost(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void WaterBoost(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void WindBoost(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void EvenRhythm(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Swordfaire(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Lancefaire(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Axefaire(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Bowfaire(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Tomefaire(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void FieryBlood(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Flank(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Swarm(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Multiscale(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void ForeignPrincess(struct BattleUnit* bunitA, struct BattleUnit* bunitB);

void Fortune(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
void Frenzy(struct BattleUnit* bunitA, struct BattleUnit* bunitB);
