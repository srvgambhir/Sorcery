#include "raiseDead.h"
#include "gameboard.h"
#include "player.h"
#include <iostream>

RaiseDead::RaiseDead(int owner) : Spell("Raise Dead", "Resurrect the top minion in your graveyard and set its defence to 1", 1, owner, "none", false) {}

void RaiseDead::cast_spell(GameBoard *gb, int target_player, int target_card){
	Player *p = gb->getPlayer(this->getOwner());
	if(p->grave.size() > 0){
		if(p->minions.size() < 5){
			std::unique_ptr<Card> temp (nullptr);
			temp.swap(p->grave[p->grave.size()-1]);
			p->grave.erase(p->grave.begin()+p->grave.size()-1);
			temp->changeDefense((temp->getDefense() * -1) +1);
			p->minions.emplace_back(nullptr);
			temp.swap(p->minions[p->minions.size()-1]);
			gb->notify_observers(gb->getActive(), "minionEnterOwn");
                        gb->notify_observers(gb->getActive(), "minionEnter");
                        gb->notify_observers(gb->getInActive(), "minionEnterOpp");
                        gb->notify_observers(gb->getInActive(), "minionEnter");
		}else{
			std::invalid_argument minionsfull{"You don't have enough space on your board to resurrect the minion"};
                	throw(minionsfull);
		}
	}else{
		std::invalid_argument error{"Your grave yard is currently empty"};
                throw(error);
	}
}
