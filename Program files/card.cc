#include "card.h"

Card::Card(std::string name, std::string type, std::string description, int cost, int owner, std::string notification_scope) :
	name{name}, type{type}, description{description}, cost{cost}, owner{owner}, notification_scope{notification_scope} {}

std::string Card::getName() const {
	return name;
}

std::string Card::getType() const {
        return type;
}

std::string Card::getDesc() const {
        return description;
}

int Card::getCost() const {
	return cost;
}

std::string Card::getScope() const {
	return notification_scope;
}

int Card::getOwner() const {
	return owner;
}

Card::~Card() {};
