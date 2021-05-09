#include "darkRitual.h"
#include "player.h"
#include "gameboard.h"

DarkRitual::DarkRitual(int owner) : Ritual("Dark Ritual", "At the start of your turn, gain 1 magic", 0, owner, "startTurn", 1, 5) {}

void DarkRitual::notify(GameBoard *gb){
	if(this->getCharges()-this->getCOA() >= 0){
		Player *p = gb->getPlayer(gb->getActive());
		p->changeMagic(1);
		this->changeCharges(-1 * this->getCOA());
	}
}
