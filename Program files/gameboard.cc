#include "gameboard.h"
#include <iostream>

using namespace std;

GameBoard::GameBoard(std::string p1_name, std::string p2_name, std::string deck1, std::string deck2, bool testing) : p1{std::make_unique<Player>(p1_name, 1)}, p2{std::make_unique<Player>(p2_name, 2)}, testing{testing}, td{std::make_unique<Display>()}{
	p1->make_deck(deck1);
	p2->make_deck(deck2);
	if (testing == false) {
		p1->shuffle();
		p2->shuffle();
	}
	p1->draw(5);
	p2->draw(5);
}


Player * GameBoard::getPlayer(int p) const {
	if (p == 1) {
		return p1.get();
	}
	else {
		return p2.get();
	}
}

int GameBoard::getActive() const { return active_player; }

int GameBoard::getInActive() const { return inactive_player; }

void GameBoard::displayBoard(){
	td->displayBoard(this);
}

void GameBoard::displayHand(){
	td->displayHand(this, active_player);
	td->clearHand();
}

void GameBoard::inspectMinion(int m){
	td->inspectMinion(this, active_player, m);
}

void GameBoard::notify_observers(int player, std::string scope) {
	Player *current = getPlayer(player);
	for (unsigned int i = 0; i < current->minions.size(); ++i) {
		if (current->minions[i]->getScope() == scope) {
			current->minions[i]->notify(this);
		}
	}
	if (current->ritual) {
		if (current->ritual->getScope() == scope) {
			current->ritual->notify(this);
		}
	}
}
        
void GameBoard::attack(int minion, int target_minion) {
	unsigned int m_ind = minion - 1;
	unsigned int target = target_minion - 1;
	Player *active = getPlayer(active_player);
	if (m_ind + 1 <= active->minions.size()) {
		Player *inactive = getPlayer(inactive_player);
		if (target + 1 <= inactive->minions.size()) {
			if (active->minions[m_ind]->getActions() > 0) {
				int dmg = active->minions[m_ind]->getAttack();
				if (target_minion == 0) {
					inactive->changeHealth(-1 * dmg);
				}
				else {
					inactive->minions[target]->changeDefense(-1 * dmg);
					int dmg2 = inactive->minions[target]->getAttack();
					active->minions[m_ind]->changeDefense(-1 * dmg2);
				}
				active->minions[m_ind]->changeActions(-1);
			}
			else {
				std::invalid_argument error{"That minion has no actions left"};
				throw(error);
			}
		}
		else {
			std::invalid_argument error{"That target minion does not exist"};
                        throw(error);
		}
	}
	else {
		std::invalid_argument error{"That minion does not exist"};
		throw(error);
	}
}
        
void GameBoard::play(int card, int target_player, int target_card) {
	// card between 1 and 5, target player either 0, 1 or 2, target_card is between 0 and 6
	unsigned int c_ind = card - 1;
	unsigned int target_c = target_card - 1;
	Player *active = getPlayer(active_player);
	Player *target;
	if (c_ind + 1 > active->hand.size()) {
		std::invalid_argument error{"That card is not in your hand"};
                throw(error);
	}
	std::string c_type = active->hand[c_ind]->getType();
	if (active->hand[c_ind]->hasTarget() && c_type != "Minion") {
		if (target_player == 0 || target_card == 0) {
			std::invalid_argument error{"That card needs a target"};
                        throw(error);
                }
		target = getPlayer(target_player);
                if (target_card == 6) {
			if (active->hand[c_ind]->getName() != "Banish") {
				std::invalid_argument error{"That card cannot target ritual"};
				throw(error);
			}
		}
		else if (target_c + 1 > target->minions.size()) {
			std::invalid_argument error{"That target does not exist"};
			throw(error);
		}
        }
        else {
                if (target_player != 0 || target_card != 0) {                
			std::cerr << "That card does not need a target, it will be run as if no target was entered" << endl;                
		}
		if (c_type == "Minion") {
			if (active->minions.size() == 5) {
                                std::invalid_argument error{"There is no more room for a minion on the board"};
                                throw(error);
                        }		
		}
        }
	int cost = active->hand[c_ind]->getCost();
	bool bypass_magic = testing;
	if (c_type != "Spell") {
		bypass_magic = false;
	}
	if (cost <= active->getMagic() || bypass_magic) {
		if (c_type == "Spell") {
			active->hand[c_ind]->cast_spell(this, target_player, target_card);
		}
		else if (c_type == "Minion") {
			active->minions.emplace_back(nullptr);
			active->minions[active->minions.size()-1].swap(active->hand[c_ind]);
			notify_observers(active_player, "minionEnterOwn");
			notify_observers(active_player, "minionEnter");
			notify_observers(inactive_player, "minionEnterOpp");	
			notify_observers(inactive_player, "minionEnter");
		}
		else if (c_type == "Enchantment") {
			target->minions[target_c]->modifiers.emplace_back(nullptr);	
			target->minions[target_c]->modifiers[target->minions[target_c]->modifiers.size()-1].swap(active->hand[c_ind]);
		}
		else if (c_type == "Ritual") {
			active->ritual.swap(active->hand[c_ind]);
		}
		if (bypass_magic && cost > active->getMagic()) {
			active->changeMagic((-1 * active->getMagic()));
                }
		else {
			active->changeMagic(-1 * cost);
		}
		active->hand.erase(active->hand.begin() + c_ind);
	}
	else {
		std::invalid_argument error{"You do not have enough magic to play that card"};
		throw(error);
	}	
}
        
