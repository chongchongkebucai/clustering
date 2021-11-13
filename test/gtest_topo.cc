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

TEST(GeneraterTopology, gt) {
    vector<Point<int>> points = {Point<int>(0, 0), Point<int>(0, 2), Point<int>(2, 3),
                                 Point<int>(4, 0), Point<int>(4, 1)};
    Topology           topo;
    vector<Point<int>> comp_binary_tree = topo.build_topology(points);
    for (auto elem : comp_binary_tree) {
        std::cout << "(" << elem.get_x() << ", " << elem.get_y() << ")" << std::endl;
    }

    EXPECT_TRUE(1);
}

// TEST(PathSolverTest, NotReached) {}
