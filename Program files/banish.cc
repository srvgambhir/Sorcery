#include "banish.h"

Banish::Banish(int owner) : Spell("Banish", "Destroy target minion or ritual", 2, owner, "none", true) {}

void Banish::cast_spell(GameBoard *gb, int target_player, int target_card){
	Player *p = gb->getPlayer(target_player); 
	std::unique_ptr<Card> temp (nullptr);
	if(target_card == 6){
		if(p->ritual){
			temp.swap(p->ritual);
		}else{
			std::invalid_argument error{"No ritual card to banish"};
                        throw(error);
		}	
	}else{
		p->minions[target_card-1]->changeDefense(p->minions[target_card-1]->getDefense() * -1);
	}
}
