#ifndef __AIRELEMENTAL_H__
#define __AIRELEMENTAL_H__
#include "minion.h"

class AirElemental: public Minion {
	public:
	AirElemental(int owner);
	
	void use_ability(GameBoard *gb, int target_player, int target_card) override {}

	void notify(GameBoard *gb) override {}
};

#endif
