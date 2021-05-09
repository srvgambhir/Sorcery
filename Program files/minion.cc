#include "minion.h"

Minion::Minion(std::string name, std::string description, int cost, int owner, std::string notification_scope, int atk, int def, int costOfAbility, bool has_target) :
	Card(name, "Minion", description, cost, owner, notification_scope), atk{atk}, def{def}, costOfAbility{costOfAbility}, has_target{has_target} {}

int Minion::getAttack() const {
	int tmp = atk;
	if (modifiers.size() > 0) {
		for (unsigned int i = 0; i < modifiers.size(); ++i) {
			if (modifiers[i]->getModifyType() == "stat_mod/atk_add") {
				tmp += modifiers[i]->getAttack();
			}
			else if (modifiers[i]->getModifyType() == "stat_mod/atk_mult") {
				tmp *= modifiers[i]->getAttack();
			}
		}
	}
	return tmp;
}

int Minion::getDefense() const {
	int tmp = def;
        if (modifiers.size() > 0) {
                for (unsigned int i = 0; i < modifiers.size(); ++i) {
			tmp += modifiers[i]->getDefense();
                }
        }
        return tmp;
}

int Minion::getCOA() const {
	int tmp = costOfAbility;
	if (modifiers.size() > 0 && costOfAbility != 0) {
		for (unsigned int i = 0; i < modifiers.size(); ++i) {
			tmp += modifiers[i]->getCOA();
		}
	}
	return tmp;
}

int Minion::getActions() const {
	return num_actions;
}
        
void Minion::changeAttack(int change) {
	atk += change;
}
        
void Minion::changeDefense(int change) {
	def += change;
}
        
void Minion::changeActions(int change) {
	num_actions += change;
}
        
bool Minion::hasTarget() const {
	return has_target;
}
        
int Minion::getCharges() const { return 0; }
        
void Minion::changeCharges(int change) {}
        
void Minion::cast_spell(GameBoard *gb, int target_player, int target_card) {}
        
std::string Minion::getModifyType() const { return "none"; }

