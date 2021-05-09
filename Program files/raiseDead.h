#ifndef __RAISEDEAD_H__
#define __RAISEDEAD_H__
#include "spell.h"

class RaiseDead: public Spell {
	public:
	RaiseDead(int owner);

	void cast_spell(GameBoard *gb, int target_player, int target_card) override;
};

#endif
