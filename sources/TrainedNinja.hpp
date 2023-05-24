#pragma once

#include "Ninja.hpp"

namespace ariel
{
	// TrainedNinja class (inherits from Ninja):
	class TrainedNinja : public Ninja
	{
	public:
		// Constructor
		TrainedNinja(std::string name, const Point &loc);

		// print()
		std::string print() const override;
	};
}