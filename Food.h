#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"            
#include "objPosArrayList.h"   


 //The Food class handles the generation of food positions and symbols in a game.
 //It ensures that food is placed in valid positions (not overlapping with blocked positions or duplicates).
 

class Food
{
    private: 
        objPos foodPos;                       // Holds the position and symbol of the current food.
        objPosArrayList* foodBucket;           // Pointer to a list of food objects, storing all generated food positions.

    public:

        void generateFood(objPosArrayList* blockOff);


        objPos getFoodPos() const;


        bool inBucketCheck();
        Food(); //Default Constructor

        Food(Food const &f); //Copy constructor



        Food& operator=(Food const &f); // Copy Assignment Operator

        ~Food();


        int bucketSize();


        objPos getFromBucket(int index);

        bool snakeBodyCheck(objPosArrayList* blockOff, int x, int y); //checks if given position overlaps with any blocked position 
};

#endif
