#pragma once

#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include "Set.h"
#include "Dataset.h"

class KMeansDiscretization {
	int numIntervals_;
	std::vector<Set> finalPartitions_;
public:
	void init(Dataset& ds, int numIntervals);
	std::vector<Set> execute(Set& set, int numIntervals);
private:
	

	void assignToClusters(const std::vector<Point>& centroids, std::vector<Set>& clusters, Set& set);

	void updateCentroids(std::vector<Point>& centroids, std::vector<Set>& clusters, const std::vector<Point>& attributes, std::mt19937& gen, std::uniform_int_distribution<>& dis);
	double calculateDistance(double a, double b);

};
