#ifndef __AURAOP_H__
#define __AURAOP_H__
#include "ritual.h"

class AuraOP: public Ritual {
	int costOfAbility;
	int charges;

	public:
	AuraOP(int owner);
	
	void notify(GameBoard *gb) override;
};

#endif
