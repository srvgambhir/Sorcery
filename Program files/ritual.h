#ifndef __RITUAL_H__
#define __RITUAL_H__
#include <string>
#include "card.h"

class Ritual: public Card {
	int costOfAbility;
	int charges;

	public:
	Ritual(std::string name, std::string description, int cost, int owner, std::string notification_scope, int costOfAbility, int charges);

	// minion
        int getAttack() const override;
        int getDefense() const override;
        int getCOA() const override;
        int getActions() const override;
        void changeAttack(int change) override;
        void changeDefense(int change) override;
        void changeActions(int change) override;
        void use_ability(GameBoard *gb, int target_player, int target_card) override;
	bool hasTarget() const override;

        // ritual
        int getCharges() const override;
        void changeCharges(int change) override;

        // spell
        void cast_spell(GameBoard *gb, int target_player, int target_card) override;

        // enchantment
        std::string getModifyType() const override;

        virtual void notify(GameBoard *gb) override = 0;
};

#endif
