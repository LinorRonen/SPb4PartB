#pragma once

#include "Team.hpp"

namespace ariel
{
	// Team2 class (inherits from Team):
	class Team2 : public Team
	{
	public:
		// Constructor
		Team2(Character *leader);

		// attack()
		void attack(Team *other) override;

		// print()
		void print() const override;
	};
}
