#pragma once

#include "Character.hpp"

namespace ariel
{
	class Ninja : public Character
	{
		private:
			int speed;

		public:
			Ninja(std::string name, const Point &loc, int hpoints, int spd);

			void move(Character *enemy);

			void slash(Character *enemy);

			int getSpeed() const;

			std::string print() const override;
	};
}
