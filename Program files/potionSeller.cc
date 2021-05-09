#include "potionSeller.h"
#include "player.h"
#include "gameboard.h"

PotionSeller::PotionSeller(int owner) : Minion("Potion Seller", "At the end of your turn, all your minions gain +0/+1", 2, owner, "endTurn", 1, 3, 0, false) {}

void PotionSeller::notify(GameBoard *gb){
	Player *p = gb->getPlayer(gb->getActive());
	
	for(unsigned int i=0; i<p->minions.size(); i++){
		p->minions[i]->changeDefense(1);
	}
}
