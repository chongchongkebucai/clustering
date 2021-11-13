#include "KMeans.h"

#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
using namespace icts;

int main() {
    KMeans clustering;
    // Test 1
    // std::vector<Point<int>> points = {
    //     Point<int>(1, 1), Point<int>(2, 3), Point<int>(3, 2), Point<int>(1, 2), Point<int>(5, 8),
    //     Point<int>(6, 6), Point<int>(5, 7), Point<int>(5, 6), Point<int>(6, 7), Point<int>(7, 1),
    //     Point<int>(8, 2), Point<int>(9, 1), Point<int>(9, 3)};

    // Test 2
    // vector<Point<int>> points;
    // srand((int)time(0));
    // for (int i = 0; i < 1000; ++i) {
    //     auto       coord_x = rand() % 10000;
    //     auto       coord_y = rand() % 10000;
    //     Point<int> point(coord_x, coord_y);
    //     points.emplace_back(point);
    // }

    vector<Point<int>> points;
    string             line;
    int                coord_x;
    int                coord_y;
    ifstream           ifs("coord.txt");
    while (getline(ifs, line)) {
        istringstream iss(line);
        iss >> coord_x >> coord_y;
        points.emplace_back(Point<int>(coord_x, coord_y));
    }
    ifs.close();

    int    cluster_size = 16;
    size_t cluster_num = points.size() % cluster_size == 0 ? points.size() / cluster_size
                                                           : points.size() / cluster_size + 1;
    vector<vector<Point<int>>> clusters = clustering.kmeans(points, cluster_num);

    ofstream out("coordination.dot");
    for (size_t idx = 0; idx < cluster_num; ++idx) {
        auto &cluster = clusters[idx];
        for (auto &point : cluster) {
            out << idx << " " << point.get_x() << " " << point.get_y() << endl;
        }
        out << endl;
    }
    out.close();
}