#include "delay.h"

Delay::Delay(int owner) : Enchantment("Delay", "Enchanted minion does not gain an action on their next turn. This enchantment is automatically destroyed after 1 turn", 1, owner, "none", "no_action") {}

int Delay::getCOA() const {
        return 0;
}

int Delay::getAttack() const {
        return 0;
}

int Delay::getDefense() const {
        return 0;
}
