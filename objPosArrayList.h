#ifndef OBJPOS_ARRAYLIST_H
#define OBJPOS_ARRAYLIST_H

#define ARRAY_MAX_CAP 200

#include "objPos.h"

class objPosArrayList
{
    private:
        objPos* aList;
        int listSize;
        int arrayCapacity;

    public:
        objPosArrayList();
        objPosArrayList(int bucketSize);
        ~objPosArrayList();
        objPosArrayList(objPosArrayList const &arr);    //Copy constructor
        objPosArrayList& operator=(objPosArrayList const &arr);     //Copy assignment operator 


        int getSize() const;
        void insertHead(objPos thisPos);
        void insertTail(objPos thisPos);
        void removeHead();
        void removeTail();
        
        objPos getHeadElement() const;
        objPos getTailElement() const;
        objPos getElement(int index) const;
        void insertElement (int index, objPos food) const;
};

#endif