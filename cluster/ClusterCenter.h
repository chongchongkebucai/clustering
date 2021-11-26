#include "Point.h"

namespace icts {

template <typename T>
class ClusterCenter {
public:
    ClusterCenter() = default;
    ClusterCenter(const Point<int> &location, int count = 0) : _location(location), _count(count) {}
    ~ClusterCenter() = default;

    // getter
    Point<int> get_location() const { return _location; }
    int        get_count() const { return _count; }

    // setter
    void set_location(const Point<int> &location) { _location = location; }
    void set_count(int count) { _count = count; }

    // operator
    void increase_count(int addend) { _count += addend; }

private:
    Point<int> _location;
    int        _count;
};

} // namespace icts