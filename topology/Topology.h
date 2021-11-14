#include <cmath>
#include <map>
#include <vector>

#include "Edge.h"
#include "Point.h"

using namespace std;

namespace icts {

template <typename T>
class Topology {
public:
    vector<T *>      build_topology(const vector<T *> &points);
    static Topology &get_instance();

private:
    Topology() = default;
    ~Topology() = default;
    Topology(const Topology &) = delete;
    Topology &operator=(const Topology &) = delete;

    int  compute_internal_node_num(int leaf_node_num);
    void build_edges(vector<Edge<T>> &edges, const vector<T *> &points);
    void add_leaf_node(vector<T *> &complete_binary_tree, vector<Edge<T>> &edges,
                       map<T *, bool> &visiteds);
    int  manhattan_distance(const Point<int> &first, const Point<int> &second);

    static double _esp;
};

template <typename T>
double Topology<T>::_esp = 1e-6;

template <typename T>
Topology<T> &Topology<T>::get_instance() {
    static Topology topo;
    return topo;
}

template <typename T>
vector<T *> Topology<T>::build_topology(const vector<T *> &points) {
    auto leaf_node_num = points.size();
    int  internal_node_num = compute_internal_node_num(leaf_node_num);

    vector<Edge<T>> edges;
    build_edges(edges, points);
    sort(edges.begin(), edges.end(),
         [](Edge<T> front, Edge<T> back) { return front.get_weight() < back.get_weight(); });

    map<T *, bool> visiteds;
    for (auto point : points) {
        visiteds[point] = false;
    }

    vector<T *> complete_binary_tree(internal_node_num, nullptr);
    add_leaf_node(complete_binary_tree, edges, visiteds);

    return complete_binary_tree;
}

template <typename T>
int Topology<T>::compute_internal_node_num(int leaf_node_num) {
    double exponent_float = log(leaf_node_num) / log(2);
    int    exponent_int = static_cast<int>(exponent_float);
    double difference = fabs(exponent_float - exponent_int);

    int level_num = difference < _esp ? exponent_int : exponent_int + 1;
    int internal_node_num = pow(2, level_num) - 1;

    return internal_node_num;
}

template <typename T>
void Topology<T>::build_edges(vector<Edge<T>> &edges, const vector<T *> &points) {
    auto vertex_num = points.size();

    for (size_t i = 0; i < vertex_num; ++i) {
        for (size_t j = i + 1; j < vertex_num; ++j) {
            auto front_location = points[i]->get_location();
            auto back_location = points[j]->get_location();
            auto weight = manhattan_distance(front_location, back_location);
            edges.emplace_back(Edge<T>(points[i], points[j], weight));
        }
    }
}

template <typename T>
void Topology<T>::add_leaf_node(vector<T *> &complete_binary_tree, vector<Edge<T>> &edges,
                                map<T *, bool> &visiteds) {
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

template <typename T>
int Topology<T>::manhattan_distance(const Point<int> &first, const Point<int> &second) {
    return abs(first.get_x() - second.get_x()) + abs(first.get_y() - second.get_y());
}

} // namespace icts
