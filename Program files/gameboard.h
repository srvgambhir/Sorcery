#ifndef __GAMEBOARD_H__
#define __GAMEBOARD_H__
#include <memory>
#include <string>
#include <utility>
#include <algorithm>
#include "player.h"
#include "display.h"

class GameBoard {
	std::unique_ptr<Player> p1;
	std::unique_ptr<Player> p2;
	bool testing;
	int active_player = 1;
	int inactive_player = 2;
	std::unique_ptr<Display> td;
	
	public:
	GameBoard(std::string p1_name, std::string p2_name, std::string deck1, std::string deck2, bool testing);

	int getActive() const;
	int getInActive() const;
	Player *getPlayer(int p) const;
	std::string getName(int p) const;

	void displayBoard();
	void inspectMinion(int m);
	void displayHand();

	void notify_observers(int player, std::string scope);
	void attack(int minion, int target_minion = 0);
	void play(int card, int target_player = 0, int target_card = 0);
	void use(int minion, int target_player = 0, int target_minion = 0);
	int checkWinner();
	void change_turn();
	void cleanDead(int player);
	void discard(int card);
	void draw();
};

#endif
