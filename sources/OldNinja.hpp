#pragma once

#include "Ninja.hpp"

namespace ariel
{
	// OldNinja class (inherits from Ninja):
	class OldNinja : public Ninja
	{
	public:
		// Constructor
		OldNinja(std::string name, const Point &loc);

		// print()
		std::string print() const override;
	};
}