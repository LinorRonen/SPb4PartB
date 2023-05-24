#include <iostream>
#include <algorithm>
#include <limits>

#include "Team.hpp"
#include "Team2.hpp"
#include "SmartTeam.hpp"
using namespace std;
using namespace ariel;

// The maximum capacity of the team
const int MAX_TEAM = 10;

// Constructor
Team::Team(Character *leader) : leader(leader)
{
	if (leader == nullptr)
		throw invalid_argument("Leader is null!");

	if (leader->getIfInTeam())
		throw runtime_error("Leader is already in a team!");

	members.reserve(MAX_TEAM);
	members.push_back(leader);

	leader->setIfInTeam(true);
}

// Destructor
Team::~Team()
{
	for (Character *member : members)
		delete member;

	members.clear();
}

// Copy constructor
Team::Team(const Team &other)
{
	members.reserve(MAX_TEAM);

	for (Character *member : other.members)
	{
		if (Cowboy *cowboy = dynamic_cast<Cowboy *>(member))
		{
			Cowboy *clonedCowboy = new Cowboy(*cowboy);
			members.push_back(clonedCowboy);
		}

		else if (Ninja *ninja = dynamic_cast<Ninja *>(member))
		{
			Ninja *clonedNinja = new Ninja(*ninja);
			members.push_back(clonedNinja);
		}
	}

	leader = members.at(0);
}

// Copy assignment operator
Team &Team::operator=(const Team &other)
{
	if (this != &other)
	{
		// Delete existing members
		for (Character *member : members)
			delete member;

		members.clear();
		members.reserve(MAX_TEAM);

		// Copy members
		for (Character *member : other.members)
		{
			if (Cowboy *cowboy = dynamic_cast<Cowboy *>(member))
			{
				Cowboy *clonedCowboy = new Cowboy(*cowboy);
				members.push_back(clonedCowboy);
			}

			else if (Ninja *ninja = dynamic_cast<Ninja *>(member))
			{
				Ninja *clonedNinja = new Ninja(*ninja);
				members.push_back(clonedNinja);
			}
		}

		// Copy leader
		leader = members.at(0);
	}

	return *this;
}

// Move constructor
Team::Team(Team &&other) noexcept : leader(other.leader), members(move(other.members))
{
	other.leader = nullptr;
}

// Move assignment operator
Team &Team::operator=(Team &&other) noexcept
{
	if (this != &other)
	{
		// Delete existing members
		for (Character *member : members)
			delete member;

		members.clear();

		// Move leader and members
		leader = other.leader;
		members = move(other.members);

		other.leader = nullptr;
	}

	return *this;
}

// add() -  takes a pointer to a cowboy or ninja, and adds it to the group.
void Team::add(Character *member)
{
	if (member == nullptr)
	{
		throw invalid_argument("Cannot add a null member!");
	}
	if (member->getIfInTeam())
	{
		throw runtime_error("Character is already a member of another team!");
	}
	// Check if the team has reached the maximum limit
	if (members.size() >= MAX_TEAM)
	{
		throw runtime_error("Maximum number of characters in the team has been reached.");
	}
	members.push_back(member);
	member->setIfInTeam(true);
}

// stillAlive() - returns the number of group members left alive
int Team::stillAlive() const
{
	int aliveCount = 0;

	for (const Character *member : members)
	{
		if (member->isAlive())
			aliveCount++;
	}

	return aliveCount;
}

