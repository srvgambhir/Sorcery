#ifndef __DISENCHANT_H__
#define __DISENCHANT_H__
#include "spell.h"

class Disenchant: public Spell {
	public:
	Disenchant(int owner);

	void cast_spell(GameBoard *gb, int target_player, int target_card) override;
};

#endif
