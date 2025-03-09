#include "Loader.h"


std::vector<Set> Loader::load(std::string filepath) {

    std::vector<Set> valueSets;
    std::ifstream file(filepath);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath;
    }

    std::string line;
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        int rowIndex = 0;
        std::string word;
        
        std::vector<std::string> words;
        while (std::getline(ss, word, ';'))
        {
            words.push_back(word);
        }
        
       
        for (std::string s : words) {
            if (isConvertible(s))
            {
                Point p;
                p.value = stod(s);
                p.className = "nazov";
                if (rowIndex >= valueSets.size()) {
                    valueSets.resize(rowIndex + 1);
                }
                valueSets.at(rowIndex).getAttributes().push_back(p);
                rowIndex++;
            }
        }
        rowIndex = 0;
    }

    return valueSets;
}




double Loader::toDouble(std::string s)
{
     return std::stod(s); 
}

bool Loader::isConvertible(std::string s)
{
    try {
        std::stod(s);
        return true;
    }
    catch (const std::invalid_argument& e) {
        return false;
    }
}