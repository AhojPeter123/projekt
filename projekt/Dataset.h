#pragma once
#include <string>
#include <vector>
#include "Loader.h"



class Dataset
{
    std::vector<Set> sets;

public:
    Dataset(std::string filepath, std::vector<std::string> labels);
    Set& getSetAt(int index);
    std::vector<Set>& getSets();

};