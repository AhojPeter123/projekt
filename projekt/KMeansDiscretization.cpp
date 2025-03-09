#include "KMeansDiscretization.h"
#include "Dataset.h"
#include <iostream>
#include <random>
#include <limits>
#include <cmath>
#include <algorithm>

// Hlavná funkcia na diskretizáciu datasetu pomocou K-means
std::vector<Set> KMeansDiscretization::execute(Set& set, int numIntervals) {
    set.sort(); // Zoradíme body pod¾a hodnoty

    const std::vector<Point>& attributes = set.getAttributes();
    std::vector<Point> centroids(numIntervals);

    // Inicializácia centroidov náhodným výberom
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, attributes.size() - 1);

    for (int i = 0; i < numIntervals; ++i) {
        centroids[i] = attributes[dis(gen)];
    }

    std::vector<Set> clusters(numIntervals);
    bool converged = false;

    while (!converged) {
        assignToClusters(centroids, clusters, set);

        std::vector<Point> newCentroids(numIntervals);
        updateCentroids(newCentroids, clusters, attributes, gen, dis); // Pridali sme parametre

        converged = true;
        for (int i = 0; i < numIntervals; ++i) {
            if (centroids[i].value != newCentroids[i].value) {
                converged = false;
                break;
            }
        }
        centroids = newCentroids;
    }

    std::sort(clusters.begin(), clusters.end(), [](Set& a, Set& b) {
        return a.getMin() < b.getMin();
        });

    for (size_t i = 0; i < clusters.size() - 1; i++) {
        double midpoint = (clusters[i].getAttributes().back().value + clusters[i + 1].getAttributes().front().value) / 2;
        clusters[i].setMax(midpoint);
        clusters[i + 1].setMin(midpoint);
    }

    return clusters;
}

void KMeansDiscretization::assignToClusters(const std::vector<Point>& centroids, std::vector<Set>& clusters, Set& set) {
    for (auto& cluster : clusters) cluster.getAttributes().clear();

    for (const auto& point : set.getAttributes()) {
        double minDistance = std::numeric_limits<double>::max();
        int closestCentroid = 0;

        for (size_t i = 0; i < centroids.size(); i++) {
            double distance = std::abs(point.value - centroids[i].value);
            if (distance < minDistance) {
                minDistance = distance;
                closestCentroid = i;
            }
        }
        clusters[closestCentroid].getAttributes().push_back(point);
    }
}

void KMeansDiscretization::updateCentroids(std::vector<Point>& centroids, std::vector<Set>& clusters, const std::vector<Point>& attributes, std::mt19937& gen, std::uniform_int_distribution<>& dis) {
    for (size_t i = 0; i < centroids.size(); i++) {
        if (clusters[i].getAttributes().empty()) {
            // Ak je klaster prázdny, preinicializujeme centroid náhodným bodom
            centroids[i] = attributes[dis(gen)];
        }
        else {
            double sum = 0.0;
            for (const Point& p : clusters[i].getAttributes()) {
                sum += p.value;
            }
            centroids[i].value = sum / clusters[i].getAttributes().size();
        }
    }
}