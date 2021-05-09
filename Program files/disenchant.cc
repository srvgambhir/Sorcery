#include "disenchant.h"
#include "gameboard.h"
#include "player.h"
#include <iostream>

Disenchant::Disenchant(int owner) : Spell("Disenchant", "Destroy the top enchantment on target minion", 1, owner, "none", true) {}

void Disenchant::cast_spell(GameBoard *gb, int target_player, int target_card){
	Player *p = gb->getPlayer(target_player);
	if( p->minions[target_card-1]->modifiers.size() >= 1){
		p->minions[target_card-1]->modifiers.erase( p->minions[target_card-1]->modifiers.begin() + (p->minions[target_card-1]->modifiers.size()-1));
	}else{
		std::invalid_argument error{"There are no enchantments on the target minion at this time"};
		throw(error);
	}
}
