#include "bomb.h"
#include "player.h"
#include "gameboard.h"
#include <iostream>	
Bomb::Bomb(int owner) : Minion("Bomb", "Deals damage to all the opponent minions equal to its attack value when it dies", 2, owner, "death", 1, 2, 0, false) {}


void Bomb::notify(GameBoard *gb){
	if (this->getDefense() > 0) {
		return;
	}
	Player *p;	
	if(this->getOwner() == 1){
		p = gb->getPlayer(2);
	}else{
		p = gb->getPlayer(1);
	}

	for(unsigned int i=0; i<p->minions.size(); i++){
		p->minions[i]->changeDefense(this->getAttack()*-1);
	}
}

