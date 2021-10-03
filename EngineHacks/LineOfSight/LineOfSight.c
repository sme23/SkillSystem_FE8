
#include "U:\Projects\FE-CLib\include\gbafe.h"

//don't know for sure where this is going to go yet but the gist is
//given unit ptr and coords find if there is an impassable tile in a straight line between the two

bool CollisionVector(struct Unit *unit, struct Vec2u coords) {
	
	u16 targetX = coords.x;
	u16 targetY = coords.y;
	u8 unitX = unit->xPos;
	u8 unitY = unit->yPos;
	
	bool isBlocked = false;
	
	//check the range map at the target tile's location
	s8 rangeValue = (**gMapRange + (targetY*4) + (targetX*targetY));
	
	//rangeValue is -1 if somewhere else found it to be blocked,
	//0 if it hasn't been checked yet,
	//and a positive value if it's accessible from somewhere
	if (rangeValue > 0) return false;
	
	
	//now, to figure out how to determine what cells in a grid a line vector intersects with
	//bresenham time
	
	
	
	return true;
	
}

void CleanUpRangeMap() {
	
	u8* mapPos = *gMapRange;
	
	for (int i = 0; i <= (gMapSize.x * gMapSize.y); i++) {
		
		if (*(mapPos+i) == 0xFF) *(mapPos+i) = 0;
	
	}
	
}

