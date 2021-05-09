#ifndef __STANDSTILL_H__
#define __STANDSTILL_H__
#include "ritual.h"

class Standstill: public Ritual {
	int costOfAbility;
	int charges;

	public:
	Standstill(int owner);
	
	void notify(GameBoard *gb) override;
};

#endif
