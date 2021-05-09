#include "enchantment.h"

Enchantment::Enchantment(std::string name, std::string description, int cost, int owner, std::string notification_scope, std::string modify_type) :
	Card(name, "Enchantment", description, cost, owner, notification_scope),modify_type{modify_type} {} 

int Enchantment::getActions() const { return 0; }
        
void Enchantment::changeAttack(int change) {}
        
void Enchantment::changeDefense(int change) {}
        
void Enchantment::changeActions(int change) {}
        
void Enchantment::use_ability(GameBoard *gb, int target_player, int target_card) {}
        
bool Enchantment::hasTarget() const { return true; }
        
int Enchantment::getCharges() const { return 0; }
        
void Enchantment::changeCharges(int charges) {}
        
void Enchantment::cast_spell(GameBoard *gb, int target_player, int target_card) {}
        
std::string Enchantment::getModifyType() const {		
	return modify_type;	
}
        
void Enchantment::notify(GameBoard *gb) {}
