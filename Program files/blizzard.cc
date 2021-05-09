#include "blizzard.h"
#include "gameboard.h"
#include "player.h"

Blizzard::Blizzard(int owner) : Spell("Blizzard", "Deal 2 damage to all minions", 3, owner, "none", false) {}

void Blizzard::cast_spell(GameBoard *gb, int target_player, int target_card){
	Player *p1 = gb->getPlayer(1);
	Player *p2 = gb->getPlayer(2);

	for(unsigned int i=0; i<p1->minions.size(); i++){
		p1->minions[i]->changeDefense(-2);
	}

	for(unsigned int j=0; j<p2->minions.size(); j++){
                p2->minions[j]->changeDefense(-2);
        }
}
