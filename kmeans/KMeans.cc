#include "KMeans.h"

using namespace std;
namespace icts {

int KMeans::_precision = 1;

vector<vector<Point<int>>> KMeans::kmeans(const std::vector<Point<int>> &points, int k) {
    init(points, k);

    int  count = 1;
    bool update_flag = true;
    while (update_flag) {
        partition_point();

        vector<pair<double, double>> centers(k);
        compute_center_points(centers);

        update_flag = update_center_points(centers);
        std::cout << "update " << count++ << " times!" << std::endl;
    }

    vector<vector<Point<int>>> clusters(k);
    for (auto &cluster_point : _cluster_points) {
        auto index = cluster_point.get_index();
        auto point = cluster_point.get_point();

        clusters[index].push_back(point);
    }

    return clusters;
}

void KMeans::init(const std::vector<Point<int>> &points, int k) {
    int points_num = points.size();
    int cluster_size = points_num / k;

    // set center point of cluster
    for (int i = 0; i < k; ++i) {
        auto         center = points[i * cluster_size];
        ClusterPoint cluster(center, 0);
        _clusters.emplace_back(cluster);
    }

    for (auto &point : points) {
        ClusterPoint cluster_point(point);
        _cluster_points.emplace_back(cluster_point);
    }
}

void KMeans::partition_point() {
    auto k = _clusters.size();

    // clear cluster
    for (auto &cluster : _clusters) {
        cluster.set_count(0);
    }

    // partiotion
    for (auto &cluster_point : _cluster_points) {
        double min_dist = INT_MAX;

        for (size_t idx = 0; idx < k; ++idx) {
            auto cur_point = cluster_point.get_point();
            auto center_point = _clusters[idx].get_point();
            auto dist = manhattan_distance(cur_point, center_point);
            if (dist < min_dist) {
                min_dist = dist;
                cluster_point.set_index(idx);
            }
        }

        auto cluster_index = cluster_point.get_index();
        auto cluster_count = _clusters[cluster_index].get_count();
        _clusters[cluster_index].set_count(cluster_count + 1);
    }
}

void KMeans::compute_center_points(vector<pair<double, double>> &centers) {
    for (auto &cluster_point : _cluster_points) {
        auto   index = cluster_point.get_index();
        auto   point = cluster_point.get_point();
        double coord_x = point.get_x();
        double coord_y = point.get_y();

        int cluster_size = _clusters[index].get_count();
        centers[index].first += coord_x / cluster_size;
        centers[index].second += coord_y / cluster_size;
    }
}

bool KMeans::update_center_points(vector<pair<double, double>> &centers) {
    auto k = _clusters.size();

    bool is_update = false;
    for (size_t idx = 0; idx < k; ++idx) {
        int coord_x = static_cast<int>(centers[idx].first + 0.5);
        int coord_y = static_cast<int>(centers[idx].second + 0.5);

        auto cluster_center = _clusters[idx].get_point();
        // if (abs(coord_x - cluster_center.get_x()) >= _precision ||
        //     abs(coord_y - cluster_center.get_y()) >= _precision) {
        //     is_update = true;
        // }

        if (coord_x != cluster_center.get_x() || coord_y != cluster_center.get_y()) {
            is_update = true;
        }
        _clusters[idx].set_point(Point<int>(coord_x, coord_y));
    }
    return is_update;
}

int KMeans::manhattan_distance(const Point<int> &first, const Point<int> &second) {
    return abs(first.get_x() - second.get_x()) + abs(first.get_y() - second.get_y());
}

} // namespace icts