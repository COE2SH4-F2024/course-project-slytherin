#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Food;
class GameMechs;


class Player
{
    public:
        // Enum to define movement directions for the player
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};  

        // Constructor to initialize the player with a reference to the game mechanics
        Player(GameMechs* thisGMRef);

        // Destructor 
        ~Player();

        // Returns a pointer to the player's position list
        objPosArrayList* getPlayerPos() const;      
        
        // Updates the player's direction based on input
        void updatePlayerDir();

        // Moves the player based on the current direction and game logic
        int movePlayer(Food* snakesFood);

        // Returns the current direction of the player
        Dir getFSMState(); 

        // Checks if the player has consumed food
        int checkFoodConsumption(Food* snakesFood);

        // Increases the player's length (e.g., when food is consumed)
        void increasePlayerLength(); 

        // Checks if the player has collided with itself
        bool checkSelfCollision(); 

    private:
        // A list to track the positions of the player (e.g., snake body segments)
        objPosArrayList* playerPosList;      

        // The current direction of the player
        Dir myDir;

        int backLogCheck;
        // Reference to the main game mechanics
        GameMechs* mainGameMechsRef;
};

#endif
