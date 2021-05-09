#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include "ascii_graphics.h"
#include <vector>

class GameBoard;
class Player;

class Display{
	std::vector<card_template_t> board;
	std::vector<card_template_t> hand;
        std::vector<card_template_t> enchantments;
	
	public:
	Display();
	// Call from gameboard to print a minion
		
	void displayBoard(GameBoard *gb);
	void displayBoardHelper(Player *p);
	void displayBoardMinionHelper(Player *p);
	void outputBoard();
	void outputRow(int lower, int upper);
	void displayHand(GameBoard *gb, int player);
	void inspectMinion(GameBoard *gb, int player, int minion);
	void clearHand();
	void outputGraphics();
	void outputEnchantments(int lower, int upper);

};


#endif

