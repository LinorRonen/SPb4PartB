#include "Point.hpp"
#include <cmath>
#include <string>
#include <stdexcept>

using namespace std;
using namespace ariel;

// Default constructor
Point::Point() : x(0), y(0) {}

// Constructor that get the value of x and y
Point::Point(double x, double y) : x(x), y(y) {}

// This function calculate the distance between this point and another point
double Point::distance(Point otherPoint) const
{
	double dx = this->x - otherPoint.getX();
	double dy = this->y - otherPoint.getY();
	return std::sqrt(dx * dx + dy * dy);
}

// This function return a string that represent the point
string Point::print() const
{
	return "(" + to_string(x) + ", " + to_string(y) + ")";
}

// The function returns the closest point to the destination point, which is at most
// the given distance from the source point. If the distance is negative, an exception is thrown.
Point Point::moveTowards(const Point &curr, const Point &other, double distance)
{
	if (distance < 0)
	{
		throw invalid_argument("Distance cannot be negative");
	}
	double dx = other.x - curr.x;
	double dy = other.y - curr.y;
	double distanceBetweenPoints = sqrt(dx * dx + dy * dy);

	if (distanceBetweenPoints <= distance)
	{
		return other;
	}

	double proportion = distance / distanceBetweenPoints;
	double newX = curr.x + dx * proportion;
	double newY = curr.y + dy * proportion;
	return Point(newX, newY);
}

// getX() function
double Point::getX() const
{
	return x;
}

// getY() function
double Point::getY() const
{
	return y;
}
