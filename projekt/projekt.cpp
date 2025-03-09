#include <iostream>
#include "Loader.h"

int main() {
    Loader loader;
    std::string filepath = "/Users/danielpc/Downloads/Iris.csv"; // Nahraď názvom svojho súboru
    std::vector<Set> sets = loader.load(filepath);

    // Výpis výsledkov s klasickými for cyklami
    for (size_t i = 0; i < sets.size(); i++) {
        Set set = sets[i];

        for (size_t j = 0; j < set.getAttributes().size(); j++) {
            Point attr = set.getAttributes()[j];
            std::cout << "Hodnota: " << attr.value << ", Trieda: " << attr.className << std::endl;
        }
    }

    return 0;
}
