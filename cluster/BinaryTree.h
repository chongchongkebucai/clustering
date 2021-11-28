#pragma once

#include <utility>
#include <vector>

using namespace std;
namespace icts {

// Binary tree node base part
struct BTNodeBase {
    typedef BTNodeBase *base_ptr;

    base_ptr _parent;
    base_ptr _left;
    base_ptr _right;

    static base_ptr minimun(base_ptr x) {
        while (x->_left) {
            x = x->_left;
        }
        return x;
    }

    static base_ptr maximum(base_ptr x) {
        while (x->_right) {
            x = x->_right;
        }
        return x;
    }
};

// Binary tree base iterator
struct BTBaseIterator {
    typedef BTNodeBase *base_ptr;

    void increment() {
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

    base_ptr _node;
};

// Binary tree node
template <typename Value>
struct BTNode : public BTNodeBase {
    typedef Value               value_type;
    typedef BTNode<value_type> *link_type;

    BTNode() = default;
    BTNode(const value_type &value) : _value(value) {}

    value_type _value;
};

// Binary tree iterator
template <typename Value>
struct BTIterator : public BTBaseIterator {
    typedef Value             value_type;
    typedef value_type *      pointer;
    typedef value_type &      reference;
    typedef BTIterator<Value> iterator;
    typedef BTNode<Value> *   link_type;

    BTIterator() {}
    BTIterator(link_type x) { _node = x; }
    BTIterator(const iterator &iter) { _node = iter._node; }

    reference operator*() const { return ((link_type)_node)->_value; }
    pointer   operator->() const { return &(operator*()); }
    iterator &operator++();
    iterator  operator++(int);

    bool operator==(const iterator &x) const { return _node == x._node; }
    bool operator!=(const iterator &x) const { return _node != x._node; }
};

// Binary tree
template <typename Value>
class BinaryTree {
protected:
    typedef Value       value_type;
    typedef value_type *pointer;
    typedef value_type &reference;

    typedef BTNodeBase *        base_ptr;
    typedef BTNode<value_type>  binary_tree_node;
    typedef BTNode<value_type> *link_type;

public:
    typedef BTIterator<value_type> iterator;

    BinaryTree() : _node_count(0) { empty_init(); }
    BinaryTree(value_type root_value);
    BinaryTree(const BinaryTree &btree);
    ~BinaryTree() {
        clear();
        put_node(_header);
    }

    iterator begin() { return leftmost(); }
    iterator end() { return _header; }
    bool     empty() const { return _node_count == 0; }
    size_t   size() const { return _node_count; }
    size_t   max_size() const { return size_t(-1); }
    void     clear();

    value_type root_value() { return value((link_type)_header->_parent); }
    bool       is_root(const iterator &iter) const { return iter->_parent == _header; }
    bool       is_leaf(const iterator &iter) const;
    void       build_edges(link_type node, vector<pair<value_type, value_type>> &edges) const;
    vector<pair<value_type, value_type>> get_edges() const;

    static BinaryTree *merge(value_type root_value, BinaryTree *left_subtree,
                             BinaryTree *right_subtree);

    BinaryTree &operator=(const BinaryTree &x);

protected:
    link_type get_node() { return new binary_tree_node(); }
    void      put_node(link_type p) { delete p; }
    link_type create_node(const value_type &x) { return new binary_tree_node(x); }
    void      destroy_node(link_type p);
    link_type clone_node(link_type x);

