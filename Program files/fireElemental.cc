#include "fireElemental.h"
#include "player.h"
#include "gameboard.h"
#include <algorithm>

FireElemental::FireElemental(int owner) : Minion("Fire Elemental", "Whenever an opponent's minion enters play, deal 1 damage to it", 2, owner, "minionEnterOpp", 2, 2, 0, false) {}

void FireElemental::notify(GameBoard *gb){
	Player *p;
	if(this->getOwner()==1){
		p = gb->getPlayer(2);
	}else{
		p = gb->getPlayer(1);
	}
	p->minions[p->minions.size()-1]->changeDefense(-1);
}
