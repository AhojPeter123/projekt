#include "Set.h"


// Getter pre minimum
double& Set::getMin() {
    return min_;
}

// Getter pre maximum
double& Set::getMax() {
    return max_;
}

// Setter pre minimum
void Set::setMin(double min) {
    min_ = min;
}

// Setter pre maximum
void Set::setMax(double max) {
    max_ = max;
}

// Vypočíta veľkosť intervalu (max - min)
double Set::size() {
    return std::abs(max_ - min_);
}

// Getter pre názov
std::string& Set::getName() {
    return name_;
}

// Getter pre atribúty
std::vector<Point>& Set::getAttributes() {
    return attributes_;
}

// Setter pre atribúty
void Set::setAttributes(std::vector<Point> attributes) {
    attributes_ = attributes;
}

void Set::sort() {
    std::sort(attributes_.begin(), attributes_.end(),
        [](const Point& a, const Point& b) {
            return a.value < b.value;
        });
}
