#include "BossChangeBGM.h"

u16 BossChangeBGM(u16 songID) {
	//songID is the song that we're to be fading out
	
	//is does either battler have boss music?
	int i = 0;
	
	while (true) {
		//if the charID is this, it's the list terminator
		if (BossMusicTable[i].unitID == 0xFFFFFFFF) return songID;
		//if the charID is either of these, this entry is currently in use
		if (BossMusicTable[i].unitID == gBattleActor.unit.pCharacterData->number || BossMusicTable[i].unitID == gBattleTarget.unit.pCharacterData->number) break;
		i++;
	}
	
	//should not be equal
	 if (songID == BossMusicTable[i].songID) return songID;
	
	//if it isn't already, make the map music player play this song
	
	//u32* musicPlayer = (u32*)0x02024E5C;
	//u16* mapMusicID = (u16*)0x02024E60;

	Sound_PlaySong(BossMusicTable[i].songID, 0);
	
	SetEventId(4);
	
	
	return BossMusicTable[i].songID;

}

