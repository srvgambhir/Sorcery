#include "display.h"
#include "player.h"
#include "gameboard.h"
#include <iostream>
#include <string>
using namespace std;

Display::Display(){}

void Display::outputBoard() {
        std::cout << EXTERNAL_BORDER_CHAR_TOP_LEFT;
        for(int i = 0; i < 165; i++){
                std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        }
        std::cout << EXTERNAL_BORDER_CHAR_TOP_RIGHT << std::endl;     

	outputRow(0,5);
	outputRow(5,10);
	
	for(unsigned int i = 0; i < CENTRE_GRAPHIC.size(); i++){
                std::cout << CENTRE_GRAPHIC[i] << std::endl;
        }
	
	outputRow(10,15);
	outputRow(15,20);
        
	std::cout << EXTERNAL_BORDER_CHAR_BOTTOM_LEFT;
        for(unsigned int i = 0; i < 165; i++){
                std::cout << EXTERNAL_BORDER_CHAR_LEFT_RIGHT;
        }
	std::cout  << EXTERNAL_BORDER_CHAR_BOTTOM_RIGHT;
	std::cout << endl;
}

void Display::outputRow(int lower, int upper){
	for(unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); i++){
                std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN;
                for(int j = lower; j < upper; j++){
                        std::cout << board[j][i];
                }
                std::cout << EXTERNAL_BORDER_CHAR_UP_DOWN << std::endl;
        }
}


void Display::displayBoard(GameBoard *gb){
        Player *p1 = gb->getPlayer(1);
	displayBoardHelper(p1);
        displayBoardMinionHelper(p1);

        Player *p2 = gb->getPlayer(2);
        displayBoardMinionHelper(p2);
        displayBoardHelper(p2);
        outputBoard();
	board.clear();
}

void Display::displayBoardHelper(Player *p){
    if(p->ritual.get() != nullptr){
                board.emplace_back(display_ritual(p->ritual->getName(),p->ritual->getCost(),p->ritual->getCOA(),p->ritual->getDesc(),p->ritual->getCharges()));
        }else{
                board.emplace_back(CARD_TEMPLATE_BORDER);
        }

        board.emplace_back(CARD_TEMPLATE_EMPTY);
        board.emplace_back(display_player_card(p->getNum(), p->getName(), p->getHealth(), p->getMagic()));
        board.emplace_back(CARD_TEMPLATE_EMPTY);
        
        if(p->grave.size() == 0){
            board.emplace_back(CARD_TEMPLATE_BORDER);
        }else{
            int length = p->grave.size();
            int cost = p->grave[length-1]->getCost();
            std::string type = p->grave[length-1]->getType();
            std::string name = p->grave[length-1]->getName();

            if(type == "Spell"){
                board.emplace_back(display_spell(name,cost,p->grave[length-1]->getDesc()));
            }else if(type == "Minion"){
                if(p->grave[length-1]->getDesc() == ""){
                    board.emplace_back(display_minion_no_ability(name,cost,p->grave[length-1]->getAttack(),p->grave[length-1]->getDefense()));
                }else if(p->grave[length-1]->getCOA()==0){
                    board.emplace_back(display_minion_triggered_ability(name, cost, p->grave[length-1]->getAttack(),p->grave[length-1]->getDefense(), p->grave[length-1]->getDesc()));
                }else{
                    board.emplace_back(display_minion_activated_ability(name,cost,p->grave[length-1]->getAttack(),p->grave[length-1]->getDefense(),
                                                 p->grave[length-1]->getCOA(), p->grave[length-1]->getDesc()));
                }

            }else if(type == "Ritual"){
                board.emplace_back(display_ritual(name,cost,p->grave[length-1]->getCOA(),p->grave[length-1]->getDesc(),p->grave[length-1]->getCharges()));
            }else if(type == "Enchantment"){
                if(name=="Giant Strength"){ 
                    board.emplace_back(display_enchantment_attack_defence(name, cost, p->grave[length-1]->getDesc(), "+2", "+2"));
                }else if(name=="Enrage"){
		    board.emplace_back( display_enchantment_attack_defence(name, cost, p->grave[length-1]->getDesc(),"*2", "-2"));	
		}else{
                    board.emplace_back(display_enchantment(name, cost,p->grave[length-1]->getDesc()));
                }
            }
        }  
}

void Display::displayBoardMinionHelper(Player *p){
    for(unsigned int i=0; i<p->minions.size(); i++){
        std::string name = p->minions[i]->getName();
        int cost = p->minions[i]->getCost();
        int attack = p->minions[i]->getAttack();
        int defence = p->minions[i]->getDefense();

        if(p->minions[i]->getDesc() == ""){
            board.emplace_back(display_minion_no_ability(name, cost, attack, defence));
        }else if(p->minions[i]->getCOA()==0){
            board.emplace_back(display_minion_triggered_ability(name, cost, attack,
                                                 defence,p->minions[i]->getDesc()));
        }else{
            board.emplace_back(display_minion_activated_ability(name,cost,attack,defence,
                                                 p->minions[i]->getCOA(), p->minions[i]->getDesc()));
        }
    }

    for(int j=p->minions.size(); j<5;j++){
        board.emplace_back(CARD_TEMPLATE_BORDER);
    }
}

