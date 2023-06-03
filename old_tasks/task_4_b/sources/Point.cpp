#include <cmath>
#include <stdexcept>
#include "Point.hpp"

Point::Point(double x_coord, double y_coord) : x(x_coord), y(y_coord) {}

Point::Point() : x(0), y(0) {}

double Point::distance(Point other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx * dx + dy * dy);
}

void Point::print() const
{
    std::cout << "(" << x << ", " << y << ")" << std::endl;
}

Point Point::moveTowards(Point dest, double distance)
{
    if (distance < 0)
    {
        throw std::invalid_argument("Invalid argument: distance must be non-negative");
    }

    double dx = dest.x - x;
    double dy = dest.y - y;
    double currentDistance = std::sqrt(dx * dx + dy * dy);
    if (currentDistance <= distance)
    {
        return dest;
    }
    double ratio = distance / currentDistance;
    double newX = x + ratio * dx;
    double newY = y + ratio * dy;
    return Point(newX, newY);
}

Point Point::moveTowards(Point src, Point dest, double distance)
{
    if (distance < 0)
    {
        throw std::invalid_argument("Invalid argument: distance must be non-negative");
    }
    double dx = dest.x - src.x;
    double dy = dest.y - src.y;
    double currentDistance = std::sqrt(dx * dx + dy * dy);

    if (currentDistance <= distance)
    {
        return dest;
    }
    else
    {
        double ratio = distance / currentDistance;
        double newX = src.x + ratio * dx;
        double newY = src.y + ratio * dy;
        return Point(newX, newY);
    }
}
