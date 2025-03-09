#include "KMeansDiscretization.h"
#include "Dataset.h"

// Main function to discretize a dataset into specified number of intervals using K-means clustering
std::vector<Set> KMeansDiscretization::execute(Set& set, int numIntervals)
{
    // Sort the input set initially
    set.sort();

    // Get all points from the set
    const std::vector<Point>& attributes = set.getAttributes();

    // Initialize centroids vector with number of desired intervals
    std::vector<Point> centroids(numIntervals);

    // Set up random number generation for initial centroid selection
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, attributes.size() - 1);

    // Randomly select initial centroids from the dataset
    for (int i = 0; i < numIntervals; ++i)
    {
        centroids[i] = attributes[dis(gen)];
    }

    // Create clusters vector to store points assigned to each centroid
    std::vector<Set> clusters(numIntervals);

    // K-means clustering loop
    while (true)
    {
        // Assign points to nearest centroid
        assignToClusters(centroids, clusters, set);

        // Calculate new centroids based on current clusters
        std::vector<Point> newCentroids(numIntervals);
        updateCentroids(newCentroids, clusters);

        // Check if centroids have stabilized (converged)
        bool converged = true;
        for (int i = 0; i < numIntervals; ++i)
        {
            if (centroids[i].value != newCentroids[i].value)
            {
                converged = false;
                break;
            }
        }
        if (converged)
        {
            break;
        }
        centroids = newCentroids;  // Update centroids for next iteration
    }

    // Sort clusters based on minimum value
    std::sort(clusters.begin(), clusters.end(), [](Set& a, Set& b) {
        return a.getMin() < b.getMax();
        });

    // Set interval boundaries between adjacent clusters
    for (int i = 0; i < clusters.size() - 1; i++)
    {
        // Set max of current cluster and min of next cluster to midpoint between clusters
        clusters.at(i).setMax((clusters.at(i + 1).getAttributes().front().value + clusters.at(i).getAttributes().back().value) / 2);
        clusters.at(i + 1).setMin((clusters.at(i + 1).getAttributes().front().value + clusters.at(i).getAttributes().back().value) / 2);
    }

    return clusters;  // Return the discretized intervals
}

// Assigns points to their nearest centroid
void KMeansDiscretization::assignToClusters(const std::vector<Point>& centroids, std::vector<Set>& clusters, Set& set)
{
    // Temporary storage for points assigned to each centroid
    std::vector<std::vector<Point>> assignedPoints(centroids.size());

    // For each point in the dataset
    for (auto point : set.getAttributes())
    {
        double minDistance = std::numeric_limits<double>::infinity();
        int closestCentroidIndex = -1;

        // Find the closest centroid
        for (int i = 0; i < centroids.size(); ++i)
        {
            double distance = std::abs(point.value - centroids[i].value);
            if (distance < minDistance)
            {
                minDistance = distance;
                closestCentroidIndex = i;
            }
        }
        assignedPoints[closestCentroidIndex].push_back(point);
    }

    // Assign points to their respective clusters
    for (int i = 0; i < centroids.size(); i++)
    {
        clusters.at(i).setAttributes(assignedPoints[i]);
    }

    // Handle empty clusters by borrowing points from nearest non-empty cluster
    for (int i = 0; i < centroids.size(); ++i)
    {
        if (clusters.at(i).getAttributes().empty())
        {
            int closestNonEmptyClusterIndex = -1;
            double minDistance = std::numeric_limits<double>::infinity();

            // Find nearest non-empty cluster
            for (int j = 0; j < centroids.size(); ++j)
            {
                if (!clusters.at(j).getAttributes().empty())
                {
                    double distance = calculateDistance(centroids[i].value, centroids[j].value);
                    if (distance < minDistance)
                    {
                        minDistance = distance;
                        closestNonEmptyClusterIndex = j;
                    }
                }
            }

            // Move one point from nearest non-empty cluster to empty cluster
            if (closestNonEmptyClusterIndex != -1)
            {
                Point pointToMove = clusters.at(closestNonEmptyClusterIndex).getAttributes().front();
                clusters.at(closestNonEmptyClusterIndex)
                    .getAttributes()
                    .erase(clusters.at(closestNonEmptyClusterIndex).getAttributes().begin());
                clusters.at(i).getAttributes().push_back(pointToMove);
            }
        }
    }
}

// Updates centroids based on mean of points in each cluster
void KMeansDiscretization::updateCentroids(std::vector<Point>& centroids, std::vector<Set>& clusters)
{
    for (int i = 0; i < centroids.size(); i++)
    {
        clusters.at(i).sort();  // Sort cluster points
        double sum = 0.0;

        // Calculate sum of all point values in cluster
        for (const Point& point : clusters.at(i).getAttributes())
        {
            sum += point.value;
        }
        // Set new centroid as mean of cluster points
        centroids.at(i).value = sum / clusters.at(i).size();
    }
}

// Helper function to calculate distance between two values
double KMeansDiscretization::calculateDistance(double a, double b)
{
    return abs(a - b);  // Returns absolute difference between two values
}