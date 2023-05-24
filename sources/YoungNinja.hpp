#pragma once

#include "Ninja.hpp"

namespace ariel
{
	// YoungNinja class (inherits from Ninja):
	class YoungNinja : public Ninja
	{
	public:
		// Constructor
		YoungNinja(std::string name, const Point &loc);

		// print()
		std::string print() const override;
	};
}