#include <vector>

namespace icts {

template <typename T>
class ClusterPoint {
public:
    ClusterPoint() = default;
    ClusterPoint(T *data, int index = 0) : _data(data), _index(index) {}
    ~ClusterPoint() = default;

    // getter
    T * get_data() const { return _data; }
    int get_index() const { return _index; }

    // setter
    void set_data(T *data) { _data = data; }
    void set_index(int index) { _index = index; }

private:
    T * _data;
    int _index;
};

} // namespace icts