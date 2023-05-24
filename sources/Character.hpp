#pragma once

#include <string>
#include "Point.hpp"

namespace ariel
{
	class Character
	{
	private:
		// The location of the character.
		Point location;

		// The number of hit points.
		int hit_points;

		// The name of the character.
		std::string name;

		// A boolean flag indicating whether the character is in a team or not.
		bool ifInTeam;

	public:
		// Constructor that get name, location and number of hit points.
		Character(std::string name, const Point &loc, int hit_points);

		// Copy constructor
		Character(const Character &other);

		// copy assignment operator.
		Character &operator=(const Character &other);

		// move constructor
		Character(Character &&other) noexcept;

		// move assignment operator
		Character &operator=(Character &&other) noexcept;

		// A virtual destructor
		virtual ~Character() {}

		// Method that checks if the character is alive (by checking if hit_points > 0).
		bool isAlive() const;

		// Returns the value of ifInTeam.
		bool getIfInTeam() const;

		// Sets the value of ifInTeam
		void setIfInTeam(bool ifExist);

		// Method that calculates the distance between this character and another character.
		double distance(const Character *other) const;

		// Reduce the character's hit points by the specified number
		void hit(int num);

		// Returns the character's name.
		std::string getName() const;

		// Returns the character's hit points.
		int getHitPoints() const;

		// Returns the character's location.
		Point getLocation() const;

		// Sets the character's location.
		void setLocation(const Point &newLoc);

		// A pure virtual method. This method returns a string representing the character.
		virtual std::string print() const = 0;
	};
}
