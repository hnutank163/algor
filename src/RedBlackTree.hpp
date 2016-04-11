//
// Created by TangXin on 2016/4/6.
//

#ifndef PROJECT_RBTREE_HPP
#define PROJECT_RBTREE_HPP

#include <iostream>

enum Color {
    RED, BLACK
};

template<class T,
        class Compare = std::less<T>()>
struct rb_node {
    static rb_node *nil;
    T value;
    rb_node *parent;
    rb_node *left;
    rb_node *right;
    Color color;

    rb_node(const T &t, rb_node *_parent, Color _color = BLACK)
            : value(t), parent(_parent), color(_color) { }

    rb_node *brother() {
        if (parent->left == this)
            return parent->right;
        return parent->left;
    }
};

template<class T,
        class Compare = std::less<T>()>
class RedBlackTree {
private:

public:
};

#endif //PROJECT_RBTREE_HPP
