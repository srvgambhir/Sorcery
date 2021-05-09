#include "recharge.h"
#include "gameboard.h"
#include "player.h"
#include <iostream>

Recharge::Recharge(int owner) : Spell("Recharge", "Your ritual gains 3 charges", 1, owner, "none", false) {}

void Recharge::cast_spell(GameBoard *gb, int target_player, int target_card){	
	Player *p = gb->getPlayer(this->getOwner());
	if(p->ritual){
		p->ritual->changeCharges(3);
	}else{
		std::invalid_argument error{"No ritual card in play"};
        	throw(error);
	}
}
