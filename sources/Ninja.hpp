#pragma once

#include "Character.hpp"

namespace ariel
{
	// Inherits from the Character class.
	class Ninja : public Character
	{
	private:
		// Represent the ninja's speed.
		int speed;

	public:
		// Constructor that get name, starting loc (a Point object), hpoints (hit points), and spd (speed).
		Ninja(std::string name, const Point &loc, int hpoints, int spd);

		// move()
		void move(Character *enemy);

		// slash()
		void slash(Character *enemy);

		// getSpeed()
		int getSpeed() const;

		// print()
		std::string print() const override;
	};
}
