#include "Character.hpp"
#include <stdexcept>

using namespace std;
using namespace ariel;

// Constructor that initializes a character with a given name, location, and number of hit points. (in addition : ifInTeam = false )
Character::Character(std::string name, const Point &loc, int hit_points) : location(loc), hit_points(hit_points), name(name), ifInTeam(false) {}

// Copy constructor
Character::Character(const Character &other) : location(other.location), hit_points(other.hit_points), name(other.name), ifInTeam(other.ifInTeam) {}

// Copy assignment operator
Character &Character::operator=(const Character &other)
{
	if (this != &other)
	{
		hit_points = other.hit_points;
		name = other.name;
		ifInTeam = other.ifInTeam;
	}

	return *this;
}

// Move constructor
Character::Character(Character &&other) noexcept : location(other.location), hit_points(other.hit_points), name(move(other.name)), ifInTeam(other.ifInTeam)
{
	other.hit_points = 0;
	other.ifInTeam = false;
}

// Move assignment operator
Character &Character::operator=(Character &&other) noexcept
{
	if (this != &other)
	{
		hit_points = other.hit_points;
		name = move(other.name);
		ifInTeam = other.ifInTeam;
		other.hit_points = 0;
		other.ifInTeam = false;
	}

	return *this;
}

// Returns a boolean value indicating whether the character is alive (hit points > 0).
bool Character::isAlive() const
{
	return this->hit_points > 0;
}

// Returns the value of the ifInTeam flag (whether the character is in a team or not)
bool Character::getIfInTeam() const
{
	return this->ifInTeam;
}

// Calculates the distance between the current character and another character(other).
double Character::distance(const Character *other) const
{
	if (other == nullptr)
	{
		throw std::invalid_argument("Invalid pointer to Character.");
	}
	return location.distance(other->location);
}

// Reduces the character's hit points by the specified number.
void Character::hit(int num)
{
	if (num < 0)
	{
		throw std::invalid_argument("Invalid damage value. Damage value must be non-negative.");
	}

	hit_points -= num;

	if (hit_points < 0)
	{
		hit_points = 0;
	}
}

// Returns the name of the character.
string Character::getName() const
{
	return name;
}

// Returns the number of hit points of the character.
int Character::getHitPoints() const
{
	return hit_points;
}

// Returns the location of the character.
Point Character::getLocation() const
{
	return location;
}

// Sets the location of the character to the given new location.
void Character::setLocation(const Point &newLoc)
{
	location = newLoc;
}

// Sets the value of the ifInTeam flag to indicate whether the character is in a team.
void Character::setIfInTeam(bool ifExist)
{
	ifInTeam = ifExist;
}
