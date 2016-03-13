#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>
template<typename Object>
class Stack
{
public:
    Stack(){
        head = new Node();
        _size = 0;
    }
    virtual ~Stack() { _delete(); }
    void _delete()
    {
        while(head)
        {
            delete head;
            head = head->next;
        }
    }
    void push(const Object &obj)
    {
        ++ _size;
        Node * node = new Node(obj, head);
        head = node;
    }

    Object & top(){return head->data;}
    const Object & top() const { return head->data; }
    bool empty(){return 0 == _size;}
    size_t size(){ return _size; }
    void pop(){
        -- _size;
        Node * old =head;
        head = head->next;
        delete old;
    }

    friend std::ostream & operator<< (std::ostream &os, const Stack &st)
    {
        Node *node = st.head;
        while(node->next)
        {
            os<<node->data<<" ";
            node = node->next;
        }
        return os;
    }
private:
    struct Node
    {
        Object data;
        Node * next;
        Node(Object _data=Object(), Node *_next =NULL):data(_data), next(_next)
        {
            
        }
    };

    Node *head;
    size_t _size;
};
#endif