void GameBoard::use(int minion, int target_player, int target_minion) {
	unsigned int m = minion - 1;
	unsigned int target_m = target_minion - 1;
	Player *active = getPlayer(active_player);
	if (m + 1 <= active->minions.size()) {
		Card *min = active->minions[m].get();
		if (min->hasTarget()) {
			if (target_player == 0 || target_minion == 0) {
				std::invalid_argument error{"That minion ability needs a target"};
				throw(error);
			}
			Player *target = getPlayer(target_player);
                        if (target_m + 1 > target->minions.size()) {
                        	std::invalid_argument error{"That target does not exist"};
				throw(error);
                        }
		}
		else { 
			if (min->getCOA() == 0) {
                        	std::invalid_argument error{"That minion has no activated ability"};
                        	throw(error);
			} 
			if (target_player != 0 || target_minion != 0) {
				std::cerr << "That minion ability does not need a target, it will be run as if no target was entered" << std::endl;
			}
		}
		if (min->getCOA() <= active->getMagic() || testing) {
			if (min->getActions() > 0) {
				for (unsigned int i = 0; i < min->modifiers.size(); ++i) {
					if (min->modifiers[i]->getModifyType() == "no_active_ability") {
						std::invalid_argument error{"Sorry, that minion has been silenced"};
						throw(error);
					}
				}
				min->use_ability(this, target_player, target_minion);
				min->changeActions(-1);
				if (testing && min->getCOA() > active->getMagic()) {
                        		active->changeMagic((-1 * active->getMagic()));
                		}
                		else {
                        		active->changeMagic(-1 * min->getCOA());
                		}
			}
			else {
				std::invalid_argument error{"That minion has no actions left"};
				throw(error);
			}
		}
		else {
			std::invalid_argument error{"You do not have enough magic"};
			throw(error);
		}
	}
	else {
		std::invalid_argument error{"That minion does not exist"};
		throw(error);
	}
}
        
void GameBoard::change_turn(){
	notify_observers(active_player, "endTurn");
	swap(active_player, inactive_player);
	Player *active = getPlayer(active_player);
	std::string c="'";
	cout << "It is now " + active->getName() + c+ "s turn" << endl;
	active->changeMagic(1);
	active->draw(1);  
	active->minionsReset();
	notify_observers(active_player, "startTurn");
}


void GameBoard::cleanDead(int player) {
	int opp;
	if (player == 1) {
		opp = 2;
	}
	else { opp = 1; }
	Player *current = getPlayer(player);
	bool isdead = false;
	
	for (unsigned int i = 0; i < current->minions.size(); ++i) {
		if (current->minions[i]->getDefense() <= 0) {
			isdead=true;
			if (current->minions[i]->getName() == "Bomb") {
				notify_observers(player, "death");
			}
			current->minions[i]->modifiers.clear();
			current->grave.emplace_back(nullptr);
			current->grave[current->grave.size() - 1].swap(current->minions[i]);
			current->minions.erase(current->minions.begin() + i);
			i -=1;
		}
	}
	
	if(isdead){
		cleanDead(opp);
	}
}


int GameBoard::checkWinner() {
	if (p1->getHealth() == 0 && p2->getHealth() == 0) {
		return 0;
	}
	else if (p1->isEverythingEmpty() && p2->isEverythingEmpty()) {
		return 0;
	}
	else if (p1->getHealth() == 0 || p1->isEverythingEmpty()) {
		return 2;
	}
	else if (p2->getHealth() == 0 || p2->isEverythingEmpty()) {
		return 1;
	}
	else {
		return -1;
	}
}

void GameBoard::draw(){
        Player *p = getPlayer(active_player);
	p->draw(1); 
}

void GameBoard::discard(int card){
	unsigned int c = card - 1;
	Player *p = getPlayer(active_player);
	if(c+1 > p->hand.size()){
		std::invalid_argument err{"Card not in hand"};
		throw(err);
	}
	p->hand.erase(p->hand.begin()+c);	
}

std::string GameBoard::getName(int p) const {
	Player *play = getPlayer(p);
	return play->getName();
}
