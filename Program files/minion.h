#ifndef __MINION_H__
#define __MINION_H__
#include <string>
#include "card.h"

class Minion: public Card {
	int atk;
	int def;
	int costOfAbility;
	bool has_target;
	int num_actions = 1;

	public:
	Minion(std::string name, std::string description, int cost, int owner, std::string notification_scope, int atk, int def, int costOfAbility, bool has_target);

	// minion
        int getAttack() const override;
        int getDefense() const override;
        int getCOA() const override;
        int getActions() const override;
        void changeAttack(int change) override;
        void changeDefense(int change) override;
        void changeActions(int change) override;
        virtual void use_ability(GameBoard *gb, int target_player, int target_card) override = 0;
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
