#include "enrage.h"

Enrage::Enrage(int owner) : Enchantment("Enrage", "", 2, owner, "none", "stat_mod/atk_mult") {}

int Enrage::getCOA() const {
        return 0;
}

int Enrage::getAttack() const {
        return 2;
}

int Enrage::getDefense() const {
        return -2;
}
	
