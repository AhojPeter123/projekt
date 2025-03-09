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

private:
	std::vector<Set> execute(Set& set, int numIntervals);

	void assignToClusters(const std::vector<Point>& centroids, std::vector<Set>& clusters, Set& set);

	void updateCentroids(std::vector<Point>& centroids, std::vector<Set>& clusters);
	double calculateDistance(double a, double b);

};