// attack () - Team
void Team::attack(Team *enemy)
{
	// 1)First check:
	if (enemy == nullptr)
	{
		throw invalid_argument("Invalid enemy provided.");
	}
	if (enemy == this)
	{
		throw runtime_error("Cannot attack your own team!");
	}

	if (enemy->stillAlive() == 0)
	{
		throw runtime_error("There are no members alive in the enemy team.");
	}
	if (stillAlive() == 0)
	{
		throw runtime_error("There are no members alive in the attacking team.");
	}

	// 2) Second, check if the leader of the attacking team is alive
	if (!leader->isAlive())
	{
		// Find a new leader from the living characters closest to the dead leader
		double minDistance = numeric_limits<double>::max();
		Character *newLeader = nullptr;

		for (Character *member : members)
		{
			if (member->isAlive())
			{
				double distance = leader->distance(member);

				if (distance < minDistance)
				{
					minDistance = distance;
					newLeader = member;
				}
			}
		}

		// Set the new leader
		leader = newLeader;
	}

	// 3) Third, find the closest enemy to the leader of the attacking team
	Character *closestEnemy = nullptr;
	double minDistance = numeric_limits<double>::max();

	for (Character *enemyMember : enemy->members)
	{
		if (enemyMember->isAlive())
		{
			double distance = leader->distance(enemyMember);

			if (leader->distance(enemyMember) < minDistance)
			{
				minDistance = distance;
				closestEnemy = enemyMember;
			}
		}
	}

	// 4) Finally, attack the closest enemy, first the cowboys attack, then the ninjas attack

	// First, the cowboys attack
	for (Character *member : members)
	{
		if (member->isAlive())
		{
			Cowboy *cowboy = dynamic_cast<Cowboy *>(member);

			if (cowboy != nullptr)
			{
				if (cowboy->hasboolets())
				{
					cowboy->shoot(closestEnemy);
				}
				else
				{
					cowboy->reload();
				}
			}
		}

		// Check if the enemy is dead
		if (!closestEnemy->isAlive())
		{
			// Check if the enemy team is dead
			if (enemy->stillAlive() == 0)
				return;

			// Find the next closest enemy
			minDistance = numeric_limits<double>::max();

			for (Character *enemyMember : enemy->members)
			{
				if (enemyMember->isAlive())
				{
					double distance = leader->distance(enemyMember);

					if (leader->distance(enemyMember) < minDistance)
					{
						minDistance = distance;
						closestEnemy = enemyMember;
					}
				}
			}
		}
	}

	// Second, the ninjas attack
	for (Character *member : members)
	{
		if (member->isAlive())
		{
			Ninja *ninja = dynamic_cast<Ninja *>(member);

			if (ninja != nullptr)
			{
				if (ninja->distance(closestEnemy) <= 1)
				{
					ninja->slash(closestEnemy);
				}
				else
				{
					ninja->move(closestEnemy);
				}
			}
		}

		// Check if the enemy is dead
		if (!closestEnemy->isAlive())
		{
			// Check if the enemy team is dead
			if (enemy->stillAlive() == 0)
				return;

			// Find the next closest enemy
			minDistance = numeric_limits<double>::max();

			for (Character *enemyMember : enemy->members)
			{
				if (enemyMember->isAlive())
				{
					double distance = leader->distance(enemyMember);

					if (leader->distance(enemyMember) < minDistance)
					{
						minDistance = distance;
						closestEnemy = enemyMember;
					}
				}
			}
		}
	}
}

// print()
void Team::print() const
{
	// First, print cowboys
	for (Character *member : members)
	{
		Cowboy *cowboy = dynamic_cast<Cowboy *>(member);

		if (cowboy != nullptr)
		{
			cout << cowboy->print() << endl;
		}
	}

	// Second, print ninjas
	for (Character *member : members)
	{
		Ninja *ninja = dynamic_cast<Ninja *>(member);

		if (ninja != nullptr)
		{
			cout << ninja->print() << endl;
		}
	}
}

// Constructor
Team2::Team2(Character *leader) : Team(leader) {}

// attack() - Team2
void Team2::attack(Team *enemy)
{
	// 1) First check
	if (enemy == nullptr)
	{
		throw invalid_argument("Invalid enemy. The enemy object is null.");
	}
	if (enemy == this)
	{
		throw runtime_error("Cannot attack self team. The enemy is the same as the attacking team.");
	}
	// First check if any members of the enemy team are still alive
	if (enemy->stillAlive() == 0)
	{
		throw runtime_error("There are no members of the enemy team that are still alive.");
	}
	if (stillAlive() == 0)
	{
		throw runtime_error("There are no members alive in the enemy team.");
	}

	// 2) Second ,check if the leader of the attacking team is alive
	if (!getLeader()->isAlive())
	{
		// Find a new leader from the living characters closest to the dead leader
		double minDistance = numeric_limits<double>::max();
		Character *newLeader = nullptr;

		for (Character *member : getMembers())
		{
			if (member->isAlive())
			{
				double distance = getLeader()->distance(member);

				if (distance < minDistance)
				{
					minDistance = distance;
					newLeader = member;
				}
			}
		}

		// Set the new leader
		setLeader(newLeader);
	}

	// 3) Third, find the closest enemy to the leader of the attacking team
	Character *closestEnemy = nullptr;
	double minDistance = numeric_limits<double>::max();

	for (Character *enemyMember : enemy->getMembers())
	{
		if (enemyMember->isAlive())
		{
			double distance = getLeader()->distance(enemyMember);

			if (getLeader()->distance(enemyMember) < minDistance)
			{
				minDistance = distance;
				closestEnemy = enemyMember;
			}
		}
	}

	// 5) Finally, attack the closest enemy
	for (Character *member : getMembers())
	{
		if (member->isAlive())
		{
			Cowboy *cowboy = dynamic_cast<Cowboy *>(member);

			if (cowboy != nullptr)
			{
				if (cowboy->hasboolets())
				{
					cowboy->shoot(closestEnemy);
				}
				else
				{
					cowboy->reload();
				}
			}

			else
			{
				Ninja *ninja = dynamic_cast<Ninja *>(member);

				if (ninja->distance(closestEnemy) <= 1)
				{
					ninja->slash(closestEnemy);
				}

				else
				{
					ninja->move(closestEnemy);
				}
			}
		}

		// Check if the enemy is dead
		if (!closestEnemy->isAlive())
		{
			// Check if the enemy team is dead
			if (enemy->stillAlive() == 0)
				return;

			// Find the next closest enemy
			minDistance = numeric_limits<double>::max();

			for (Character *enemyMember : enemy->getMembers())
			{
				if (enemyMember->isAlive())
				{
					double distance = getLeader()->distance(enemyMember);

					if (getLeader()->distance(enemyMember) < minDistance)
					{
						minDistance = distance;
						closestEnemy = enemyMember;
					}
				}
			}
		}
	}
}

