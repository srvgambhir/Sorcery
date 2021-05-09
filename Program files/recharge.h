#ifndef __RECHARGE_H__
#define __RECHARGE_H__
#include "spell.h"

class Recharge: public Spell {
	public:
	Recharge(int owner);

	void cast_spell(GameBoard *gb, int target_player, int target_card) override;
};

#endif
