#include "novPyro.h"
#include "player.h"
#include "gameboard.h"
#include <algorithm>

NovPyro::NovPyro(int owner) : Minion("Novice Pyromancer", "Deal 1 damage to target minion", 1, owner, "none", 0, 1 , 1, true) {}

void NovPyro::use_ability(GameBoard *gb, int target_player, int target_card){
	Player *p = gb->getPlayer(target_player);
	p->minions[target_card-1]->changeDefense(-1);       	
}

