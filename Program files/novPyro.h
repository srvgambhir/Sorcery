#ifndef __NOVPYRO_H__
#define __NOVPYRO_H__
#include "minion.h"

class NovPyro: public Minion {
	public:
	NovPyro(int owner);
	
	void use_ability(GameBoard *gb, int target_player, int target_card) override;

	void notify(GameBoard *gb) override {};
};

#endif
