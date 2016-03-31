#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H

#include <iostream>
#include <stack>
#include <deque>
#include <cstdlib>

using namespace std;

template<typename T>
class BinaryTree {
public:
    BinaryTree() : root(NULL) { }

    virtual ~BinaryTree() { };

    bool contains(T t) {
        return contains(t, root);
    }

    void insert(const T &t) {
        insert(t, root);
    }

    void remove(const T &el) {
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
        stack<BinaryNode *> st;
        st.push(root);
        while (!st.empty()) {
            BinaryNode *temp = st.top();
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
        stack<BinaryNode *> st;
        BinaryNode *node = root;
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
        stack<BinaryNode *> st;
        BinaryNode *node = root;
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
        stack<BinaryNode *> st;
        st.push(root);
        BinaryNode *preNode = NULL;
        while (!st.empty()) {
            BinaryNode *node = st.top();
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
        deque<BinaryNode *> que;
        que.push_back(root);
        while (!que.empty()) {
            BinaryNode *node = que.front();
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
        for (T *pt = begin; pt != end; ++pt) {
            bt.insert(*pt);
        }
        T *pt = begin;
        while (pt != end) {
            BinaryNode *node = findMin(bt.root);
            *(begin++) = node->element;
            bt.remove(node->element);
            ++pt;
        }
    }

private:
    struct BinaryNode {
        T element;
        BinaryNode *lchild;
        BinaryNode *rchild;

        BinaryNode(T el = T(), BinaryNode *_lchild = NULL, BinaryNode *_rchild = NULL)
                : element(el), lchild(_lchild), rchild(_rchild) { }
    };

    BinaryNode *root;

    bool contains(T x, BinaryNode *t) const {
        if (t == NULL)
            return false;
        else if (x < t->element)
            return contains(x, t->lchild);
        else
            return contains(x, t->rchild);
    }

    BinaryNode *findMax(BinaryNode *t) {
        if (t == NULL)
            return NULL;
        if (t->rchild == NULL)
            return t;
        findMax(t->rchild);
    }

    BinaryNode *findMin(BinaryNode *t) {
        if (t)
            while (t->lchild)
                t = t->lchild;
        return t;
    }

    void insert(const T &el, BinaryNode *&t) {
        if (t == NULL)
            t = new BinaryNode(el);
        else if (el < t->element)
            insert(el, t->lchild);
        else
            insert(el, t->rchild);
    }

    void remove(const T &el, BinaryNode *&node) {
        if (node == NULL)
            return;
        if (el < node->element)
            remove(el, node->lchild);
        else if (el > node->element)
            remove(el, node->rchild);
        else if (node->lchild && node->rchild)
            //delete node have two child
        {
            node->element = findMin(node->rchild)->element;
            remove(node->element, node->rchild);
        } else {
            BinaryNode *old = node;
            node = (node->lchild) ? node->lchild : node->rchild;
            delete old;
        }
    }

    void preorder(BinaryNode *t) {
        if (t == NULL)
            return;
        std::cout << t->element << " ";
        preorder(t->lchild);
        preorder(t->rchild);
    }

    void inorder(BinaryNode *t) {
        if (t == NULL)
            return;
        inorder(t->lchild);
        std::cout << t->element << " ";
        inorder(t->rchild);
    }

    void postorder(BinaryNode *t) {
        if (t == NULL)
            return;
        postorder(t->lchild);
        postorder(t->rchild);
        std::cout << t->element << " ";
    }


};

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
    for(auto i:a)
        cout<<i<<" ";
    cout<<endl;
}

#endif
