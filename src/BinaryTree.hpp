#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <iostream>
#include <stack>
#include <deque>
#include <cstdlib>
#include "common.h"

using namespace std;

template<class T>
class AvlTree;

template<class T>
struct BinaryNode {
    T element;
    BinaryNode<T> *lchild;
    BinaryNode<T> *rchild;
    int height;

    BinaryNode<T>(T el = T(), BinaryNode<T> *_lchild = NULL, BinaryNode<T> *_rchild = NULL)
            : element(el), lchild(_lchild), rchild(_rchild), height(0) { }
};

template<typename T>
class BinaryTree {
public:
    friend class AvlTree<T>;

    BinaryTree() : root(NULL) { }

    virtual ~BinaryTree() { };

    bool contains(T t) {
        return contains(t, root);
    }

    virtual void insert(const T &t) {
        insert(t, root);
    }

    virtual void remove(const T &el) {
        remove(el, root);
    }

    void preorder() {
        preorder(root);
        cout << endl;
    }

    void inorder() {
        inorder(root);
        cout << endl;
    }

    void postorder() {
        postorder(root);
        cout << endl;
    }

    void preorder_no_recursive() {
        stack<BinaryNode<T> *> st;
        st.push(root);
        while (!st.empty()) {
            BinaryNode<T> *temp = st.top();
            st.pop();
            cout << temp->element << " ";
            if (temp->rchild)
                st.push(temp->rchild);
            if (temp->lchild)
                st.push(temp->lchild);
        }
        cout << endl;
    }

    void preorder_no_recursive2() {
        stack<BinaryNode<T> *> st;
        BinaryNode<T> *node = root;
        while (!st.empty() || node) {
            while (node) {
                cout << node->element << " ";
                st.push(node);
                node = node->lchild;
            }
            node = st.top()->rchild;
            st.pop();
        }
        cout << endl;
    }

    void inorder_no_recursive() {
        stack<BinaryNode<T> *> st;
        BinaryNode<T> *node = root;
        while (!st.empty() || node) {
            while (node) {
                st.push(node);
                node = node->lchild;
            }
            node = st.top();
            cout << node->element << " ";
            st.pop();
            node = node->rchild;
        }
        cout << endl;
    }

    void postorder_no_recursive() {
        stack<BinaryNode<T> *> st;
        st.push(root);
        BinaryNode<T> *preNode = NULL;
        while (!st.empty()) {
            BinaryNode<T> *node = st.top();
            if ((NULL == node->lchild && NULL == node->rchild)
                || (preNode && (node->lchild == preNode || node->rchild == preNode))) {
                st.pop();
                cout << node->element << " ";
                preNode = node;
            } else {
                if (node->rchild)
                    st.push(node->rchild);
                if (node->lchild)
                    st.push(node->lchild);
            }
        }
        cout << endl;
    }

    void level_order() {
        deque<BinaryNode<T> *> que;
        que.push_back(root);
        while (!que.empty()) {
            BinaryNode<T> *node = que.front();
            cout << node->element << " ";
            que.pop_front();
            if (node->lchild)
                que.push_back(node->lchild);
            if (node->rchild)
                que.push_back(node->rchild);
        }
        cout << endl;
    }

    void sort(T *begin, T *end) {
        BinaryTree bt;
        timer tm;
        for (T *pt = begin; pt != end; ++pt) {
            bt.insert(*pt);
        }
        cout << "insert time " << tm.elapsed() << endl;
        tm.start();
        BinaryNode<T> *node = bt.root;
        stack<BinaryNode<T> *> st;
        while (!st.empty() || node) {
            while (node) {
                st.push(node);
                node = node->lchild;
            }
            node = st.top();
            *(begin++) = node->element;
            st.pop();
            node = node->rchild;
        }
        cout << "sort time " << tm.elapsed() << endl;
    }

private:
    BinaryNode<T> *root;

    bool contains(T x, BinaryNode<T> *t) const {
        if (t == NULL)
            return false;
        else if (x < t->element)
            return contains(x, t->lchild);
        else
            return contains(x, t->rchild);
    }

    BinaryNode<T> *findMax(BinaryNode<T> *t) {
        if (NULL == t)
            return NULL;
        if (NULL == t->rchild)
            return t;
        findMax(t->rchild);
    }

    BinaryNode<T> *findMin(BinaryNode<T> *t) {
        if (t)
            while (t->lchild)
                t = t->lchild;
        return t;
    }

    void insert(const T &el, BinaryNode<T> *&t) {
        if (t == NULL)
            t = new BinaryNode<T>(el);
        else insert(el, t->element > el ? t->lchild : t->rchild);
    }

