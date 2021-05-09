#ifndef __MASSUMMONER_H__
#define __MASSUMMONER_H__
#include "minion.h"

class MasSummoner: public Minion {
	public:
	MasSummoner(int owner);
	
	void use_ability(GameBoard *gb, int target_player, int target_card) override;

	void notify(GameBoard *gb) override {}
};

#endif
