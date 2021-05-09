#include "silence.h"

Silence::Silence(int owner) : Enchantment("Silence", "Enchanted minion cannot use abilities", 1, owner, "none", "no_active_ability") {}

int Silence::getCOA() const {
        return 0;
}

int Silence::getAttack() const {
        return 0;
}

int Silence::getDefense() const {
        return 0;
}
