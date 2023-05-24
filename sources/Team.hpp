#pragma once

#include <vector>
#include "Cowboy.hpp"
#include "YoungNinja.hpp"
#include "TrainedNinja.hpp"
#include "OldNinja.hpp"

namespace ariel
{
	class Team
	{
		private:
			std::vector<Character *> members;

			Character *leader;

		public:
			Team(Character *leader);
			virtual ~Team();

			// Copy constructor
			Team(const Team &other);

			// Copy assignment operator
			Team &operator=(const Team &other);

			Team(Team &&other) noexcept;
			
			Team &operator=(Team &&other) noexcept;

			void add(Character *member);

			int stillAlive() const;

			virtual void attack(Team *other);

			virtual void print() const;

			Character *getLeader() const { 
				return leader;
			}

			const std::vector<Character *> &getMembers() const {
				return members; 
			}

			void setLeader(Character *newLeader) { 
				leader = newLeader;
			}
	};
}
