#ifndef __EARTHELEMENTAL_H__
#define __EARTHELEMENTAL_H__
#include "minion.h"

class EarthElemental: public Minion {
	public:
	EarthElemental(int owner);
	
	void use_ability(GameBoard *gb, int target_player, int target_card) override {}

	void notify(GameBoard *gb) override {}
};

#endif
