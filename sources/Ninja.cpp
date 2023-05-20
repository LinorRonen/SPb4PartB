#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"
#include <cmath>
#include <iostream>

using namespace std;
using namespace ariel;

Ninja::Ninja(string name, const Point &loc, int hp, int spd) : Character(name, const_cast<Point &>(loc), hp), speed(spd) {}

void Ninja::move(Character *enemy) {
	if (enemy == nullptr)
		throw invalid_argument("Other character is null!");

	if (enemy == this)
		throw invalid_argument("Cannot move to yourself!");

	if (!isAlive())
		throw runtime_error("Cannot move while dead!");

	else
	{
		Point newLocation = Point::moveTowards(getLocation(), enemy->getLocation(), speed);
		setLocation(newLocation);
		cout << getName() << " moved towards " << enemy->getName() << endl;
	}
}

void Ninja::slash(Character *enemy) {
	if (enemy == nullptr)
		throw invalid_argument("Other character is null!");

	if (enemy == this)
		throw runtime_error("Cannot slash yourself!");

	if (!isAlive())
		throw runtime_error("Cannot slash while dead!");

	if (!enemy->isAlive())
		throw runtime_error("Cannot slash a dead character!");
		
	else
	{
		if (getLocation().distance(enemy->getLocation()) <= 1)
		{
			cout << getName() << " slashes at " << enemy->getName() << endl;
			enemy->hit(40);
		}
	}
}

string Ninja::print() const {
	string str = "Ninja: " + getName() + " (" + to_string(getHitPoints()) + "), Speed: " + to_string(speed) + ", Location: ";

	str += getLocation().print();

	return str;
}

YoungNinja::YoungNinja(string name, const Point &loc): Ninja(name, const_cast<Point &>(loc), 100, 14) {}

string YoungNinja::print() const {
	string str;

	if (isAlive())
	{
		str = "N: " + getName() + " (" + to_string(getHitPoints()) + "), Speed: " + to_string(getSpeed()) + ", Location: ";
		str += getLocation().print();
	}

	else
		str = "N: (" + to_string(getHitPoints()) + " hit points) [DEAD]";

	return str;
}

TrainedNinja::TrainedNinja(string name, const Point &loc): Ninja(name, const_cast<Point &>(loc), 120, 12) {}

string TrainedNinja::print() const {
	string str;

	if (isAlive())
	{
		str = "N: " + getName() + " (" + to_string(getHitPoints()) + "), Speed: " + to_string(getSpeed()) + ", Location: ";
		str += getLocation().print();
	}

	else
		str = "N: (" + to_string(getHitPoints()) + " hit points) [DEAD]";

	return str;
}

OldNinja::OldNinja(string name, const Point &loc): Ninja(name, const_cast<Point &>(loc), 150, 8) {}

string OldNinja::print() const {
	string str;

	if (isAlive())
	{
		str = "N: " + getName() + " (" + to_string(getHitPoints()) + "), Speed: " + to_string(getSpeed()) + ", Location: ";
		str += getLocation().print();
	}

	else
		str = "N: (" + to_string(getHitPoints()) + " hit points) [DEAD]";

	return str;
}

int Ninja::getSpeed() const {
	return speed;
}
