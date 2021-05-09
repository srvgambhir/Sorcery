#ifndef __FIREELEMENTAL_H__
#define __FIREELEMENTAL_H__
#include "minion.h"

class FireElemental: public Minion {
	public:
	FireElemental(int owner);
	
	void use_ability(GameBoard *gb,int target_player, int target_card) override {}

	void notify(GameBoard *gb) override;
};

#endif