void Display::displayHand(GameBoard *gb, int player){
    Player *p = gb->getPlayer(player);
    int hand_length = p->hand.size();

    for(int i=0; i<hand_length; i++){
            card_template_t card = CARD_TEMPLATE_BORDER;
	    std::string name = p->hand[i]->getName();
	    std::string type = p->hand[i]->getType();
	    int cost = p->hand[i]->getCost();
            if(type == "Spell"){
                card = display_spell(name,cost,p->hand[i]->getDesc());
            }else if(type == "Minion"){
                if(p->hand[i]->getDesc() == ""){
                    card = display_minion_no_ability(name,cost,p->hand[i]->getAttack(),p->hand[i]->getDefense());
                }else if(p->hand[i]->getCOA()==0){
                    card = display_minion_triggered_ability(name, cost, p->hand[i]->getAttack(),p->hand[i]->getDefense(), p->hand[i]->getDesc());
                }else{
                    card = display_minion_activated_ability(name,cost,p->hand[i]->getAttack(),p->hand[i]->getDefense(),
                                                 p->hand[i]->getCOA(), p->hand[i]->getDesc());
                }

            }else if(type == "Ritual"){
                    card = display_ritual(name,cost,p->hand[i]->getCOA(),p->hand[i]->getDesc(),p->hand[i]->getCharges());
            }else if(type == "Enchantment"){
                if(name == "Giant Strength"){ 
                    card = display_enchantment_attack_defence(name, cost, p->hand[i]->getDesc(),
                                                   "+2", "+2");
                }else if(name == "Enrage"){
		    card = display_enchantment_attack_defence(name, cost, p->hand[i]->getDesc(),
                                                   "*2", "-2");	
		}else{
                    card = display_enchantment(name, cost,p->hand[i]->getDesc());
                }
            }
	    hand.emplace_back(card);

	}
    for(unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); i++){
                for(unsigned int j = 0; j < hand.size(); j++){
                        std::cout << hand[j][i];
                }
                std::cout <<"" << std::endl; 
        }

    }


void Display::inspectMinion(GameBoard *gb, int player, int minion){
    Player *p = gb->getPlayer(player);
    
    unsigned int m = minion;
    if(m >= p->minions.size()){
	std::invalid_argument error{"You've entered an invalid minion. Please see Help!"};
        throw(error);
    }
    std::string name = p->minions[minion]->getName();
    int cost = p->minions[minion]->getCost();
    int attack = p->minions[minion]->getAttack();
    int defence = p->minions[minion]->getDefense();
    card_template_t card = CARD_TEMPLATE_BORDER;
    
    if(p->minions[minion]->getDesc() == ""){
        card = display_minion_no_ability(name, cost, attack, defence);
    }else if(p->minions[minion]->getCOA()==0){
        card = display_minion_triggered_ability(name, cost, attack, defence,p->minions[minion]->getDesc());
    }else{
        card = display_minion_activated_ability(name,cost,attack,defence,
                                             p->minions[minion]->getCOA(), p->minions[minion]->getDesc());
    }

    for(unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); i++){
                std::cout << card[i];
		std::cout << "" << std::endl;
        }

    for(unsigned int i=0; i<p->minions[minion]->modifiers.size(); i++){
        std::string name = p->minions[minion]->modifiers[i]->getName();
        int cost = p->minions[minion]->modifiers[i]->getCost();
        std::string description = p->minions[minion]->modifiers[i]->getDesc();


        if(name=="Giant Strength"){ 
                    enchantments.emplace_back(display_enchantment_attack_defence(name, cost, description,"+2","+2"));
        }else if(name=="Enrage"){ 
                    enchantments.emplace_back(display_enchantment_attack_defence(name, cost, description,"*2","-2"));
        }else{
                    enchantments.emplace_back(display_enchantment(name, cost,description));
        }
    }
       
    int length = enchantments.size();
    for(int z=0; z < length; z++){
	     int minimum = std::min(z+5, length);	
	     outputEnchantments(z, minimum);
	     z+=minimum - 1;
      }
    enchantments.clear();
	                
}

void Display::outputEnchantments(int lower, int upper){
               for(unsigned int i = 0; i < CARD_TEMPLATE_BORDER.size(); i++){
                        for(int j = lower; j < upper; j++){
                        std::cout << enchantments[j][i];
                }
			std::cout << std::endl;
        }
}

void Display::clearHand(){
	hand.clear();
}

