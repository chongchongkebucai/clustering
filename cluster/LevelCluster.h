#pragma once
#include <algorithm>
#include <utility>
#include <vector>

#include "BinaryTree.h"
#include "GetLocation.h"

namespace icts {
using namespace std;

template <typename Value, typename LocationOfValue = GetLocation<Value>>
class LevelCluster {
public:
    typedef pair<BinaryTree<Value> *, BinaryTree<Value> *> TreePair;

    BinaryTree<Value> LevelCluster<Value, LocationOfValue>::clustering(vector<Value> values);

private:
    LocationOfValue get_location;
};

template <typename Value, typename LocationOfValue>
BinaryTree<Value>
LevelCluster<Value, LocationOfValue>::clustering(vector<Value> values) { // save data
    vector<BinaryTree<Value> *> clusters;
    for (auto value : values) {
        auto *btree = new BinaryTree<Value>(value);
        clusters.push_back(btree);
    }

    // compute distance
    vector<TreePair> dists;
    auto            len = clusters.size();
    for (size_t i = 0; i < len; ++i) {
        for (size_t j = i + 1; j < len; ++j) {
            auto left_tree = clusters[i];
            auto right_tree = clusters[j];
            dists.push_back(make_pair<TreePair>(left_tree, right_tree));
            // auto left_loc = get_location(left_tree->root_value());
            // auto right_loc = get_location(right_tree->root_value());
        }
    }
    auto cmp = [](const TreePair &front_pair, const TreePair &back_pair) {
        auto front_left_loc = get_location(front_pair.first->root_value());
        auto front_right_loc = get_location(front_pair.second->root_value());
        auto front_dist = manhatan_dist(front_left_loc, front_right_loc);

        auto back_left_loc = get_location(back_pair.first->root_value());
        auto back_right_loc = get_location(back_pair.second->root_value());
        auto back_dist = manhatan_dist(back_left_loc, back_right_loc);
        return front_dist < back_dist;
    };
    sort(dists.begin(), dists.end(), cmp);

    // merge small cluster to large cluster
    while (true) {
        TreePair tree_pair = dists.front();
        dists.
    }
}

} // namespace icts