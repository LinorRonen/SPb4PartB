#pragma once

#include "Team.hpp"

namespace ariel
{
	// SmartTeam class (inherits from Team):
	class SmartTeam : public Team
	{
	public:
		// Constructor
		SmartTeam(Character *leader);

		// attack()
		void attack(Team *other) override;

		// print()
		void print() const override;

		// This function returns a pointer to the weakest enemy character.
		Character *findWeakestEnemy(const std::vector<Character *> &enemies);
	};
}