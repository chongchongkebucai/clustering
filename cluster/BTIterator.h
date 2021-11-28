#pragma once

#include "BinaryTree.h"

namespace icts {

struct BTBaseIterator {
    typedef BTNodeBase *base_ptr;

    base_ptr _node;
    void     increment();
};

template <typename value>
struct BTIterator : public BTBaseIterator {
    typedef value             value_type;
    typedef value_type *      pointer;
    typedef value_type &      reference;
    typedef BTIterator<value> iterator;
    typedef BTNode<value> *   link_type;

    BTIterator() {}
    BTIterator(link_type x) { _node = x; }
    BTIterator(const iterator &iter) { _node = iter._node; }

    reference operator*() const { return ((link_type)_node)->_value; }
    pointer   operator->() const { return &(operator*()); }
    iterator &operator++();
    iterator &operator++(int);

    bool operator==(const iterator &x) const { return _node == x._node; }
    bool operator!=(const iterator &x) const { return _node != x._node; }
};

template <typename value>
BTIterator<value> &BTIterator<value>::operator++() {
    increment();
    return *this;
}

template <typename value>
BTIterator<value> &BTIterator<value>::operator++(int) {
    iterator tmp = *this;
    increment();
    return tmp;
}

void BTBaseIterator::increment() {
    if (_node->_right != nullptr) {
        _node = _node->_right;
        while (_node->_left != nullptr) {
            _node = _node->_left;
        }
    } else {
        base_ptr y = _node->_parent;
        while (_node == y->_right) {
            _node = y;
            y = y->_parent;
        }
        if (_node->_right != y) { // the right subtree is null of root node.
            _node = y;
        }
    }
}

} // namespace icts
