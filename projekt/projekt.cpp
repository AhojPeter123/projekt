#include <iostream>
#include "Loader.h"
#include "KMeansDiscretization.h"

int main() {
    Loader loader;
    std::string filepath = "Iris.txt"; // Nahraď názvom svojho súboru
    std::vector<Set> sets = loader.load(filepath, ',');

   

    int numIntervals = 3; // Alebo iná hodnota podľa datasetu
   

    for (size_t i = 0; i < sets.size(); i++) {
        Set& set = sets[i];

        // Spustenie K-means diskrétnizácie
        KMeansDiscretization kmeans;
        std::vector<Set> clusters = kmeans.execute(set, numIntervals);

        // Výpis výsledkov
        std::cout << "Vysledky pre set " << i + 1 << ":" << std::endl;
        for (size_t j = 0; j < clusters.size(); j++) {
            std::cout << " Interval " << j + 1 << " (min: " << clusters[j].getMin()
                << ", max: " << clusters[j].getMax() << ")" << std::endl;

            for (const Point& point : clusters[j].getAttributes()) {
                std::cout << "  Hodnota: " << point.value << ", Trieda: " << point.className << std::endl;
            }
        }
        std::cout << std::endl;
    }

    return 0;
}