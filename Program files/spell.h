#ifndef __SPELL_H__
#define __SPELL_H__
#include <string>
#include "card.h"

class Spell: public Card {
	bool has_target;
	
	public:
	Spell(std::string name, std::string description, int cost, int owner, std::string notification_scope, bool has_target);

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
        virtual void cast_spell(GameBoard *gb, int target_player, int target_card) override = 0;

        // enchantment
        std::string getModifyType() const override;

        void notify(GameBoard *gb) override;
};

#endif
