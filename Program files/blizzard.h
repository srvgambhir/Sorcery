#ifndef __BLIZZARD_H__
#define __BLIZZARD_H__
#include "spell.h"

class Blizzard: public Spell {
	public:
	Blizzard(int owner);

	void cast_spell(GameBoard *gb, int target_player, int target_card) override;
};

#endif
