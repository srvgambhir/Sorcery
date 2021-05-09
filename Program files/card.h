#ifndef __CARD_H__
#define __CARD_H__
#include <vector>
#include <memory>
#include <string>

class GameBoard;

class Card {
	std::string name;
	std::string type;
	std::string description;
	int cost;
	int owner;
	std::string notification_scope;

	public:
	std::vector<std::unique_ptr<Card>> modifiers; //minion enchantments

	Card(std::string name, std::string type, std::string description, int cost, int owner, std::string notification_scope);

	// general
	std::string getName() const;
	std::string getType() const;
	std::string getDesc() const;
	int getCost() const;
	std::string getScope() const;
	int getOwner() const;

	// minion
	virtual int getAttack() const = 0; // also for enchantment
	virtual int getDefense() const = 0; // also for enchantment
	virtual int getCOA() const = 0; // also for ritual and enchantment
	virtual int getActions() const = 0;
	virtual void changeAttack(int change) = 0;
	virtual void changeDefense(int change) = 0;
	virtual void changeActions(int change) = 0;
	virtual void use_ability(GameBoard *gb, int target_player, int target_card) = 0;
	virtual bool hasTarget() const = 0; // also for spell
	
	// ritual
	virtual int getCharges() const = 0;
	virtual void changeCharges(int change) = 0;

	// spell
	virtual void cast_spell(GameBoard *gb, int target_player, int target_card) = 0;

	// enchantment
	virtual std::string getModifyType() const = 0;

	virtual void notify(GameBoard *gb) = 0;
	virtual ~Card();
};

#endif
