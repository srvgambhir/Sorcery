#ifndef __POTIONSELLER_H__
#define __POTIONSELLER_H__
#include "minion.h"

class PotionSeller: public Minion {
	public:
	PotionSeller(int owner);
	
	void use_ability(GameBoard *gb, int target_player, int target_card) override {}

	void notify(GameBoard *gb) override;
};

#endif
