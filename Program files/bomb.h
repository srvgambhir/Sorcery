#ifndef __BOMB_H__
#define __BOMB_H__
#include "minion.h"

class Bomb: public Minion {
	public:
	Bomb(int owner);
	
	void use_ability(GameBoard *gb, int target_player, int target_card) override {};

	void notify(GameBoard *gb);
};

#endif
