#pragma once

#include "Character.hpp"
#include "Point.hpp"
#include <iostream>

namespace ariel
{
	class Cowboy : public Character
	{
		private:
			int bullets;

		public:
			// Constructor
			Cowboy(std::string name, const Point &loc);

			// Copy constructor
			Cowboy(const Cowboy &other);

			// Copy assignment operator
			Cowboy &operator=(const Cowboy &other);

			// Move constructor
			Cowboy(Cowboy &&other) noexcept;

			// Move assignment operator
			Cowboy &operator=(Cowboy &&other) noexcept;

			// Destructor
			~Cowboy() override;

			// Set the number of bullets
			void setBullets(int num);

			// Shoot at an enemy character
			void shoot(Character *enemy);

			// Check if the cowboy has bullets
			bool hasboolets() const;

			// Reload bullets
			void reload();

			// Print cowboy information
			std::string print() const override;
	};
}