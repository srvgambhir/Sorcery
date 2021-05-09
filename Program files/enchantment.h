#ifndef __ENCHANTMENT_H__
#define __ENCHANTMENT_H__
#include <string>
#include "card.h"

class Enchantment: public Card {
	std::string modify_type;

	public:
	Enchantment(std::string name, std::string description, int cost, int owner, std::string notification_scope, std::string modify_type);
	
	// minion
        virtual int getAttack() const override = 0;
        virtual int getDefense() const override = 0;
        virtual int getCOA() const override = 0;
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

        void notify(GameBoard *gb) override;
};

#endif
