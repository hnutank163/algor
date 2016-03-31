#ifndef _HASH_TABLE_H
#define _HASH_TABLE_H

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <unordered_map>
#include <vector>
#include <list>

using namespace std;
struct myhash;

template<class Key,
        class T,
        class Hash=std::hash<Key>,
        class KeyEqual = std::equal_to<Key> >
class HashTable {

public:
    typedef std::pair<Key, T> value_type;
    typedef value_type *iterator;
    typedef Key key_type;
    typedef Hash hash_func;
    typedef KeyEqual equal_func;

private:
    size_t size_;
    size_t capacity_;
    key_type empty_key;
    value_type *buckets_;

private:
    void init_bucket() {
        delete[]buckets_;
        buckets_ = new value_type[capacity_]();
    }

    value_type *_insert(const value_type &v) {
        const key_type &key = v.first;

    }

    void find(const key_type &key) {
        size_t hash_index = hash_func(key);

    }

public:
    HashTable(size_t capacity = 32) : size_(0), capacity_(capacity), empty_key(key_type()), buckets_(nullptr) {
        init_bucket();
    }

    HashTable &operator=(const HashTable &ht) {
        size_ = ht.size_;
        capacity_ = ht.capacity_;
        init_bucket();

        return *this;
    }
};

template<class Key,
        class T,
        class Hash=std::hash<Key>,
        class equal=std::equal_to<Key> >
class HashMap {
private:
    typedef T map_type;
    typedef Key key_type;
    typedef std::pair<Key, T> value_type;
    typedef value_type *iterator;
    typedef Hash hash_fn;
    typedef equal equal_fn;
private:
    vector<list<value_type> > table;
    size_t size_;
    size_t bucket_count;
    hash_fn hash_func;
    equal_fn equal_func;
public:
    HashMap() : size_(0), bucket_count(32), hash_func(), equal_func() {
        table.resize(32);
    }

    void rehash() {
        bucket_count *= 2;
        vector<list<value_type> > old_table = table;
        table.resize(bucket_count);
        for (int i = 0; i < bucket_count; ++i) {
            table[i].assign(old_table[i].begin(), old_table[i].end());
        }
    }

    value_type insert(const value_type &val) {
        size_t hash_code = hash_func(val.first) % bucket_count;
        if (hash_code > bucket_count)
            rehash();
        ++size_;
        table[hash_code].push_front(std::make_pair(val.first, val.second));
    }

    map_type &operator[](const key_type &key) {
        size_t hash_code = hash_func(key) % bucket_count;
        for (auto l: table[hash_code]) {
            if (l.first == key)
                return l.second;
        }
        table[hash_code].push_front(std::make_pair(key, map_type()));
        return table[hash_code].begin()->second;
    }

    map_type &operator[](const key_type &key) const {
        size_t hash_code = hash_func(key) % bucket_count;
        for (auto l: table[hash_code]) {
            if (l.first == key)
                return l.second;
        }
        table[hash_code].push_front(std::make_pair(key, map_type()));
        return table[hash_code].begin()->first;
    }

    friend ostream &operator<<(ostream &os, const HashMap &hm) {
        for (auto l: hm.table) {
            os << "[";
            for (auto p: l) {
                os << p.first << " : " << p.second << " ";
            }
            os << "]\n";
        }
        return os;
    }
};

struct HashObj {
    string s1;

    HashObj(string s = NULL) : s1(s) { }

    bool operator==(const HashObj &obj) const {
        return s1 == obj.s1;
    }

    friend ostream &operator<<(ostream &os, const HashObj &obj) {
        os << obj.s1;
        return os;
    }

    size_t hash() const {
        return (s1.length() + s1[0]) / 131;
    }


};

namespace std {
    template<>
    struct hash<HashObj> {
        std::size_t operator()(const HashObj &) const {
            return 1;
        }
    };
}

void unordered_map_test();

void unordered_map_test() {
    unordered_map<HashObj, string> um({{HashObj("aa"), "1"},
                                       {HashObj("bb"), "2"}});

    unordered_map<HashObj, string>::iterator iter = um.begin();
    for (int i = 0; i < um.size(); ++i) {
        cout << (*iter).first << " : " << (*iter).second << endl;
        ++iter;
    }
    for (auto var : um) {
        cout << var.first << " " << var.second << endl;
    }

    //um.rehash(20);
    cout << um.size() << " " << um.bucket_count() << endl;
}

struct myhash {
    size_t operator()(const string &x) const {
        std::hash<string>()(x);
        /* your code here, e.g. "return hash<int>()(x.value);" */
    }
};

void HashTable_test() {
    HashMap<string, int, myhash> hm;
    hm["one"] = 1;
    hm["two"] = 2;
    hm["three"] = 3;
    hm.insert(make_pair("five", 5));
    cout << hm;
    cout << std::hash<string>()("google") << endl;
}


#endif
