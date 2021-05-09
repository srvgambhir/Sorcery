#ifndef __GIANTSTRENGTH_H__
#define __GIANTSTRENGTH_H__
#include "enchantment.h"

class GiantStrength: public Enchantment {
	public:
	GiantStrength(int owner);

	int getCOA() const override; 	

	int getAttack() const override;

	int getDefense() const override;
};

#endif
