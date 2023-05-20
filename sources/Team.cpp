#include <iostream>
#include <algorithm>
#include <limits>

#include "Team.hpp"
#include "Team2.hpp"
#include "SmartTeam.hpp"
using namespace std;
using namespace ariel;

const int MAX_TEAM = 10;

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

Team::~Team()
{
	for (Character *member : members)
		delete member;

	members.clear();
}

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

Team::Team(Team &&other) noexcept : leader(other.leader), members(move(other.members))
{
	other.leader = nullptr;
}

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

void Team::add(Character *member)
{
	if (member == nullptr)
		throw invalid_argument("Member is null!");

	if (member->getIfInTeam())
		throw runtime_error("Character already exists in a group.");

	// Check if the team has reached the maximum limit
	if (members.size() >= MAX_TEAM)
		throw runtime_error("Maximum number of characters in the team has been reached.");

	members.push_back(member);
	member->setIfInTeam(true);
}

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

////////////////////////////////////////////////////////////////////////

void Team::attack(Team *enemy)
{
	if (enemy == nullptr)
		throw invalid_argument("Invalid enemy");

	if (enemy == this)
		throw runtime_error("Cannot attack self team!");

	// First check if any members of the enemy team are still alive
	if (enemy->stillAlive() == 0)
		throw runtime_error("There are no members of the enemy team that are still alive.");

	if (stillAlive() == 0)
		throw runtime_error("There are no members of the attacking team that are still alive.");

	// Second check if the leader of the attacking team is alive
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

		// Set the new leader (Won't be null since there is at least one living member, as checked above).
		leader = newLeader;
	}

	// Third, find the closest enemy to the leader of the attacking team
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

	// Finally, attack the closest enemy, first the cowboys attack, then the ninjas attack

	// First, the cowboys attack
	for (Character *member : members)
	{
		if (member->isAlive())
		{
			Cowboy *cowboy = dynamic_cast<Cowboy *>(member);

			if (cowboy != nullptr)
			{
				if (cowboy->hasboolets())
					cowboy->shoot(closestEnemy);

				else
					cowboy->reload();
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
					ninja->slash(closestEnemy);

				else
					ninja->move(closestEnemy);
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

void Team::print() const
{
	// Print cowboys
	for (Character *member : members)
	{
		Cowboy *cowboy = dynamic_cast<Cowboy *>(member);

		if (cowboy != nullptr)
			cout << cowboy->print() << endl;
	}

	// Print ninjas
	for (Character *member : members)
	{
		Ninja *ninja = dynamic_cast<Ninja *>(member);

		if (ninja != nullptr)
			cout << ninja->print() << endl;
	}
}

Team2::Team2(Character *leader) : Team(leader) {}

void Team2::attack(Team *enemy)
{
	if (enemy == nullptr)
		throw invalid_argument("Invalid enemy");

	if (enemy == this)
		throw runtime_error("Cannot attack self team!");

	// First check if any members of the enemy team are still alive
	if (enemy->stillAlive() == 0)
		throw runtime_error("There are no members of the enemy team that are still alive.");

	if (stillAlive() == 0)
		throw runtime_error("There are no members of the attacking team that are still alive.");

	// Second check if the leader of the attacking team is alive
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

	// Third, find the closest enemy to the leader of the attacking team
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

	// Finally, attack the closest enemy
	for (Character *member : getMembers())
	{
		if (member->isAlive())
		{
			Cowboy *cowboy = dynamic_cast<Cowboy *>(member);

			if (cowboy != nullptr)
			{
				if (cowboy->hasboolets())
					cowboy->shoot(closestEnemy);

				else
					cowboy->reload();
			}

			else
			{
				Ninja *ninja = dynamic_cast<Ninja *>(member);

				if (ninja->distance(closestEnemy) <= 1)
					ninja->slash(closestEnemy);

				else
					ninja->move(closestEnemy);
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

void Team2::print() const
{
	for (Character *member : getMembers())
		cout << member->print() << endl;
}

SmartTeam::SmartTeam(Character *leader) : Team(leader) {}

void SmartTeam::attack(Team *enemy)
{
	if (enemy == nullptr)
		throw invalid_argument("Invalid enemy");

	if (enemy == this)
		throw runtime_error("Cannot attack self team!");

	// First check if any members of the enemy team are still alive
	if (enemy->stillAlive() == 0)
		throw runtime_error("There are no members of the enemy team that are still alive.");

	if (stillAlive() == 0)
		throw runtime_error("There are no members of the attacking team that are still alive.");

	// Second check if the leader of the attacking team is alive
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

	// Third, find the closest enemy to the leader of the attacking team
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
	// First, the ninjas attack
	for (Character *member : getMembers())
	{
		if (member->isAlive())
		{
			Ninja *ninja = dynamic_cast<Ninja *>(member);

			if (ninja != nullptr)
			{
				if (ninja->distance(closestEnemy) <= 1)
					ninja->slash(closestEnemy);

				else
				{
					while (ninja->distance(closestEnemy) > 1)
					{
						ninja->move(closestEnemy);
					}
					ninja->slash(closestEnemy);
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
	// Second , the cowboys attack
	for (Character *member : getMembers())
	{
		if (member->isAlive())
		{
			Cowboy *cowboy = dynamic_cast<Cowboy *>(member);

			if (cowboy != nullptr)
			{
				if (cowboy->hasboolets())
					cowboy->shoot(closestEnemy);

				else
					cowboy->reload();
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

void SmartTeam::print() const {}
