#include "unsummon.h"
#include "gameboard.h"
#include "player.h"
#include <iostream>

Unsummon::Unsummon(int owner) : Spell("Unsummon", "Return target minion to its owner's hand", 1, owner, "none", true) {}

void Unsummon::cast_spell(GameBoard *gb, int target_player, int target_card){
	Player *p = gb->getPlayer(target_player);
	std::unique_ptr<Card> temp (nullptr);
	temp.swap(p->minions[target_card-1]);
	p->minions.erase(p->minions.begin()+(target_card-1));
	
	if(target_player == gb->getActive()){
		p->hand.emplace_back(nullptr);
                temp.swap(p->hand[p->hand.size()-1]);
	}else{
		if(p->hand.size() < 5){
			p->hand.emplace_back(nullptr);
			temp.swap(p->hand[p->hand.size()-1]);
		}else{
			p->grave.emplace_back(nullptr);
			temp.swap(p->grave[p->grave.size()-1]);
			std::cout << "Hand full: target minion sent to grave, but enchantments remain" << std::endl;
		}
	}
}
