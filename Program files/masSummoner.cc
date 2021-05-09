#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include "masSummoner.h"
#include "airElemental.h"
#include "player.h"
#include "gameboard.h"

MasSummoner::MasSummoner(int owner) : Minion("Master Summoner", "Summon up to three 1/1 air elementals", 3, owner, "none", 2, 3, 2, false) {}

void MasSummoner::use_ability(GameBoard *gb, int target_player, int target_card) {
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
			unsigned int size = active->minions.size();
			for (unsigned int i = size + 1; i <= 5 && i <= size + 3; ++i) {
                        	active->minions.emplace_back(std::make_unique<AirElemental>(gb->getActive()));
				gb->notify_observers(gb->getActive(), "minionEnterOwn");
                                gb->notify_observers(gb->getActive(), "minionEnter");
                                gb->notify_observers(inactive, "minionEnterOpp");
                                gb->notify_observers(inactive, "minionEnter");				
			}
		}
}
