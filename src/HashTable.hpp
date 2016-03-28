#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

template<typename KEY, typename VALUE>
struct HashNode
{
    KEY key;
    VALUE val;
    HashNode<KEY,VALUE> *next;
    HashNode<KEY,VALUE>(const KEY k=KEY(), const VALUE  v=VALUE(), HashNode<KEY,VALUE> *_next=NULL):key(k),val(v),next(_next){
        cout<<"enter hasnode\n";
    }
    HashNode<KEY,VALUE> & operator=(const HashNode<KEY,VALUE> &rhs){
        this->key = rhs.key;
        this->val = rhs.val;
        next = rhs->next;
        return *this;
    }
};
template<typename KEY, typename VALUE>
class HashTable
{
private:
    vector< HashNode<KEY,VALUE> * > table;
public:
    HashTable()
    {
        table.resize(10);
        for (auto i : table) {
            i = NULL;
        }
    }
    bool insert(const HashNode<KEY,VALUE> &node)
    {
        size_t hash_code = node.key.hash();
        cout<<"hash code "<<hash_code<<endl;
        if(table.size()<hash_code || table[hash_code] == NULL)
        {
            cout<<"insert NULL\n";
            table[hash_code] = new HashNode<KEY,VALUE>(node.key, node.val);
        }
        else
        {
            cout<<"insert not NULL\n";
            HashNode<KEY,VALUE> *old_node = table[hash_code];
            table[hash_code] = new HashNode<KEY,VALUE>(node.key, node.val, old_node);
        }
    }

    VALUE  operator[] (const KEY &key)
    {
        size_t hash_code = key.hash();
        HashNode<KEY,VALUE> *node = table[hash_code];
        if(node)
        {
            while(node)
            {
                if (node->key == key)
                    return node->val;
                node = node->next;
            }
        }
        return VALUE();
    }
};

struct HashObj
{
    string s1;
    HashObj(string s=NULL):s1(s){}
    bool operator==(const HashObj &obj) const
    {
        return s1 == obj.s1;
    }

    friend ostream & operator<<(ostream &os, const HashObj &obj)
    {
        os<<obj.s1;
        return os;
    }

    size_t hash() const
    {
        return (s1.length()+s1[0])/131;
    }
};

namespace std
{
    template<>
    struct hash<HashObj>
    {
        std::size_t operator()(const HashObj &) const
        {
            return 1;
        }
    };
}
void unordered_map_test()
{
    unordered_map<HashObj, string> um( { {HashObj("aa"),"1"}, {HashObj("bb"),"2"}});
    um[HashObj("cc")] = "1";
    um[HashObj("dd")] = "2";
    um[HashObj("ee")] = "5";
    um[HashObj("ff")] = "6";

    for (auto var : um) {
        cout<<var.first<<" "<<var.second<<endl;
    }

    cout<<um[HashObj("df")]<<endl;
    //um.rehash(20);
    cout<<um.size()<<" "<<um.bucket_count()<<endl;
}

void HashTable_test()
{
    HashTable<HashObj, int> ht;
    ht.insert(HashNode<HashObj,int>(HashObj("one"),1));
    ht.insert(HashNode<HashObj,int>(HashObj("two"),2));
    cout<<ht[HashObj("one")]<<" "<<ht[HashObj("two")]<<endl;
    try
    {
        vector<int> vi;
        vi.resize(10);
        cout<<vi[1]<<endl;
    }
    catch(std::exception &e)
    {
        cout<<e.what()<<endl;
    }
}
#endif
