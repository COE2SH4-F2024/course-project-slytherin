#include "Food.h"
#include <iostream>
#include <time.h>
using namespace std;

// Generates food items while avoiding conflicts with obstacles or duplicates
void Food::generateFood(objPosArrayList* blockOff)
{
    int numItemsGen = 0; // Counter for generated food items
    int i, j, unique, RandNum_x, RandNum_y, yRange = 10, xRange = 20; // Variables for random generation
    char RandSymbol; // Random symbol for food
    bool existingInBucket = false; // Tracks if food is already in bucket
    srand(time(NULL)); // Seed random number generator

    while (numItemsGen != 5) { // Generate 5 unique food items
        do {
            unique = 1; // Assume food is unique
            RandNum_x = (rand() % (xRange - 2)) + 1; // Random x position
            RandNum_y = (rand() % (yRange - 2)) + 1; // Random y position
            RandSymbol = (rand() % 93) + 33; // Random ASCII symbol

            foodPos.pos->x = RandNum_x; // Assign x position
            foodPos.pos->y = RandNum_y; // Assign y position
            foodPos.symbol = RandSymbol; // Assign symbol

            if (RandSymbol == ' ' || RandSymbol == '$' || RandSymbol == '*') // Exclude invalid symbols
                unique = 0;

            if (snakeBodyCheck(blockOff, RandNum_x, RandNum_y)) // Check snake body overlap
                unique = 0;

            if (existingInBucket = inBucketCheck()) // Check for duplicates in bucket
                unique = 0;

        } while (unique == 0); // Repeat until unique food is found

        foodBucket->insertElement(numItemsGen, foodPos); 
        numItemsGen++; 
    }

    return; 
}

// Returns the current food position
objPos Food::getFoodPos() const
{
    return foodPos;
}

// Default constructor initializes the food bucket
Food::Food()
{
    foodBucket = new objPosArrayList(5); // Create bucket for 5 items
}

// Copy constructor creates a new Food object from an existing one
Food::Food(Food const &f)
{
    foodPos.pos = new Pos; // Allocate memory for position
    foodPos.pos->x = f.foodPos.pos->x; // Copy x position
    foodPos.pos->y = f.foodPos.pos->y; // Copy y position
    foodPos.symbol = f.foodPos.symbol; // Copy symbol
}

// Copy assignment operator assigns values from another Food object
Food& Food::operator=(Food const &f)
{
    if (this != &f) { // Avoid self-assignment
        this->foodPos.pos = new Pos; 
        this->foodPos.pos->x = f.foodPos.pos->x; 
        this->foodPos.pos->y = f.foodPos.pos->y;
        this->foodPos.symbol = f.foodPos.symbol;
    }
    return *this; 
}

// Checks if the current food position or symbol already exists in bucket
bool Food::inBucketCheck()
{
    for (int i = 0; i < foodBucket->getSize(); i++) {
        objPos currentFood = foodBucket->getElement(i).getObjPos(); // Get food from bucket
        if ((currentFood.pos->x == foodPos.pos->x && currentFood.pos->y == foodPos.pos->y) || currentFood.getSymbol() == foodPos.getSymbol())
            return true; // Return true if duplicate found
    }
    return false; // No duplicates
}

// Checks if the given position overlaps with blocked positions (snake body)
bool Food::snakeBodyCheck(objPosArrayList* blockOff, int x, int y)
{
    bool isCordTaken = false; // Flag for position overlap
    for (int i = 0; i < blockOff->getSize(); i++) {
        isCordTaken = blockOff->getElement(i).pos->x == x && blockOff->getElement(i).pos->y == y; // Check overlap
        if (isCordTaken)
            return isCordTaken; 
    }
    return isCordTaken; 
}

// Returns the size of the food bucket
int Food::bucketSize()
{
    return foodBucket->getSize();
}

// Gets a specific food item from the bucket by index
objPos Food::getFromBucket(int index)
{
    return foodBucket->getElement(index);
}

// Destructor to free allocated memory
Food::~Food()
{
   // delete foodPos.pos; // Free memory for position


}
