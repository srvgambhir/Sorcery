#ifndef __APPSUMMONER_H__
#define __APPSUMMONER_H__
#include "minion.h"

class AppSummoner: public Minion {
	public:
	AppSummoner(int owner);
	
	void use_ability(GameBoard *gb, int target_player, int target_card) override;

	void notify(GameBoard *gb) override {}
};

#endif
