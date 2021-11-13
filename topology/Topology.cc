#include "Topology.h"

namespace icts {

double Topology::_esp = 1e-6;

vector<Point<int>> Topology::build_topology(const vector<Point<int>> &points) {
    auto leaf_node_num = points.size();
    int  internal_node_num = compute_internal_node_num(leaf_node_num);

    vector<Edge> edges;
    build_edges(edges, points);
    sort(edges.begin(), edges.end(),
         [](Edge front, Edge back) { return front.get_weight() < back.get_weight(); });

    map<Point<int>, bool> visiteds;
    for (auto point : points) {
        visiteds[point] = false;
    }

    vector<Point<int>> complete_binary_tree(internal_node_num);
    add_leaf_node(complete_binary_tree, edges, visiteds);

    return complete_binary_tree;
}

int Topology::compute_internal_node_num(int leaf_node_num) {
    double exponent_float = log(leaf_node_num) / log(2);
    int    exponent_int = static_cast<int>(exponent_float);
    double difference = fabs(exponent_float - exponent_int);

    int level_num = difference < _esp ? exponent_int : exponent_int + 1;
    int internal_node_num = pow(2, level_num) - 1;

    return internal_node_num;
}

void Topology::build_edges(vector<Edge> &edges, const vector<Point<int>> &points) {
    auto vertex_num = points.size();

    for (size_t i = 0; i < vertex_num; ++i) {
        for (size_t j = i + 1; j < vertex_num; ++j) {
            auto front = points[i];
            auto back = points[j];
            auto weight = manhattan_distance(front, back);
            edges.emplace_back(Edge(front, back, weight));
        }
    }
}

void Topology::add_leaf_node(vector<Point<int>> &complete_binary_tree, vector<Edge> &edges,
                             map<Point<int>, bool> &visiteds) {
    while (!edges.empty()) {
        auto edge = edges.front();
        auto front = edge.get_front();
        auto back = edge.get_back();

        // add two leaf node and set visited flag
        complete_binary_tree.emplace_back(front);
        complete_binary_tree.emplace_back(back);
        visiteds[front] = true;
        visiteds[back] = true;

        // delete the edges related with two vertex
        auto remove_rule = [&front, &back](auto &edge) {
            return (edge.get_front() == front || edge.get_front() == back) ||
                   (edge.get_back() == front || edge.get_back() == back);
        };
        edges.erase(remove_if(edges.begin(), edges.end(), remove_rule), edges.end());
    }

    auto leaf_node_num = visiteds.size();
    if (leaf_node_num % 2 == 1) {
        for (auto &visited : visiteds) {
            if (visited.second == false) {
                complete_binary_tree.push_back(visited.first);
                break;
            }
        }
    }
}

int Topology::manhattan_distance(const Point<int> &first, const Point<int> &second) {
    return abs(first.get_x() - second.get_x()) + abs(first.get_y() - second.get_y());
}

} // namespace icts
