#pragma once
#include <string>

namespace ariel
{
	class Point
	{
		private:
			// x-coordinate of the point
			double x;

			// y-coordinate of the point
			double y;

		public:
			// Default constructor
			Point();

			// Constructor that get the value of x and y
			Point(double xValue, double yValue);

			// This function calculate the distance between this point and another point
			double distance(Point otherPoint) const;

			// This function return a string that represent the point
			std::string print() const;

			// The function returns the closest point to the destination point, which is at most
			// the given distance from the source point
			static Point moveTowards(const Point &curr, const Point &other, double distance);

			// getX() function
			double getX() const;

			// getY() function
			double getY() const;
	};
}