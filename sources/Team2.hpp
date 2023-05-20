#pragma once

#include "Team.hpp"

namespace ariel
{
	class Team2 : public Team
	{
		public:
			Team2(Character *leader);

			void attack(Team *other) override;

			void print() const override;
	};
}
