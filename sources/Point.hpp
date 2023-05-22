#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cassert>
#include <vector>

class Point
{

public:
    double x; // x coordinate
    double y; // y coordinate
    // constructor
    Point(double x_coord, double y_coord);
    Point();

    // compute distance between two points
    double distance(Point other) const;

    // print point coordinates
    void print() const;

    // move towards a destination point
    Point moveTowards(Point dest, double distance);

    // move towards a destination point
    static Point moveTowards(Point src, Point dest, double distance);
};