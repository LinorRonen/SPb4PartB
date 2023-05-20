#include "Character.hpp"
#include <stdexcept>

using namespace std;
using namespace ariel;

Character::Character(std::string name, const Point &loc, int hit_points): location(loc), hit_points(hit_points), name(name), ifInTeam(false) {}

Character::Character(const Character &other): location(other.location), hit_points(other.hit_points), name(other.name), ifInTeam(other.ifInTeam) {}

Character &Character::operator=(const Character &other) {
	if (this != &other)
	{
		hit_points = other.hit_points;
		name = other.name;
		ifInTeam = other.ifInTeam;
	}

	return *this;
}

Character::Character(Character &&other) noexcept: location(other.location), hit_points(other.hit_points), name(move(other.name)), ifInTeam(other.ifInTeam) {
	other.hit_points = 0;
	other.ifInTeam = false;
}

Character &Character::operator=(Character &&other) noexcept {
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

bool Character::isAlive() const {
	return this->hit_points > 0;
}

bool Character::getIfInTeam() const {
	return this->ifInTeam;
}

double Character::distance(const Character *other) const {
	if (other == nullptr)
	{
		throw std::invalid_argument("Invalid pointer to Character.");
	}
	return location.distance(other->location);
}

void Character::hit(int num) {
	if (num < 0)
		throw std::invalid_argument("Negative damage value is not allowed");
	
	hit_points -= num;

	if (hit_points < 0)
		hit_points = 0;
}

string Character::getName() const {
	return name;
}

int Character::getHitPoints() const {
	return hit_points;
}

Point Character::getLocation() const {
	return location;
}

void Character::setLocation(const Point &newLoc) {
	location = newLoc;
}

void Character::setIfInTeam(bool ifExist) {
	ifInTeam = ifExist;
}
