#include "spell.h"

Spell::Spell(std::string name, std::string description, int cost, int owner, std::string notification_scope, bool has_target) :
	Card(name, "Spell", description, cost, owner, notification_scope), has_target{has_target} {}


int Spell::getAttack() const { return 0; }
        
int Spell::getDefense() const { return 0; }
        
int Spell::getCOA() const { return 0; }
        
int Spell::getActions() const { return 0; }
        
void Spell::changeAttack(int change) {}
        
void Spell::changeDefense(int change) {}
        
void Spell::changeActions(int change) {}
        
void Spell::use_ability(GameBoard *gb, int target_player, int target_card) {}
         
bool Spell::hasTarget() const {	
	return has_target;	
}
        
int Spell::getCharges() const { return 0; }
        
void Spell::changeCharges(int change) {}
       
std::string Spell::getModifyType() const { return "none"; }
        
void Spell::notify(GameBoard *gb) {}
