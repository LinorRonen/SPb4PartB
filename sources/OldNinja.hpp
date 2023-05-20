#pragma once

#include "Ninja.hpp"

namespace ariel
{
	class OldNinja : public Ninja
	{
		public:
			OldNinja(std::string name, const Point &loc);

			std::string print() const override;
	};
}