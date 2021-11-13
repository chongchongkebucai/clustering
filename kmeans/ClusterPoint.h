#include "Point.h"

#include <vector>

namespace icts {

class ClusterPoint {
public:
    ClusterPoint() = default;
    ClusterPoint(const Point<int> &point) : _point(point) {}
    ClusterPoint(const Point<int> &point, int index) : _point(point), _index(index) {}
    ~ClusterPoint() = default;

    // getter
    Point<int> get_point() const { return _point; }
    int        get_index() const { return _index; }
    int        get_count() const { return _count; }

    // setter
    void set_point(const Point<int> &point) { _point = point; }
    void set_index(int index) { _index = index; }
    void set_count(int count) { _count = count; }

private:
    Point<int> _point;
    int        _index;
    int        _count;
};

} // namespace icts