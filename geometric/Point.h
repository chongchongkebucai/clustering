#pragma once

namespace icts {

template <typename T>
class Point {
public:
    Point() = default;
    Point(int x, int y) : _x(x), _y(y) {}
    ~Point() = default;

    // getter
    T get_x() const { return _x; }
    T get_y() const { return _y; }

    // setter
    void set_x(T x) { _x = x; }
    void set_y(T y) { _y = y; }

    // operator
    bool operator==(const Point &coord) const;
    bool operator!=(const Point<T> &coord) const;
    bool operator<(const Point<T> &coord) const;

    Point<int> get_location() const { return Point<int>(_x, _y); }

private:
    T _x;
    T _y;
};

template <typename T>
bool Point<T>::operator<(const Point<T> &coord) const {
    return _y < coord.get_y() || (_y == coord.get_y() && _x < coord.get_x());
}

template <typename T>
bool Point<T>::operator==(const Point<T> &coord) const {
    return _x == coord.get_x() && _y == coord.get_y();
}

template <typename T>
bool Point<T>::operator!=(const Point<T> &coord) const {
    return _x != coord.get_x() || _y != coord.get_y();
}

} // namespace icts