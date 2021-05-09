#ifndef __MAGICFATIGUE_H__
#define __MAGICFATIGUE_H__
#include "enchantment.h"

class MagicFatigue: public Enchantment {
	public:
	MagicFatigue(int owner);

	int getCOA() const override;

        int getAttack() const override;

        int getDefense() const override;
};

#endif