// print()  Team2
void Team2::print() const
{
	for (Character *member : getMembers())
		cout << member->print() << endl;
}

// Constructor - SmartTeam
SmartTeam::SmartTeam(Character *leader) : Team(leader) {}

// findWeakestEnemy() -the function findWeakestEnemy in the SmartTeam class is responsible for finding the weakest
// enemy character from a given vector of enemy characters.
Character *SmartTeam::findWeakestEnemy(const std::vector<Character *> &enemies)
{
	Character *weakestEnemy = nullptr;
	int minHealth = std::numeric_limits<int>::max();

	for (Character *enemy : enemies)
	{
		if (enemy->isAlive() && enemy->getHitPoints() < minHealth)
		{
			weakestEnemy = enemy;
			minHealth = enemy->getHitPoints();
		}
	}
	return weakestEnemy;
}

// attack() - SmartTeam
void SmartTeam::attack(Team *enemy)
{
	// 1) First, check:
	if (enemy == nullptr)
	{
		throw invalid_argument("Invalid enemy: enemy is null");
	}
	if (enemy == this)
	{
		throw runtime_error("Cannot attack self team. The enemy is the same as the attacking team.");
	}
	// First check if any members of the enemy team are still alive
	if (enemy->stillAlive() == 0)
	{
		throw runtime_error("There are no members of the enemy team that are still alive.");
	}
	if (stillAlive() == 0)
	{
		throw runtime_error("There are no members of the attacking team that are still alive.");
	}

	// 2) Second check if the leader of the attacking team is alive
	if (!getLeader()->isAlive())
	{
		// Find a new leader from the living characters closest to the dead leader
		double minDistance = numeric_limits<double>::max();
		Character *newLeader = nullptr;

		for (Character *member : getMembers())
		{
			if (member->isAlive())
			{
				double distance = getLeader()->distance(member);

				if (distance < minDistance)
				{
					minDistance = distance;
					newLeader = member;
				}
			}
		}

		// Set the new leader (Won't be null since there is at least one living member, as checked above).
		setLeader(newLeader);
	}

	// 3) find the weakes enemy
	Character *weakestEnemy = findWeakestEnemy(enemy->getMembers());
	if (weakestEnemy == nullptr)
	{
		return;
	}

	// First, the ninjas attack
	for (Character *member : getMembers())
	{
		if (member->isAlive())
		{
			Ninja *ninja = dynamic_cast<Ninja *>(member);

			if (ninja != nullptr)
			{
				if (ninja->distance(weakestEnemy) <= 1)
					ninja->slash(weakestEnemy);

				else
				{
					while (ninja->distance(weakestEnemy) > 1)
					{
						ninja->move(weakestEnemy);
					}
					ninja->slash(weakestEnemy);
				}
			}
		}

		// Check if the enemy is dead
		if (!weakestEnemy->isAlive())
		{
			// Check if the enemy team is dead
			if (enemy->stillAlive() == 0)
				return;

			// Find the next weakest enemy
			Character *weakestEnemy = findWeakestEnemy(enemy->getMembers());
			if (weakestEnemy == nullptr)
			{
				return;
			}
		}
	}
	// Second , the cowboys attack
	for (Character *member : getMembers())
	{
		if (member->isAlive())
		{
			Cowboy *cowboy = dynamic_cast<Cowboy *>(member);

			if (cowboy != nullptr)
			{
				if (cowboy->hasboolets())
					cowboy->shoot(weakestEnemy);

				else
					cowboy->reload();
			}
		}

		// Check if the enemy is dead
		if (!weakestEnemy->isAlive())
		{
			// Check if the enemy team is dead
			if (enemy->stillAlive() == 0)
				return;

			// Find the next weakest enemy
			Character *weakestEnemy = findWeakestEnemy(enemy->getMembers());
			if (weakestEnemy == nullptr)
			{
				return;
			}
		}
	}
}

// print() - SmartTeam
void SmartTeam::print() const
{
	// Print ninjas
	for (Character *member : getMembers())
	{
		Ninja *ninja = dynamic_cast<Ninja *>(member);

		if (ninja != nullptr)
			cout << ninja->print() << endl;
	}
	// Print cowboys
	for (Character *member : getMembers())
	{
		Cowboy *cowboy = dynamic_cast<Cowboy *>(member);

		if (cowboy != nullptr)
			cout << cowboy->print() << endl;
	}
}
