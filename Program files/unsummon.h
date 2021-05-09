#ifndef __UNSUMMON_H__
#define __UNSUMMON_H__
#include <iostream>
#include "spell.h"
#include "gameboard.h"
#include "player.h"

class Unsummon: public Spell {
	public:
	Unsummon(int owner);

	void cast_spell(GameBoard *gb, int target_player, int target_card) override;
};

#endif
