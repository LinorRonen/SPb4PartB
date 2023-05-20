#pragma once

#include <string>
#include "Point.hpp"

namespace ariel
{
	class Character
	{
		private:
			Point location;

			int hit_points;

			std::string name;

			bool ifInTeam;

		public:
				Character(std::string name, const Point &loc, int hit_points);

				Character(const Character &other);

				Character &operator=(const Character &other);

				Character(Character &&other) noexcept;

				Character &operator=(Character &&other) noexcept;

				virtual ~Character() {}

				bool isAlive() const;

				bool getIfInTeam() const;

				void setIfInTeam(bool ifExist);

				double distance(const Character *other) const;

				void hit(int num);

				std::string getName() const;

				int getHitPoints() const;

				Point getLocation() const;

				void setLocation(const Point &newLoc);

				virtual std::string print() const = 0;
	};
}
