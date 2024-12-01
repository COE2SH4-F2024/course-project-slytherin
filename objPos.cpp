#include "objPos.h"

// Default constructor, initializes position to (0, 0) and symbol to NULL
objPos::objPos()
{
    pos = new Pos;
    pos->x = 0;
    pos->y = 0;
    symbol = 0; // NULL
}

// Parameterized constructor, initializes position and symbol with given values
objPos::objPos(int xPos, int yPos, char sym)
{
    pos = new Pos;
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Destructor, deletes dynamically allocated memory for position
objPos::~objPos()
{
   delete pos;
//     if(pos != nullptr)
//      {
//         delete pos;
//         pos = nullptr;
//      }
 }

// Copy constructor, creates a deep copy of another objPos object
objPos::objPos(const objPos &a)
{
    pos = new Pos;
    pos->x = a.pos->x;
    pos->y = a.pos->y;
    symbol = a.symbol;
}

// Copy assignment operator, assigns one objPos object to another
objPos& objPos::operator=(const objPos &a)
{
    if (this != &a) // Avoid self-assignment
    {
        // free existing 
        delete pos;

        //Allocate new memory and yRange values
        this->pos = new Pos;
        this->pos->x = a.pos->x;
        this->pos->y = a.pos->y;
        this->symbol = a.symbol;
    }
    return *this;
}

// Sets position and symbol from another objPos object
void objPos::setObjPos(objPos o)
{
    pos->x = o.pos->x;
    pos->y = o.pos->y;
    symbol = o.symbol;
}

// Sets position and symbol with given values
void objPos::setObjPos(int xPos, int yPos, char sym)
{
    pos->x = xPos;
    pos->y = yPos;
    symbol = sym;
}

// Returns a copy of the current objPos object
objPos objPos::getObjPos() const
{
    objPos returnPos;
    returnPos.pos->x = pos->x;
    returnPos.pos->y = pos->y;
    returnPos.symbol = symbol;
    return returnPos;
}

// Returns the symbol of the object
char objPos::getSymbol() const
{
    return symbol;
}

// Checks if the position matches the given objPos reference
bool objPos::isPosEqual(const objPos* refPos) const
{
    return (refPos->pos->x == pos->x && refPos->pos->y == pos->y);
}

// Returns the symbol if the position matches the given objPos reference, otherwise returns NULL
char objPos::getSymbolIfPosEqual(const objPos* refPos) const
{
    if (isPosEqual(refPos))
        return symbol;
    else
        return 0; // NULL
}
