#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "appSummoner.h"
#include "airElemental.h"
#include "player.h"
#include "gameboard.h"
	
AppSummoner::AppSummoner(int owner) : Minion("Apprentice Summoner", "Summon a 1/1 air elemental", 1, owner, "none", 1, 1, 1, false) {}

void AppSummoner::use_ability(GameBoard *gb, int target_player, int target_card) {
		Player *active = gb->getPlayer(gb->getActive());
		if (active->minions.size() == 5) {
			std::invalid_argument error{"No minion spots left"};
			throw(error);
		}
		else {

			int inactive = 0;
                        if(gb->getActive()==1){
                                inactive = 2;
                        }else{
                                inactive = 1;
                        }

			active->minions.emplace_back(std::make_unique<AirElemental>(gb->getActive()));
			gb->notify_observers(gb->getActive(), "minionEnterOwn");
                        gb->notify_observers(gb->getActive(), "minionEnter");
                        gb->notify_observers(inactive, "minionEnterOpp");
                        gb->notify_observers(inactive, "minionEnter"); 
		}
}
