#include "objPosArrayList.h"
#include <iostream>

using namespace std;


objPosArrayList::objPosArrayList()//Constructor
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = 0;
    aList = new objPos[ARRAY_MAX_CAP];  //allocate array of objPos

}

objPosArrayList::objPosArrayList(int bucketSize)      //Constructor
{
    arrayCapacity = ARRAY_MAX_CAP;
    listSize = bucketSize;
    aList = new objPos[ARRAY_MAX_CAP];  // allocate the array

}

objPosArrayList::~objPosArrayList()  //Destructor 
{
    delete[] aList;
    
}

objPosArrayList::objPosArrayList(objPosArrayList const &arr)    //Copy constructor
{
    listSize = arr.listSize;
    arrayCapacity = arr.arrayCapacity;
    aList = new objPos[ARRAY_MAX_CAP];  // allocate memory for copy

    for (int i = 0; i < listSize - 1; i++)
    {
        aList[i] = arr.aList[i]; // copy elements
    }
}

objPosArrayList& objPosArrayList::operator =(objPosArrayList const &arr)
{
    if (this != &arr)
    {
       
        this->listSize = arr.listSize;
        this->arrayCapacity = arr.arrayCapacity;

        for (int i = 0; i < listSize - 1; i++)
        {
            this->aList[i] = arr.aList[i]; //copy elements
        }
    }

    return *this;
}

int objPosArrayList::getSize() const
{
    return listSize;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    if (listSize == arrayCapacity)  // checking if the list is full
    {
        cout << "The array is full" << endl;
    }

    for (int i = listSize; i > 0; i--) //shift all elements to the right by 1
    {
        aList[i] = aList[i-1];
    }

    aList[0] = thisPos; //insert the new element at the head
    listSize++; 
}

void objPosArrayList::insertTail(objPos thisPos)
{
    if (listSize == arrayCapacity) //check if array is full
    {
        cout << "The array is full" << endl;
    }

    aList[listSize] = thisPos; //insert new element at tail
    listSize++;
}

void objPosArrayList::removeHead() 
{
   if (listSize != arrayCapacity)
   {
        for(int i = 0; i < listSize - 1; i++)
        {
            aList[i] = aList[i + 1];
        }
        listSize--;
   }
   
   else

   {    
        cout << "No head to remove" << endl;
   }
}  

void objPosArrayList::removeTail()
{
    if (listSize != 0)
    {
       listSize--;
    }

    else
    {    
        cout << "No tail to remove" << endl;
    }
}

objPos objPosArrayList::getHeadElement() const
{
    return aList[0];
}

objPos objPosArrayList::getTailElement() const
{
    return aList[listSize - 1];
}

objPos objPosArrayList::getElement(int index) const
{
    if (index >= 0 && index < listSize) 
    {
        return aList[index];
    }

    else
    {
        cout << "Index Out of Bounds" << endl;
        return objPos(); 
    }
}

void objPosArrayList::insertElement(int index, objPos food) const
{
    if(index >= 0 && index < listSize)
    {
       aList[index] = food ; 
    }

    else
    {
        cout << "Index out of Bounds" << endl;
    }
}