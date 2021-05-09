#include "auraOP.h"
#include "player.h"
#include "gameboard.h"

AuraOP::AuraOP(int owner) : Ritual("Aura of Power", "Whenever a minion enters play under your control, it gains +1/+1", 1, owner, "minionEnterOwn", 1, 4) {}

void AuraOP::notify(GameBoard *gb){
	if(this->getCharges()-this->getCOA() >= 0){
		Player *p = gb->getPlayer(gb->getActive());
		p->minions[p->minions.size()-1]->changeAttack(1);
		p->minions[p->minions.size()-1]->changeDefense(1);
		this->changeCharges(-1 * this->getCOA());
	}
}
	