    link_type &       root() const { return (link_type &)_header->_parent; }
    link_type &       leftmost() const { return (link_type &)_header->_left; }
    link_type &       rightmost() const { return (link_type &)_header->_right; }
    static link_type &left(link_type x) { return (link_type &)x->_left; }
    static link_type &right(link_type x) { return (link_type &)x->_right; }
    static link_type &parent(link_type x) { return (link_type &)x->_parent; }
    static reference  value(link_type x) { return x->_value; }
    static link_type  minimum(link_type x) { return (link_type)BTNodeBase::minimun(x); }
    static link_type  maximum(link_type x) { return (link_type)BTNodeBase::maximum(x); }

private:
    void      empty_init();
    void      _erase(link_type x);
    link_type _copy(link_type x, link_type y);

private:
    link_type _header;     // the parent pointer to root node
    size_t    _node_count; // node number of binary tree
};

// Binary tree iterator
template <typename Value>
BTIterator<Value> &BTIterator<Value>::operator++() {
    increment();
    return *this;
}

template <typename Value>
BTIterator<Value> BTIterator<Value>::operator++(int) {
    iterator tmp = *this;
    increment();
    return tmp;
}

// Binary tree part
template <typename Value>
BinaryTree<Value>::BinaryTree(value_type root_value) {
    empty_init();
    root() = create_node(root_value);
    leftmost() = root();
    rightmost() = _header;
}

template <typename Value>
inline void BinaryTree<Value>::empty_init() {
    _header = get_node();
    root() = nullptr;
    leftmost() = _header;
    rightmost() = _header;
}

template <typename Value>
void BinaryTree<Value>::clear() {
    if (_node_count != 0) {
        _erase(root());
        root() = nullptr;
        leftmost = _header;
        rightmost = _header;
        _node_count = 0;
    }
}

template <typename Value>
inline bool BinaryTree<Value>::is_leaf(const iterator &iter) const {
    return iter->_left == nullptr && iter->_right == nullptr;
}

template <typename Value>
BinaryTree<Value> *BinaryTree<Value>::merge(value_type root_value, BinaryTree *left_subtree,
                                            BinaryTree *right_subtree) {
    // build a new tree
    BinaryTree *tree = new BinaryTree(root_value);
    link_type   root = tree->root();
    tree->_node_count = tree->_node_count + left_subtree->size() + right_subtree->size();

    // connect two subtree to root
    left(root) = left_subtree->root();
    if (left_subtree->root() != nullptr) {
        parent(left_subtree->root()) = root;
    }
    right(root) = right_subtree->root();
    if (right_subtree->root() != nullptr) {
        parent(right_subtree->root()) = root;
    }

    // free subtree header node
    left_subtree->put_node(left_subtree->_header);
    right_subtree->put_node(right_subtree->_header);

    return tree;
}

template <typename Value>
vector<pair<Value, Value>> BinaryTree<Value>::get_edges() const {
    vector<pair<value_type, value_type>> edges;
    build_edges(root(), edges);
    return edges;
}

template <typename Value>
void BinaryTree<Value>::build_edges(link_type                             node,
                                    vector<pair<value_type, value_type>> &edges) const {
    if (node != nullptr) {
        // add edge if subtree is not null
        if (left(node) != nullptr) {
            edges.push_back(make_pair(node->_value, left(node)->_value));
        }
        if (right(node) != nullptr) {
            edges.push_back(make_pair(node->_value, right(node)->_value));
        }

        // recursive to solve the original question
        build_edges(left(node), edges);
        build_edges(right(node), edges);
    }
}

template <typename Value>
void BinaryTree<Value>::_erase(link_type x) {
    if (x != nullptr) {
        _erase(left(x));
        _erase(right(x));
        destroy_node(x);
    }
}

template <typename Value>
BinaryTree<Value> &BinaryTree<Value>::operator=(const BinaryTree &btree) {
    if (this == &btree) {
        return *this;
    }
    clear();
    if (btree.root() != nullptr) {
        root() = _copy(btree.root(), _header);
        leftmost() = minimum(root());
        rightmost() = maximum(root());
        _node_count = btree._node_count;
    }
}

template <typename Value>
BinaryTree<Value>::link_type BinaryTree<Value>::_copy(link_type x, link_type parent) {
    link_type child_root = clone_node(x);
    child_root->_parent = parent;

    if (x->_right) {
        child_root->_right = _copy(right(x), child_root);
    }
    parent = child_root;
    x = left(x);

    while (x != nullptr) {
        link_type y = clone_node(x);
        parent->_left = y;
        y->_parent = parent;
        if (x->_right) {
            y->_right = _copy(right(x), y);
        }
        parent = y;
        x = left(x);
    }

    return child_root;
}

template <typename Value>
void BinaryTree<Value>::destroy_node(link_type p) {
    // p->~decltype (&p->_value)();
    put_node(p);
}

template <typename Value>
BTNode<Value> *BinaryTree<Value>::clone_node(link_type x) {
    link_type tmp = create_node(x->_value);
    tmp->_left = nullptr;
    tmp->_right = nullptr;
    tmp->_parent = nullptr;
    return tmp;
}

} // namespace icts
