////
//// Created by TangXin on 2016/4/6.
////
//
//#ifndef PROJECT_SET_HPP
//#define PROJECT_SET_HPP
//#include <set>
//#include <iostream>
//#include "BinaryTree.hpp"
//using namespace std;
//
//template <class Key,
//        class Compare = std::less<_Key>() >
//class Set{
//private:
//    AvlTree<Key> tree;
//
//public:
//    typedef Key * iterator;
//    Set(){}
//    ~Set(){}
//    void insert(const Key &key){
//        tree.insert(key);
//    }
//    void insert(iterator begin, iterator end){
//        while (begin!=end){
//            tree.insert(*(begin++));
//        }
//    }
//
//    iterator begin(){return tree.findMin();}
//    iterator end(){return tree.findMax();}
//    void erase(const Key &key)
//    {
//        tree.remove(key);
//    }
//
//
//
//};
//
//void set_test(){
//    set<int> s;
//    int a[] = {2,1,4,3,5};
//    s.insert(a,a+5);
//    for(auto i: s)
//        cout<<i<<" ";
//    s.erase(10);
//    s.erase(2);
//    cout<<(s.find(1)!= s.end())<<endl;
//    cout<<(s.find(2)!= s.end())<<endl;
//}
//#endif //PROJECT_SET_HPP
