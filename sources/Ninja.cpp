#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace ariel;

// Constructor
Ninja::Ninja(string name, const Point &loc, int hp, int spd) : Character(name, const_cast<Point &>(loc), hp), speed(spd) {}

// move() - receives a pointer to the enemy and move towards the enemy. The ninja move a distance equal to its speed.
void Ninja::move(Character *enemy)
{
	if (enemy == nullptr)
	{
		throw invalid_argument("Cannot move towards a null character!");
	}
	if (enemy == this)
	{
		throw invalid_argument("Cannot move to yourself!");
	}
	if (!isAlive())
	{
		throw runtime_error("Cannot move while dead!");
	}
	else
	{
		Point newLoc = Point::moveTowards(getLocation(), enemy->getLocation(), speed);
		setLocation(newLoc);
		cout << getName() << " moved towards " << enemy->getName() << endl;
	}
}

// slash() - receives a pointer to the enemy. If the ninja is alive and the enemy is
// less than 1 meter away, the ninja will deal 40 damage to the enemy. Otherwise, no damage will be done to the enemy.
void Ninja::slash(Character *enemy)
{
	if (enemy == nullptr)
	{
		throw invalid_argument("Cannot slash a null character!");
	}
	if (enemy == this)
	{
		throw runtime_error("Cannot slash yourself!");
	}
	if (!isAlive())
	{
		throw runtime_error("Cannot slash while dead!");
	}
	if (!enemy->isAlive())
	{
		throw runtime_error("Cannot slash a dead character!");
	}
	else
	{
		if (getLocation().distance(enemy->getLocation()) <= 1)
		{
			cout << getName() << " slashes at " << enemy->getName() << " and cause him 40 damage." << endl;
			enemy->hit(40);
		}
	}
}

// print()
string Ninja::print() const
{
	string str = "Ninja: " + getName() + " (" + to_string(getHitPoints()) + "), Speed: " + to_string(speed) + ", Location: ";

	str += getLocation().print();

	return str;
}

// Constructor - YoungNinja
YoungNinja::YoungNinja(string name, const Point &loc) : Ninja(name, const_cast<Point &>(loc), 100, 14) {}

// print()
string YoungNinja::print() const
{
	string str;

	if (isAlive())
	{
		str = "N: " + getName() + " (" + to_string(getHitPoints()) + "), Speed: " + to_string(getSpeed()) + ", Location: ";
		str += getLocation().print();
	}

	else
	{
		str = "N: (" + getName() + ") [DEAD]";
	}
	return str;
}

// Constructor - TrainedNinja
TrainedNinja::TrainedNinja(string name, const Point &loc) : Ninja(name, const_cast<Point &>(loc), 120, 12) {}

// print()
string TrainedNinja::print() const
{
	string str;

	if (isAlive())
	{
		str = "N: " + getName() + " (" + to_string(getHitPoints()) + "), Speed: " + to_string(getSpeed()) + ", Location: ";
		str += getLocation().print();
	}

	else
	{
		str = "N: (" + getName() + ") [DEAD]";
	}

	return str;
}

// Constructor - OldNinja
OldNinja::OldNinja(string name, const Point &loc) : Ninja(name, const_cast<Point &>(loc), 150, 8) {}

// print()
string OldNinja::print() const
{
	string str;

	if (isAlive())
	{
		str = "N: " + getName() + " (" + to_string(getHitPoints()) + "), Speed: " + to_string(getSpeed()) + ", Location: ";
		str += getLocation().print();
	}

	else
	{
		str = "N: (" + getName() + ") [DEAD]";
	}
	return str;
}

// getSpeed()
int Ninja::getSpeed() const
{
	return speed;
}