    void remove(const T &el, BinaryNode<T> *&node) {
        if (node == NULL)
            return;
        if (node->element > el)
            remove(el, node->lchild);
        else if (el > node->element)
            remove(el, node->rchild);
        else if (node->lchild && node->rchild)
            //delete node have two child
        {
            node->element = findMin(node->rchild)->element;
            remove(node->element, node->rchild);
        } else {
            BinaryNode<T> *old = node;
            node = (node->lchild) ? node->lchild : node->rchild;
            delete old;
        }
    }

    void preorder(BinaryNode<T> *t) {
        if (t == NULL)
            return;
        std::cout << t->element << " ";
        preorder(t->lchild);
        preorder(t->rchild);
    }

    void inorder(BinaryNode<T> *t) {
        if (t == NULL)
            return;
        inorder(t->lchild);
        std::cout << t->element << " ";
        inorder(t->rchild);
    }

    void postorder(BinaryNode<T> *t) {
        if (t == NULL)
            return;
        postorder(t->lchild);
        postorder(t->rchild);
        std::cout << t->element << " ";
    }
};

template<class T>
class AvlTree : public BinaryTree<T> {
public:
    int height(BinaryNode<T> *node) {
        if (node == NULL)
            return 0;
        return node->height;
    }

    void single_right_rotate(BinaryNode<T> *&node) {  //turn right when insert on left
        BinaryNode<T> *pLeft = node->lchild;
        node->lchild = pLeft->rchild;
        pLeft->rchild = node;
        node = pLeft;
        pLeft->height = max(height(pLeft->lchild), height(pLeft->rchild)) + 1;
        node->height = max(height(node->lchild), height(node->rchild)) + 1;
    }

    void single_left_rotate(BinaryNode<T> *&node) {  //turn left when insert on right
        BinaryNode<T> *oldNode = node;
        BinaryNode<T> *pRight = node->rchild;
        oldNode->rchild = pRight->lchild;
        pRight->lchild = oldNode;
        oldNode = pRight;
        node->height = max(height(node->lchild), height(node->rchild)) + 1;
        pRight->height = max(height(pRight->lchild), height(pRight->rchild)) + 1;
    }

    BinaryNode<T> * insert(const T &t, BinaryNode<T> *&node) {
        if (node == NULL) {
            BinaryNode<T> * new_node = new BinaryNode<T>(t);
            return new_node;
        }
        else if (t < node->element) {
            node->lchild =insert(t, node->lchild);
            if (height(node->lchild) - height(node->rchild) > 1) {  //从插入节点到根节点的路径上可能出现不平衡
                //insert node on left child's left child;
                if (t < node->lchild->element) {
                    single_right_rotate(node);
                }
            }
        }
        else {
            node->rchild = insert(t, node->rchild);
            if (height(node->rchild) - height(node->lchild) > 1) {
                if (t > node->rchild->element) {
                    single_left_rotate(node);
                }
            }
        }
        node->height = std::max(height(node->lchild), height(node->rchild)) + 1;
        return node;
    }

public:
    int height() {
        return height(this->root);
    }

    void insert(const T &t) {
        this->root = insert(t, this->root);
    }
};

void AvlTree_Test() {
    AvlTree<int> at;
    at.insert(1);
    cout << "h1 " << at.height() << endl;
    at.insert(2);
    cout << "h2 " << at.height() << endl;
    at.insert(3);
    cout << "h3 " << at.height() << endl;
//    at.insert(4);

    cout << "post order\n";
    at.postorder();
}

void BinaryTree_Test() {
    BinaryTree<int> bt;
    bt.insert(2);
    bt.insert(3);
    bt.insert(1);
    bt.insert(4);
    bt.insert(5);
    bt.insert(0);
    cout << "preorder\n";
    bt.preorder();
    cout << "preorder_no_recursive\n";
    bt.preorder_no_recursive();
    cout << "preorder_no_recursive2\n";
    bt.preorder_no_recursive2();
    cout << "inorder\n";
    bt.inorder();
    cout << "inorder_no_recursive\n";
    bt.inorder_no_recursive();
    cout << "postorder\n";
    bt.postorder();
    cout << "postorder_no_recursive\n";
    bt.postorder_no_recursive();
    cout << "level order\n";
    bt.level_order();
    bt.remove(2);
    cout << "after remove 2\n";
    bt.inorder_no_recursive();
    cout << "test sort\n";
    int a[] = {2, 3, 1, 5, 4};
    bt.sort(a, a + 5);
    for (auto i:a)
        cout << i << " ";
    cout << endl;
}

#endif
