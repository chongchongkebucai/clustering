#pragma once

namespace icts {

template <typename T>
class GetLocation {
public:
    Point<DBU> operator()(const T &point) { return point->get_point(); }
};

} // namespace icts