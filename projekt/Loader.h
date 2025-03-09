#pragma once
#include <fstream>
#include <vector>
#include <sstream>
#include <stdexcept>
#include <iostream>

#include "Set.h"



class Loader {

public:
    std::vector<Set> load(std::string filepath, char delimiter);

private:
    double toDouble(std::string s);
    bool isConvertible(std::string s);

};