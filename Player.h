#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

//include food.h

class Player
{
    // Construct the remaining declaration from the project manual.

    // Only some sample members are included here

    // You will include more data members and member functions to complete your design.

    
    public:
        //Directions
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  

        Player(GameMechs* thisGMRef);
        ~Player();

        objPosArrayList* getPlayerPos() const;      
        
        void updatePlayerDir();

        void movePlayer(Food *newSnakesFood);

        Dir getFSMState(); 

        bool checkFoodConsumption (Food* snakesFood);

        void increasePlayerLength(); 
        
        bool checkSelfCollision(); 


    private:
        objPosArrayList playerPosList;      
        Dir myDir;

        // Need a reference to the Main Game Mechanisms
        GameMechs* mainGameMechsRef;
};

#endif