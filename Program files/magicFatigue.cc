#include "magicFatigue.h"

MagicFatigue::MagicFatigue(int owner) : Enchantment("Magic Fatigue", "Enchanted minion's activated ability costs 2 more", 0, owner, "none", "active_ability_cost_mod") {}

int MagicFatigue::getCOA() const {
        return 2;
}

int MagicFatigue::getAttack() const {
        return 0;
}

int MagicFatigue::getDefense() const {
        return 0;
}
	
