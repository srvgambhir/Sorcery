#include "ritual.h"

Ritual::Ritual(std::string name, std::string description, int cost, int owner, std::string notification_scope, int costOfAbility, int charges) :
	Card(name, "Ritual", description, cost, owner, notification_scope), costOfAbility{costOfAbility}, charges{charges} {}
	
        
int Ritual::getAttack() const { return 0; }
        
int Ritual::getDefense() const { return 0;}
        
int Ritual::getCOA() const { 
	return costOfAbility; 	
}
        
int Ritual::getActions() const { return 0; }
        
void Ritual::changeAttack(int change) {}
        
void Ritual::changeDefense(int change) {}
        
void Ritual::changeActions(int change) {}
        
void Ritual::use_ability(GameBoard *gb, int target_player, int target_card) {}
        
bool Ritual::hasTarget() const { return false; }
        
int Ritual::getCharges() const {		
	return charges;	
}

void Ritual::changeCharges(int change) {	
	charges += change;	
}
        
void Ritual::cast_spell(GameBoard *gb, int target_player, int target_card) {}
        
std::string Ritual::getModifyType() const { return "none"; }

