#ifndef __DARKRITUAL_H__
#define __DARKRITUAL_H__
#include "ritual.h"

class DarkRitual: public Ritual {
	int costOfAbility;
	int charges;

	public:
	DarkRitual(int owner);
	
	void notify(GameBoard *gb) override;
};

#endif
