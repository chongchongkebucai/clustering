/**
 * @file graph.h
 * @author congx
 * @brief This is google test class to check if program is rigth.
 * @version 0.1
 * @date 2021-09-05
 *
 * @copyright Copyright (c) 2021 PCL
 *
 */

#include <gtest/gtest.h>
#include <iostream>
#include <vector>

#include "Point.h"
#include "Topology.h"

using namespace std;
using namespace icts;

TEST(case1, topo) {
    vector<Point<int> *> points = {new Point<int>(0, 0), new Point<int>(0, 2), new Point<int>(2, 3),
                                   new Point<int>(4, 0), new Point<int>(4, 1)};

    auto &               topo = Topology<Point<int>>::get_instance();
    vector<Point<int> *> comp_binary_tree = topo.build_topology(points);
    for (auto elem : comp_binary_tree) {
        if (elem != nullptr) {
            std::cout << "(" << elem->get_location().get_x() << ", " << elem->get_location().get_y()
                      << ")" << std::endl;
        }
    }
    for (auto point : points) {
        delete point;
    }

    EXPECT_TRUE(1);
}

// TEST(PathSolverTest, NotReached) {}
