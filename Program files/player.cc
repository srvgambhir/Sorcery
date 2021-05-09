#include <fstream>
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>
#include "player.h"

Player::Player(std::string name, int p_num) : name{name}, p_num{p_num} {}

void Player::shuffle() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine rng{seed};
        for ( int i = 0; i < 1000; i++ ) {
                std::shuffle( deck.begin(), deck.end(), rng );
        }
}

void Player::make_deck(std::string file) {
	std::ifstream d{file};
	if(d.fail()){
		std::cerr << name + " your file with your deck failed to open, so you'll instead use the defualt deck provided" << std::endl;
		make_deck("default.deck");
	}
	std::string card;
	while(getline(d, card)) {	
		if(card == "Banish"){
        		deck.emplace_back(std::make_unique<Banish>(p_num));
		}
		else if(card == "Unsummon"){
                        deck.emplace_back(std::make_unique<Unsummon>(p_num));
                }
		else if(card == "Recharge"){
                        deck.emplace_back(std::make_unique<Recharge>(p_num));
                }
		else if(card == "Disenchant"){
                        deck.emplace_back(std::make_unique<Disenchant>(p_num));
                }
		else if(card == "Raise Dead"){
                        deck.emplace_back(std::make_unique<RaiseDead>(p_num));
                }
		else if(card == "Blizzard"){
                        deck.emplace_back(std::make_unique<Blizzard>(p_num));
                }
		else if(card == "Air Elemental"){
                        deck.emplace_back(std::make_unique<AirElemental>(p_num));
                }
		else if(card == "Earth Elemental"){
			deck.emplace_back(std::make_unique<EarthElemental>(p_num));
		}
		else if(card == "Bomb"){
                        deck.emplace_back(std::make_unique<Bomb>(p_num));
                }
		else if(card == "Fire Elemental"){
                        deck.emplace_back(std::make_unique<FireElemental>(p_num));
                }
		else if(card == "Potion Seller"){
                        deck.emplace_back(std::make_unique<PotionSeller>(p_num));
                }
		else if(card == "Novice Pyromancer"){
                        deck.emplace_back(std::make_unique<NovPyro>(p_num));
                }
		else if(card == "Apprentice Summoner"){
                        deck.emplace_back(std::make_unique<AppSummoner>(p_num));
                }
		else if(card == "Master Summoner"){
                        deck.emplace_back(std::make_unique<MasSummoner>(p_num));
                }
		else if(card == "Giant Strength"){
                        deck.emplace_back(std::make_unique<GiantStrength>(p_num));
                }
		else if(card == "Enrage"){
                        deck.emplace_back(std::make_unique<Enrage>(p_num));
                }
		else if(card == "Delay"){
                        deck.emplace_back(std::make_unique<Delay>(p_num));
                }
		else if(card == "Magic Fatigue"){
                        deck.emplace_back(std::make_unique<MagicFatigue>(p_num));
                }
		else if(card == "Silence"){
                        deck.emplace_back(std::make_unique<Silence>(p_num));
                }
		else if(card == "Dark Ritual"){
                        deck.emplace_back(std::make_unique<DarkRitual>(p_num));
                }
		else if(card == "Aura of Power"){
                        deck.emplace_back(std::make_unique<AuraOP>(p_num));
                }
		else if(card == "Standstill"){
                        deck.emplace_back(std::make_unique<Standstill>(p_num));
                }
	}
}

void Player::draw(int num) {
	if (deck.size() > 0 && hand.size() < 5) {
		for (int i = 1; i <= num && !deck.empty(); ++i) {
			hand.emplace_back(nullptr);
			deck[0].swap(hand[hand.size()-1]);
			deck.erase(deck.begin());
		}
	}	
	else {
		std::cerr << "No card drawn, deck empty or hand full" << std::endl;
	}
}

std::string Player::getName() const {
	return name;
}

int Player::getNum() const {
	return p_num;
}

int Player::getHealth() const {
	return health;
}

void Player::changeHealth(int change){
	health += change;
}

int Player::getMagic() const {
	return magic;
}

void Player::changeMagic(int change){
	magic += change;
}

void Player::minionsReset() {
	for (unsigned int i = 0; i < minions.size(); ++i) {
		bool restore = true;
		for (unsigned int j = 0; j < minions[i]->modifiers.size(); ++j) {
			if (minions[i]->modifiers[j]->getModifyType() == "no_action") {
				restore = false;
				minions[i]->modifiers.erase(minions[i]->modifiers.begin() + j);
				--j;
			}
		}
		if (minions[i]->getActions() == 0 && restore == true) {
			minions[i]->changeActions(1);
		}
	}
}

