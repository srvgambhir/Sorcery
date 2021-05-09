#ifndef __DELAY_H__
#define __DELAY_H__
#include "enchantment.h"

class Delay: public Enchantment {
	public:
	Delay(int owner);

	int getCOA() const override;

        int getAttack() const override;

        int getDefense() const override;
};

#endif
