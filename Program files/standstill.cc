#include "standstill.h"
#include "player.h"
#include "gameboard.h"


Standstill::Standstill(int owner) : Ritual("Standstill", "Whenever a minion enters play, destroy it", 3, owner, "minionEnter", 2, 4) {}

void Standstill::notify(GameBoard *gb){
        if(this->getCharges()-this->getCOA() >= 0){
                Player *p = gb->getPlayer(gb->getActive());
                p->minions[p->minions.size()-1]->changeDefense(p->minions[p->minions.size()-1]->getDefense()*-1);
                this->changeCharges(-1 * this->getCOA());
        }
}
