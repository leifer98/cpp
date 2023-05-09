#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>

#include "Team.hpp"

// constructor
Point::Point(double x_coord, double y_coord)
    : x(x_coord), y(y_coord)
{
}

// compute distance between two points
double Point::distance(Point other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    return std::sqrt(dx*dx + dy*dy);
}

// print point coordinates
void Point::print() const
{
    std::cout << "(" << x << ", " << y << ")";
}

// move towards a destination point
Point Point::moveTowards(Point dest, double distance) const
{
    double d = this->distance(dest);
    if (d <= distance) {
        // move directly to the destination point
        return dest;
    } else {
        // move along the line connecting the two points
        double dx = dest.x - x;
        double dy = dest.y - y;
        double factor = distance / d;
        double new_x = x + factor * dx;
        double new_y = y + factor * dy;
        return Point(new_x, new_y);
    }
}

