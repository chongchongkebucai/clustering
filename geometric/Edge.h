namespace icts {

template <typename T>
class Edge {
public:
    Edge() = default;
    Edge(T *front, T *back, int weight = 0) : _front(front), _back(back), _weight(weight) {}
    ~Edge() = default;

    // setter
    void set_front(T *front) { _front = front; }
    void set_back(T *back) { _back = back; }
    void set_weight(int weight) { _weight = weight; }

    // getter
    T * get_front() const { return _front; }
    T * get_back() const { return _back; }
    int get_weight() const { return _weight; }

private:
    T * _front;
    T * _back;
    int _weight;
};
} // namespace icts