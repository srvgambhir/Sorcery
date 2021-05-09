#ifndef __ENRAGE_H__
#define __ENRAGE_H__
#include "enchantment.h"

class Enrage: public Enchantment {
	public:
	Enrage(int owner);

	int getCOA() const override;

        int getAttack() const override;

        int getDefense() const override;	
};

#endif
