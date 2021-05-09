#ifndef __SILENCE_H__
#define __SILENCE_H__
#include "enchantment.h"

class Silence: public Enchantment {
	public:
	Silence(int owner);

	int getCOA() const override;

        int getAttack() const override;

        int getDefense() const override;
};

#endif
