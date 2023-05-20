#include "Cowboy.hpp"
#include <stdexcept>
using namespace std;
using namespace ariel;
//// Constructor
Cowboy::Cowboy(string name, const Point &loc): Character(name, const_cast<Point &>(loc), 110), bullets(6) {}

// Copy constructor
Cowboy::Cowboy(const Cowboy &other): Character(other), bullets(other.bullets) {}

// Copy assignment operator
Cowboy &Cowboy::operator=(const Cowboy &other) {
	if (this != &other)
	{
		Character::operator=(other);
		bullets = other.bullets;
	}
	return *this;
}

// Move constructor
Cowboy::Cowboy(Cowboy &&other) noexcept: Character(move(other)), bullets(other.bullets) {
	other.bullets = 0;
}

// Move assignment operator
Cowboy &Cowboy::operator=(Cowboy &&other) noexcept {
	if (this != &other)
	{
		Character::operator=(move(other));
		bullets = other.bullets;
		other.bullets = 0;
	}

	return *this;
}

// Destructor
Cowboy::~Cowboy() {}

void Cowboy::shoot(Character *enemy) {
	if (enemy == nullptr)
		throw invalid_argument("Other character is null!");

	if (enemy == this)
		throw runtime_error("Cannot shoot yourself!");

	if (!isAlive())
		throw runtime_error("Cannot shoot while dead!");

	if (!enemy->isAlive())
		throw runtime_error("Cannot shoot a dead character!");

	else
	{
		if (this->bullets > 0)
		{
			cout << getName() << " shoots " << enemy->getName() << " with 10 damage." << endl;
			this->bullets -= 1;
			enemy->hit(10);
		}

		else
			cout << getName() << " is out of ammo." << endl;
	}
}

// Check if the cowboy has bullets
bool Cowboy::hasboolets() const {
	return bullets > 0;
}

void Cowboy::reload() {
	if (this->isAlive() == false)
		throw runtime_error("Cannot reload. Cowboy is dead.");
	
	this->bullets = 6;
}

// Set the number of bullets
void Cowboy::setBullets(int num) {
	this->bullets = num;
}

// Print cowboy information
string Cowboy::print() const {
	return "Cowboy: " + getName() + ", Hit Points: " + to_string(getHitPoints()) + ", Bullets: " + to_string(bullets);
}