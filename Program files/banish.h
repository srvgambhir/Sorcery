#ifndef __BANISH_H__
#define __BANISH_H__
#include "spell.h"
#include "gameboard.h"
#include "player.h"

class Banish: public Spell {
	public:
	Banish(int owner);

	void cast_spell(GameBoard *gb, int target_player, int target_card) override;
};

#endif
