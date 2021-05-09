#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <string>
#include <vector>
#include <memory>
#include "card.h"
#include "minion.h"
#include "spell.h"
#include "enchantment.h"
#include "ritual.h"

//adding minions
#include "airElemental.h"
#include "earthElemental.h"
#include "bomb.h"
#include "fireElemental.h"
#include "potionSeller.h"
#include "novPyro.h"
#include "appSummoner.h"
#include "masSummoner.h"

//adding spells
#include "banish.h"
#include "unsummon.h"
#include "recharge.h"
#include "disenchant.h"
#include "raiseDead.h"
#include "blizzard.h"

//adding enchantments
#include "giantStrength.h"
#include "enrage.h"
#include "delay.h"
#include "magicFatigue.h"
#include "silence.h"

//adding rituals
#include "darkRitual.h"
#include "auraOP.h"
#include "standstill.h"

class Player {
	std::string name;
	int health = 20;
	int magic = 3;
	int p_num;
	std::vector<std::unique_ptr<Card>> deck;

	public:
	std::vector<std::unique_ptr<Card>> grave;
	std::vector<std::unique_ptr<Card>> hand;
	std::vector<std::unique_ptr<Card>> minions;
	std::unique_ptr<Card> ritual;

	Player(std::string name, int p_num);

	void shuffle();

	void make_deck(std::string deck);

	void draw(int num);

	std::string getName() const;
	
	int getNum() const;
	
	int getHealth() const;
	
	int getMagic() const;

	void changeHealth( int change );

	void changeMagic( int change );

	void minionsReset(); // for setting each minion's actions back to 1 at the start of each turn

	bool isEverythingEmpty() {
		return deck.empty() && hand.empty() && minions.empty();
	}
};

#endif
