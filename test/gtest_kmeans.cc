#include "KMeans.h"

#include <fstream>
#include <gtest/gtest.h>
#include <sstream>
#include <vector>

using namespace std;
using namespace icts;

TEST(kmeans, case1) {
    // read data from file
    string   input_file = "/home/congxiang/work/clustering/build/coord.txt";
    ifstream ifs(input_file);
    if (!ifs) {
        std::cout << "can't open file!" << std::endl;
        exit(1);
    }

    vector<Point<int> *> points;
    string               line;
    int                  coord_x;
    int                  coord_y;
    while (getline(ifs, line)) {
        istringstream iss(line);
        iss >> coord_x >> coord_y;
        points.emplace_back(new Point<int>(coord_x, coord_y));
    }
    ifs.close();

    // call clustering algorithm
    int    cluster_size = 16;
    size_t cluster_num = points.size() % cluster_size == 0 ? points.size() / cluster_size
                                                           : points.size() / cluster_size + 1;
    auto &                       clustering = KMeans<Point<int>>::get_instance();
    vector<vector<Point<int> *>> clusters = clustering.kmeans(points, cluster_num);

    // wirte data of clustering to file
    ofstream out("coordination.dot");
    for (size_t idx = 0; idx < cluster_num; ++idx) {
        auto &cluster = clusters[idx];
        for (auto point : cluster) {
            out << idx << " " << point->get_location().get_x() << " "
                << point->get_location().get_y() << endl;
        }
        out << endl;
    }
    out.close();

    // free memory
    for (auto point : points) {
        delete point;
    }

    EXPECT_TRUE(1);
}

TEST(kmeans, case2) {
    // initial data
    std::vector<Point<int> *> points = {
        new Point<int>(1, 1), new Point<int>(2, 3), new Point<int>(3, 2), new Point<int>(1, 2),
        new Point<int>(5, 8), new Point<int>(6, 6), new Point<int>(5, 7), new Point<int>(5, 6),
        new Point<int>(6, 7), new Point<int>(7, 1), new Point<int>(8, 2), new Point<int>(9, 1),
        new Point<int>(9, 3)};

    // call clustering algorithm
    auto &                       clustering = KMeans<Point<int>>::get_instance();
    int                          cluster_num = 3;
    vector<vector<Point<int> *>> clusters = clustering.kmeans(points, cluster_num);

    // print result of clustering to file
    ofstream out("coordination.dot");
    for (auto idx = 0; idx < cluster_num; ++idx) {
        auto &cluster = clusters[idx];
        for (auto point : cluster) {
            out << idx << " " << point->get_location().get_x() << " "
                << point->get_location().get_y() << endl;
        }
        out << endl;
    }
    out.close();

    // free memory
    for (auto point : points) {
        delete point;
    }
}

TEST(kmeans, case3) {
    // initial data
    vector<Point<int> *> points;
    srand((int)time(0));
    for (int i = 0; i < 1000; ++i) {
        auto coord_x = rand() % 10000;
        auto coord_y = rand() % 10000;
        points.emplace_back(new Point<int>(coord_x, coord_y));
    }

    // call clustering algorithm
    auto & clustering = KMeans<Point<int>>::get_instance();
    int    cluster_size = 16;
    size_t cluster_num = points.size() % cluster_size == 0 ? points.size() / cluster_size
                                                           : points.size() / cluster_size + 1;
    vector<vector<Point<int> *>> clusters = clustering.kmeans(points, cluster_num);

    // print result of clustering to file
    ofstream out("coordination.dot");
    for (size_t idx = 0; idx < cluster_num; ++idx) {
        auto &cluster = clusters[idx];
        for (auto point : cluster) {
            out << idx << " " << point->get_location().get_x() << " "
                << point->get_location().get_y() << endl;
        }
        out << endl;
    }
    out.close();

    // free memory
    for (auto point : points) {
        delete point;
    }
}
