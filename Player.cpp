#include "Player.h"
#include "iostream"


Player::Player(GameMechs* thisGMRef)
{
    playerPosList = new objPosArrayList();
    mainGameMechsRef = thisGMRef;
    myDir = STOP;
    playerPosList -> insertHead(objPos(11,5,'*'));

    // more actions to be included
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPos Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic  

        char input = mainGameMechsRef->getInput();
        
        if ((input == 'w' || input == 'W') && myDir != DOWN) 
        {
            myDir = UP;
        }
        
        else if ((input == 's' || input == 'S') && myDir != UP) 
        {
            myDir = DOWN;
        }
        
        else if ((input == 'a' || input == 'A') && myDir != RIGHT) 
        {
            myDir = LEFT;

        }
        
        else if ((input == 'd' || input == 'D') && myDir != LEFT) 
        {
            myDir = RIGHT;
        }


}

void Player::movePlayer()
{
    // PPA3 Finite State Machine logic

    objPos nextHead = playerPosList->getHeadElement(); 

        
    switch (myDir) {
        
    case DOWN:  // current direction down then move character down by 1
        nextHead.pos->y++;
           
           // if the y position reaches upper bound, wrap around
            if (nextHead.pos->y == mainGameMechsRef->getBoardSizeY()- 1 )
            {
                nextHead.pos->y = 1;
            }
            break;

    case UP:  // current direction up then move character up 1
        nextHead.pos->y--;

            // if y position reaches lower bound wrap around
            if (nextHead.pos->y == 0) 
            {
                nextHead.pos->y = mainGameMechsRef->getBoardSizeY()-2;
            }
            break;

    case RIGHT: // current direction right, move right by 1
        nextHead.pos->x++;

            // x position goes out of bounds to the right, wrap around
            if (nextHead.pos->x == mainGameMechsRef->getBoardSizeX()-1)
            {
                nextHead.pos->x = 1;
            }
            break;

    case LEFT: // if current direction is left, move left by 1
        nextHead.pos->x--;

            // x position goes out of bounds to the left, wrap around
            if (nextHead.pos->x== 0)
            {
                nextHead.pos->x = mainGameMechsRef->getBoardSizeX()-2;
            }
            break;

    case STOP:
        
        break; 
    
    }

    
    if (checkSelfCollision())
    {
        mainGameMechsRef->setLoseFlag();
        return; 
    }
        
    if (checkFoodConsumption(snakeFood))
    {
        increasePlayerLength();
        snakeFood->generateFood(playerPosList);
    }

    playerPosList->insertHead(nextHead); 
    playerPosList->removeTail();

    
}



// More methods to be added

Player::Dir Player::getFSMState()
{
    return myDir; 
}

bool Player::checkFoodConsumption(Food *snakesFood)
{
    for (int i =0; i < snakesFood->bucketSize(); i++)
    {
        objPos currentFood = snakesFood->getFromBucket(i);

        if (playerPosList->getHeadElement().pos->x == currentFood.pos->x  && playerPosList->getHeadElement().pos->y == currentFood.pos->y)
        {
            return true; 
        }
    }
    return false;

}

void Player::increasePlayerLength()
{
    objPos newTail = playerPosList->getTailElement();

    playerPosList->insertTail(objPos(newTail.pos->x,newTail.pos->y,'@')); 

    mainGameMechsRef->setScore(playerPosList->getSize()-1); 
}

bool Player::checkSelfCollision()
{
    objPos playerHead = playerPosList->getHeadElement();

    for (int i =1; i < playerPosList->getSize(); i++)
    {
        objPos currentBodyPart = playerPosList->getElement(i);
        if (playerHead.pos->x == currentBodyPart.pos->x && playerHead.pos->y==currentBodyPart.pos->y)
        {
            return true; 
        }
    }

    return false; 
}

