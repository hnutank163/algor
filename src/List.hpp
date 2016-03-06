#ifndef _LIST_H
#define _LIST_H 
#include <stdio.h>
template<class Object>
class List
{
private:
    struct Node
    {
        Object data;
        Node *pre;
        Node * next;
        Node(const Object &obj = Object(), Node *p=NULL, Node *n = NULL)
        :data(obj), pre(p), next(n) 
        {
            
        }
    };

    Node *head;
    Node *tail;
    int theSize;
public:
    void init()
    {
        head = new Node();
        tail = new Node();
        theSize = 0;
        head->next  = tail;
        tail->pre = head;
    }
    List(){ init(); }
    ~List(){}
    
};
#endif /* ifndef _LIST_H */
