#pragma once
#include <vector>

#include "GetLocation.h"

namespace icts {
using namespace std;

template <typename Value, typename LocationOfValue = GetLocation<Value>>
class LevelCluster {
public:
    vecctor<vector<BTNode *>> clustering(vector<Value> values);

private:
};

template <typename Value, typename LocationOfValue>
vecctor<vector<BTNode *>> LevelCluster<Value, LocationOfValue>::clustering(vector<Value> values) {}

} // namespace icts