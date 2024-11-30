#include "Player.h"
#include "iostream"


Player::Player(GameMechs* thisGMRef)
{
    playerPosList = new objPosArrayList();    // list to track player positions
    mainGameMechsRef = thisGMRef;
    myDir = STOP;                             // start with no movement
    playerPosList->insertHead(objPos(10,5,'*'));    // set initial player position
    backLogCheck = 0;


  
}


Player::~Player()
{
    // delete any heap members here
    //delete playerPosList;
    if(playerPosList != nullptr)
     {
        delete playerPosList;
        playerPosList = nullptr;
     }
}

objPosArrayList* Player::getPlayerPos() const
{
    // return the reference to the playerPos arrray list
    return playerPosList;
}

void Player::updatePlayerDir()
{
        // PPA3 input processing logic  

        char input = mainGameMechsRef->getInput();
        
        if ((input == 'w' || input == 'W') && myDir != DOWN) // move up unless currently moving down
        {
            myDir = UP;
        }
        
        else if ((input == 's' || input == 'S') && myDir != UP)  // move down unless currently moving up
        {
            myDir = DOWN;
        }
        
        else if ((input == 'a' || input == 'A') && myDir != RIGHT)  // move left unless currently moving right
        {
            myDir = LEFT;

        }
        
        else if ((input == 'd' || input == 'D') && myDir != LEFT)   // move right unless currently moving left
        {
            myDir = RIGHT;
        }


}

int Player::movePlayer(Food *snakesFood)
{
  

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

    
    if (checkSelfCollision()) // check for collisoins with self and trigger lose condition
    {
        mainGameMechsRef->setLoseFlag();
        return 1; 
    }

    // check if food has been eaten, generate new food, and update the score based on it 
    if (checkFoodConsumption(snakesFood) == 1)   
    {
        backLogCheck = 1;
        snakesFood->generateFood(playerPosList);
        mainGameMechsRef->setScore(mainGameMechsRef->incrementScore(3));
    }

    if (checkFoodConsumption(snakesFood) == 2)
    {
        backLogCheck = 3;
        snakesFood->generateFood(playerPosList);
        mainGameMechsRef->setScore(mainGameMechsRef->incrementScore(1));
    }
    if (checkFoodConsumption(snakesFood) == -1)
    {
        backLogCheck = 1;

        snakesFood->generateFood(playerPosList);
        mainGameMechsRef->setScore(mainGameMechsRef->incrementScore(1));
    }

    if (backLogCheck > 0)  // insert the new head psoiton and delay tail removal for growth if needed
    {
        backLogCheck--;
        playerPosList->insertHead(nextHead);

    }

    else
    {
        playerPosList->insertHead(nextHead); 
        playerPosList->removeTail();
    }

    return 0;
    

    
}

// More methods to be added

Player::Dir Player::getFSMState()
{
    return myDir; 
}


int Player::checkFoodConsumption(Food* snakesFood)
{
    for (int i =0; i < snakesFood->bucketSize(); i++)
    {
        objPos currentFood = snakesFood->getFromBucket(i);

        if (playerPosList->getHeadElement().pos->x == currentFood.pos->x  && playerPosList->getHeadElement().pos->y == currentFood.pos->y)
        {
        if (currentFood.symbol == 'A') // if the food eaten is 'A' then you get 3 extra points
            {
                return 1; 
            }
            else if(currentFood.symbol == 'a') // if the food eaten is 'a' then body frows by 3
            {
                return 2;
            }
            else
            {
                return -1; 
            }
        }
    }
    return 0;

}

void Player::increasePlayerLength()  // increased the length of the snake
{
    objPos newTail = playerPosList->getTailElement();

    playerPosList->insertTail(objPos(newTail.pos->x,newTail.pos->y,'*')); // adds a new segment to the tail

}

bool Player::checkSelfCollision() // checks for self collision by head with any other part of the body of the snake
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

