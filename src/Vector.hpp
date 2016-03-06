#include <iostream>
#include <algorithm>
using namespace std;


template<typename Object>
class Vector
{
public:
    explicit Vector (int size=0):theSize(size),theCapacity(theSize+SPARE_CAPACITY)
    {
        this->objects = new Object[theCapacity];
    }

    virtual ~Vector ()
    {
        delete [] objects;
    }

    Vector & operator=(const Vector &rhs)
    {
        if( this != &rhs )
        {
            delete [] objects;
            theSize = rhs.size;
            theCapacity = rhs.theCapacity;
            objects = new Object[theCapacity];
            for(int i=0; i<theSize; ++i)
                objects[i]  = rhs.objects[i];
        }

        return *this;
    }

    Vector( const Vector & rhs ):objects(NULL)
    {
        this->operator=(rhs) ;
    }

    void reserve(int newCapacity)
    {
        if( newCapacity < theCapacity )
            return;

        Object *old = objects;
        objects = new Object[newCapacity];
        for(int i=0; i<theSize; ++i)
            objects[i] = old[i];
        theCapacity = newCapacity;
        delete [] old;
    }

    void resize(int newSize)
    {
        if(newSize > theCapacity) 
            reserve(newSize*2 + SPARE_CAPACITY);

        theSize = newSize;
    }

    Object & operator[] (int index)
    {
        return objects[index];
    }

    const Object & operator[] (int index) const
    {
        return objects[index];
    }

    bool empty() const{return theSize == 0;}

    void push_back(const Object &obj)
    {
        if( theSize == theCapacity )
            resize(2*theCapacity + 1);

        objects[theSize++] = obj;
    }

    void pop_back()
    {
        theSize -- ;
    }

    const Object & back() const 
    {
        return objects[theSize-1];
    }

    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin( ){return &objects[0];}
    const_iterator begin() const { return & objects[0]; }
    iterator end() {return &objects[theSize];}
    const_iterator end() const { return & objects[theSize] ;}

private:
    enum{SPARE_CAPACITY=128};
    int theSize;
    int theCapacity;
    
   Object *objects;
};
