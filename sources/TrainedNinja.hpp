#pragma once

#include "Ninja.hpp"

namespace ariel
{
	class TrainedNinja : public Ninja
	{
		public:
			TrainedNinja(std::string name, const Point &loc);

			std::string print() const override;
	};
}