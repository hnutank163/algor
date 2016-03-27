#ifndef _BINARY_TREE_H
#define _BINARY_TREE_H
#include <iostream>
#include <cstdlib>
template<typename T>
class BinaryTree
{
public:
    BinaryTree ():root(NULL) {}
    virtual ~BinaryTree() {};
    bool contains(T t)
    {
        return contains(t, root);
    }

    void insert(const T &t)
    {
        insert(t, root);
    }

    void preorder()
    {
        preorder(root);
    }
    void inorder()
    {
        inorder(root);
    }
    void postorder()
    {
        postorder(root);
    }
private:
    struct BinaryNode {
        T element;
        BinaryNode *lchild;
        BinaryNode *rchild;
        BinaryNode(T el=T(), BinaryNode *_lchild = NULL,BinaryNode *  _rchild=NULL)
            :element(el),lchild(_lchild),rchild(_rchild) {}
    };
    BinaryNode *root;

    bool contains(T x, BinaryNode *t) const
    {
        if(t==NULL)
            return false;
        else if(x < t->element)
            return contains(x, t->lchild);
        else
            return contains(x, t->rchild);
    }

    BinaryNode * findMax(BinaryNode *t)
    {
        if( t==NULL )
            return NULL;
        if( t->rchild == NULL )
            return t;
        findMax(t->rchild);
    }

    BinaryNode * findMin(BinaryNode *t)
    {
        if( t )
            while( t->lchild )
                t = t->lchild;
        return t;
    }

    void insert(const T &el, BinaryNode *&t)
    {
        if( t == NULL )
            t = new BinaryNode(el);
        else if( el<t->element )
            insert(el, t->lchild);
        else
            insert(el, t->rchild);
    }

    void remove(T &el, BinaryNode * & node)
    {
        if( node == NULL )
            return;
        if( el < node->element)
            remove(el, node->lchild);
        else if( el > node->element )
            remove(el, node->rchild);
        else if( node->lchild && node->rchild )
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

    void preorder(BinaryNode *t)
    {
        if (t == NULL)
            return;
        std::cout << t->element << endl;
        preorder(t->lchild);
        preorder(t->rchild);
    }

    void inorder(BinaryNode *t)
    {
        if (t==NULL)
            return;
        inorder(t->lchild);
        std::cout << t->element << endl;
        inorder(t->rchild);
    }

    void postorder(BinaryNode *t)
    {
        if (t==NULL)
            return;
        postorder(t->lchild);
        postorder(t->rchild);
        std::cout << t->element << endl;
    }
};

void BinaryTree_Test()
{
    BinaryTree<int> bt;
    bt.insert(2);
    bt.insert(3);
    bt.insert(1);
    bt.insert(4);
    bt.insert(5);
    bt.insert(0);
    cout << "preorder\n";
    bt.preorder();
    cout << "inorder\n";
    bt.inorder();
    cout << "postorder\n";
    bt.postorder();

}
#endif
