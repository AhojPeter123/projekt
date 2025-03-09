#pragma once
#include <string>
#include <vector>
#include <cmath>

struct Point
{
    double value;
    std::string className;
};

class Set
{
    double min_;
    double max_;
    std::string name_;
    std::vector<Point> attributes_;

public:

    double& getMin();
    double& getMax();
    void setMin(double min);
    void setMax(double max);
    double size();
    std::string& getName();
    std::vector<Point>& getAttributes();
    void setAttributes(std::vector<Point> attributes);
};