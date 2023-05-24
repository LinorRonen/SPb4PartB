#include "Cowboy.hpp"
#include <stdexcept>
using namespace std;
using namespace ariel;

// Constructor
Cowboy::Cowboy(string name, const Point &loc) : Character(name, const_cast<Point &>(loc), 110), bullets(6) {}

// Copy constructor
Cowboy::Cowboy(const Cowboy &other) : Character(other), bullets(other.bullets) {}

// Copy assignment operator
Cowboy &Cowboy::operator=(const Cowboy &other)
{
	if (this != &other)
	{
		Character::operator=(other);
		bullets = other.bullets;
	}
	return *this;
}

// Move constructor
Cowboy::Cowboy(Cowboy &&other) noexcept : Character(move(other)), bullets(other.bullets)
{
	other.bullets = 0;
}

// Move assignment operator
Cowboy &Cowboy::operator=(Cowboy &&other) noexcept
{
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

// shoot() -  gets a pointer to the enemy. If the cowboy is not dead and has bullets left,
// the cowboy shoots the enemy, subtracting 10 hit points from the enemy
//- and losing 1 bullet. Otherwise, no damage will be done to the enemy.
void Cowboy::shoot(Character *enemy)
{
	if (enemy == nullptr)
		throw invalid_argument("Invalid target. The other character is null!");

	if (enemy == this)
		throw runtime_error("Invalid target. Cannot shoot yourself!");

	if (!isAlive())
		throw runtime_error("Invalid action. Cannot shoot while dead!");

	if (!enemy->isAlive())
		throw runtime_error("Invalid target. Cannot shoot a dead character!");

	else
	{
		if (this->bullets > 0)
		{
			cout << getName() << " shoots " << enemy->getName() << " and cause him 10 damage." << endl;

			this->bullets -= 1;

			enemy->hit(10);
		}

		else
			cout << getName() << " is out of bullets and cannot shoot." << endl;
	}
}

// Check if the cowboy has bullets
bool Cowboy::hasboolets() const
{
	return bullets > 0;
}

// reload() -  reloads the gun with six new bullets.
void Cowboy::reload()
{
	if (this->isAlive() == false)
		throw runtime_error("Cannot reload. Cowboy is dead.");

	this->bullets = 6;
}

// Set the number of bullets
void Cowboy::setBullets(int num)
{
	this->bullets = num;
}

// Print cowboy information
std::string Cowboy::print() const
{
	if (isAlive())
	{
		return "C: " + getName() + " (" + std::to_string(getHitPoints()) + " hit points), Bullets: " + std::to_string(bullets);
	}
	else
	{
		return "C: (" + getName() + ") [DEAD]";
	}
}
