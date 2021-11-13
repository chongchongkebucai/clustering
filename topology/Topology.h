#include <map>
#include <vector>
#include <cmath>

#include "Edge.h"
#include "Point.h"

using namespace std;

namespace icts {

class Topology {
public:
    vector<Point<int>> build_topology(const vector<Point<int>> &points);

private:
    int  compute_internal_node_num(int leaf_node_num);
    void build_edges(vector<Edge> &edges, const vector<Point<int>> &points);
    void add_leaf_node(vector<Point<int>> &complete_binary_tree, vector<Edge> &edges,
                       map<Point<int>, bool> &visiteds);
    int  manhattan_distance(const Point<int> &first, const Point<int> &second);

    static double _esp;
};
} // namespace icts
