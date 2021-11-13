#include "ClusterPoint.h"
#include "Point.h"

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;
namespace icts {

class KMeans {
public:
    KMeans() = default;
    ~KMeans() = default;
    vector<vector<Point<int>>> kmeans(const std::vector<Point<int>> &points, int k);

private:
    void init(const std::vector<Point<int>> &points, int k);
    void partition_point();
    void compute_center_points(vector<pair<double, double>> &centers);
    bool update_center_points(std::vector<std::pair<double, double>> &cluster_centers);
    int  manhattan_distance(const Point<int> &first, const Point<int> &second);

private:
    std::vector<ClusterPoint> _cluster_points;
    std::vector<ClusterPoint> _clusters;
    static int                _precision;
};

} // namespace icts
