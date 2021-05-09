#include <fstream>
#include <iostream>
#include "gameboard.h"
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char *argv[]) {
  string player1_deck = "default.deck";
  string player2_deck = "default.deck";
  ifstream init_file;
  bool testing_mode = false;
  
  for(int i=0; i<argc; i++){
	string input = argv[i];
	if(input == "-deck1"){
		if(i+1 < argc){
			player1_deck = argv[i+1];
		}else{
			player1_deck = "default.deck";
		}
	}else if(input == "-deck2"){
		if(i+1 < argc){
                	player2_deck = argv[i+1];
		}else{
			player2_deck = "default.deck";
		}
        }else if(input == "-init"){
		if(i+1 < argc){
			init_file.open(argv[i+1]);
			if(init_file.fail()){
                        	cerr << "Init file cannot be opened" << endl;
                	}
		}else{
			cerr << "You did not pass in an Init file" << endl;
		}
	}else if(input == "-testing"){
		testing_mode = true;
	}
  }
  
  string player1_name = "";
  string player2_name = "";
  string pname;

  if(init_file.is_open()){
	  if(getline(init_file, pname)){
		player1_name = pname;			
	  }
	  if(getline(init_file, pname)){
                player2_name = pname;
          }
  }else{
	  cout << "Player 1 Enter Your Name:" << endl;
	  getline(cin, player1_name);
	  cout << "Player 2 Enter Your Name:" << endl;
          getline(cin, player2_name);
  }

  
  GameBoard gb{player1_name, player2_name, player1_deck, player2_deck, testing_mode};
  
  string input;
  string cmd;
  while((init_file.is_open() && getline(init_file, input)) || getline(cin, input)){
	try{	
		istringstream cmdss(input);
		cmdss >> cmd;	
		if (cmd == "help"){
			cout<< "Commands:";
            		cout<< "\thelp -- Display this message."<<endl;
            		cout<<  "\tend -- End the current player’s turn."<<endl;
            		cout<<  "\tquit -- End the game."<<endl;
            		cout<<  "\tattack minion other-minion -- Orders minion to attack other-minion."<<endl;
            		cout<<  "\tattack minion -- Orders minion to attack the opponent." <<endl;
            		cout<<  "\tplay card [target-player target-card] -- Play card,";
            		cout<<  "\toptionally targeting target-card owned by target-player."<<endl;
            		cout<<  "\tuse minion [target-player target-card] -- Use minion’s special ability,";
            		cout<<  "\toptionally targeting target-card owned by target-player. " << endl;
            		cout<<  "\tinspect minion -- View a minion’s card and all enchantments on that minion." << endl;
            		cout<<  "\thand -- Describe all cards in your hand." <<endl;
            		cout<<  "\tboard -- Describe all cards on the board." << endl;
		}else if(cmd == "end"){
			gb.change_turn();
		}else if(cmd == "quit"){
			break;
		}else if(cmd == "draw"){
			if(testing_mode){
				gb.draw();
                	}else{
                        	cerr << "The draw function is only available in testing mode" << endl;
                	}
		}else if(cmd == "discard"){
			if(testing_mode){
				int card=0;
				if (cmdss >> card) {
                                	if (card < 1 || card > 5) {
                                        	cerr << "Invalid card entered" << endl;
						continue;
                                	}
                        	}	
                        	else {
                                	cerr << "No minion entered" << endl;
					continue;
                        	}
                        	gb.discard(card);
			}else{
				cerr << "The discard function is only available in testing mode" << endl;
			}
        	}else if(cmd == "attack"){
			int minion = 0;
			std::string target_minion="0";
			if(cmdss >> minion){
                        	if(minion<1 || minion>5){
                                	cerr << "Invalid minion entered" << endl;
                                	continue;
                        	}
                	}else{
                        	cerr << "No minion entered" << endl;
                        	continue;
                	}
			if(cmdss >> target_minion){
				if(target_minion != "1" && target_minion != "2" && target_minion != "3" && target_minion != "4" && target_minion != "5"){
					cerr << "Inavlid target minion entered" << endl;
					continue;
				}			
			}
			gb.attack(minion, stoi(target_minion));

        	}else if(cmd == "play"){
			int card = 0;
			std::string target_player = "0";
			std::string target_card = "0";
			if(cmdss >> card){
				if(card<1 || card>5){
					cerr << "Invalid card entered" << endl;
					continue;
				}
			}else{
				cerr << "No card entered" << endl;
                        	continue;
			}
			if(cmdss >> target_player){
				if(target_player == "1" || target_player == "2"){
					if(cmdss >> target_card){
						if(target_card == "r"){
							target_card = "6";
                				}else if(target_card != "1" && target_card != "2" && target_card != "3" && target_card != "4" && target_card != "5"){
							cerr << "Invalid target card entered" << endl;
							continue;
						}
					}else{
						cerr << "Missing parameters" << endl;
                                		continue;
					}
				}else{
					cerr << "Invalid player entered" << endl;
					continue;	
				}
			
			}	
			gb.play(card, stoi(target_player), stoi(target_card));
        	}else if(cmd == "use"){
			int card = 0;
                	std::string target_player = "0";
                	std::string target_card = "0";
                	if(cmdss >> card){
                        	if(card<1 || card>5){
                                	cerr << "Invalid card entered" << endl;
                                	continue;
                        	}
                	}else{
                        	cerr << "No card entered" << endl;
                        	continue;
                	}
                	if(cmdss >> target_player){
                        	if(target_player == "1" || target_player == "2"){
                                	if(cmdss >> target_card){
                                        	if(target_card != "1" && target_card != "2" && target_card != "3" && target_card != "4" && target_card != "5"){
                                        		cerr << "Invalid target card entered" << endl;
                                                	continue;
                                        	}
                                	}else{
                                        	cerr << "Not enough input" << endl;
                                        	continue;
                                	}
                        	}else{
                                	cerr << "Invalid player entered" << endl;
                                	continue;
                        	}
                	}
        	gb.use(card, stoi(target_player), stoi(target_card));

        	}else if(cmd == "inspect"){	
			int index=0;
			if (cmdss >> index) {
				if (index < 1 || index > 5) {
					cerr << "Invalid minion entered" << endl;
					continue;
				}
			}
			else {
				cerr << "No minion entered" << endl;
				continue;
			}
			gb.inspectMinion(index-1); 	                
        	}else if(cmd == "hand"){
			gb.displayHand();

        	}else if(cmd == "board"){
			gb.displayBoard();
        	}
		else {
			cerr << "Invalid command entered. Please use \"help\" for a list of possible commands" << endl;
			continue;
		}
	}catch(std::invalid_argument & e) {        
		std::cerr << e.what() << std::endl;  
	}

	gb.cleanDead(gb.getActive());
	gb.cleanDead(gb.getInActive());
	int w = gb.checkWinner();
	if (w == 1 || w == 2) {
		cout << "Congratulations, player " << gb.getName(w) << " has won!" << endl;
		break;
	}
	else if (w == 0) {
		cout << "Game ended in a draw" << endl;
		break;
	}
  }
  
  if(init_file.is_open()){
	init_file.close();
  }

}
