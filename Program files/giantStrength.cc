#include "giantStrength.h"

GiantStrength::GiantStrength(int owner) : Enchantment("Giant Strength", "", 1, owner, "none", "stat_mod/atk_add") {}

int GiantStrength::getCOA() const {
	return 0;
}
        
int GiantStrength::getAttack() const {
	return 2;
}
	
int GiantStrength::getDefense() const {
	return 2;	
}
	
