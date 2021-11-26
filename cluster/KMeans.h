#include "ClusterCenter.h"
#include "ClusterPoint.h"
#include "Point.h"

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

using namespace std;
namespace icts {

template <typename T>
class KMeans {
public:
    vector<vector<T *>> kmeans(const std::vector<T *> &points, int k);
    static KMeans &     get_instance();

private:
    KMeans() = default;
    ~KMeans() = default;
    KMeans(const KMeans &) = delete;
    KMeans &operator=(const KMeans &) = delete;

    void init(const std::vector<T *> &points, int k);
    void partition_point();
    void compute_center_coords(vector<pair<double, double>> &center_coords);
    bool update_center_coords(std::vector<std::pair<double, double>> &center_coords);
    int  manhattan_distance(const Point<int> &first, const Point<int> &second);

private:
    std::vector<ClusterPoint<T>>  _cluster_points;
    std::vector<ClusterCenter<T>> _cluster_centers;
    static int                    _precision;
};

template <typename T>
int KMeans<T>::_precision = 1;

template <typename T>
KMeans<T> &KMeans<T>::get_instance() {
    static KMeans instance;
    return instance;
}

template <typename T>
vector<vector<T *>> KMeans<T>::kmeans(const std::vector<T *> &points, int k) {
    init(points, k);

    int  count = 1;
    bool update_flag = true;
    while (update_flag) {
        partition_point();

        vector<pair<double, double>> center_coords(k);
        compute_center_coords(center_coords);

        update_flag = update_center_coords(center_coords);
        std::cout << "update " << count++ << " times!" << std::endl;
    }

    vector<vector<T *>> clusters(k);
    for (auto &cluster_point : _cluster_points) {
        auto index = cluster_point.get_index();
        auto data = cluster_point.get_data();

        clusters[index].push_back(data);
    }

    return clusters;
}

template <typename T>
void KMeans<T>::init(const std::vector<T *> &points, int k) {
    _cluster_centers.clear();
    _cluster_points.clear();
    
    int points_num = points.size();
    int cluster_size = points_num / k;

    // set center point of cluster
    for (int i = 0; i < k; ++i) {
        auto             point = points[i * cluster_size];
        auto             center = point->get_location();
        ClusterCenter<T> cluster_center(center);
        _cluster_centers.emplace_back(cluster_center);
    }

    for (auto &point : points) {
        ClusterPoint<T> cluster_point(point);
        _cluster_points.emplace_back(cluster_point);
    }
}

template <typename T>
void KMeans<T>::partition_point() {
    auto k = _cluster_centers.size();

    // clear cluster
    for (auto &cluster : _cluster_centers) {
        cluster.set_count(0);
    }

    // partiotion
    for (auto &cluster_point : _cluster_points) {
        double min_dist = INT_MAX;
        auto   cur_location = cluster_point.get_data()->get_location();

        for (size_t idx = 0; idx < k; ++idx) {
            auto center_location = _cluster_centers[idx].get_location();
            auto dist = manhattan_distance(cur_location, center_location);
            if (dist < min_dist) {
                min_dist = dist;
                cluster_point.set_index(idx);
            }
        }

        auto cluster_index = cluster_point.get_index();
        _cluster_centers[cluster_index].increase_count(1);
    }
}

template <typename T>
void KMeans<T>::compute_center_coords(vector<pair<double, double>> &center_coords) {
    for (auto &cluster_point : _cluster_points) {
        auto   index = cluster_point.get_index();
        auto   location = cluster_point.get_data()->get_location();
        double coord_x = location.get_x();
        double coord_y = location.get_y();

        int cluster_size = _cluster_centers[index].get_count();
        center_coords[index].first += coord_x / cluster_size;
        center_coords[index].second += coord_y / cluster_size;
    }
}

template <typename T>
bool KMeans<T>::update_center_coords(vector<pair<double, double>> &center_coords) {
    auto k = _cluster_centers.size();

    bool is_update = false;
    for (size_t idx = 0; idx < k; ++idx) {
        int coord_x = static_cast<int>(center_coords[idx].first + 0.5);
        int coord_y = static_cast<int>(center_coords[idx].second + 0.5);

        auto &cluster_center = _cluster_centers[idx];
        auto  center_location = cluster_center.get_location();

        if (coord_x != center_location.get_x() || coord_y != center_location.get_y()) {
            is_update = true;
        }
        _cluster_centers[idx].set_location(Point<int>(coord_x, coord_y));
    }
    return is_update;
}

template <typename T>
int KMeans<T>::manhattan_distance(const Point<int> &first, const Point<int> &second) {
    return abs(first.get_x() - second.get_x()) + abs(first.get_y() - second.get_y());
}

} // namespace icts
