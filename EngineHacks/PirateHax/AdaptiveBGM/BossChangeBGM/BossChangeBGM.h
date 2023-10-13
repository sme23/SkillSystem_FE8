#include "gbafe.h"

struct BossMusicEntry {
	u32 unitID;
	u32 songID;
} typedef BossMusicEntry;

extern BossMusicEntry* BossMusicTable;

extern void SetEventId(u16 flag);

