#include <Point.h>

namespace icts {
class Edge {
public:
    Edge() = default;
    Edge(const Point<int> &front, const Point<int> &back, int weight = 0)
        : _front(front), _back(back), _weight(weight) {}
    ~Edge() = default;

    // setter
    void set_front(const Point<int> &front) { _front = front; }
    void set_back(const Point<int> &back) { _back = back; }
    void set_weight(int weight) { _weight = weight; }

    // getter
    Point<int> get_front() const { return _front; }
    Point<int> get_back() const { return _back; }
    int        get_weight() const { return _weight; }

private:
    Point<int> _front;
    Point<int> _back;
    int        _weight;
};
} // namespace icts