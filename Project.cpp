#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include <time.h>
#include "Food.h"


using namespace std;

#define DELAY_CONST 120000 // speed of the game



void Initialize(void);
void GetInput(void);
int RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



bool exitFlag;
GameMechs* gameMechInstance = new GameMechs(20,10); // setting game board to 20x10

Food* snakesFood = nullptr;

Player* snakeHead = new Player(gameMechInstance);


int main(void)
{

    Initialize();

    while(gameMechInstance->getExitFlagStatus() == false && gameMechInstance->getLoseFlagStatus() == false)  
    {
        GetInput();

        if (RunLogic() != 1)
            ;
        
        DrawScreen();
        
        
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    snakesFood = new Food (); 
    snakesFood->generateFood(snakeHead->getPlayerPos()); //places the initial food on the board
    exitFlag = false;
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
    gameMechInstance->setInput(MacUILib_getChar()); // update game mechanics with input

    }

   
}

int RunLogic(void)
{
    if (gameMechInstance->getInput()== 27)
    {  
        gameMechInstance->setExitTrue();     // if escape key is pressed set exit flag to true
    }

    snakeHead->updatePlayerDir();    

    if (1 == snakeHead->movePlayer(snakesFood))
    {
        MacUILib_clearScreen();         // clear the screen when food is eaten
        return 1;
    }
    
    
    gameMechInstance->clearInput();  
        return 0;
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    objPosArrayList* myCharacter = snakeHead->getPlayerPos();    // obtaining player position

    // drawing the game board
    string gameBoard[10]=

    {
        "####################",  
        "#                  #",   
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "#                  #",
        "####################"  
    };

    // render the game board, snake and food
    for (int i =0; i<gameMechInstance->getBoardSizeY();i++)
    {
        for (int j=0; j<gameMechInstance->getBoardSizeX(); j++)
        {
            int printed =0; 

            for (int  k = 0; k<myCharacter->getSize(); k++)   // loop through all positions occupied by the snake
            {
                objPos snake = myCharacter->getElement(k);

                //print character if char position is met
                if (snake.pos->x== j && snake.pos->y == i)
                {
                    MacUILib_printf("%c", snake.getSymbol());
                    printed = 1; 
                }
            }
            
            if (printed!=1)
            {
                for (int foodIndex =0; foodIndex < snakesFood->bucketSize(); foodIndex++)
                {

                    objPos foodGeneration = snakesFood->getFromBucket(foodIndex);

                    if(foodGeneration.pos->x == j && foodGeneration.pos->y == i)
                    {   
                        printed =1; 
                        MacUILib_printf("%c", foodGeneration.getSymbol());
                        break; 
                    }
                }
            }

            if (printed!=1)
            {
                MacUILib_printf("%c", gameBoard[i][j]);
                 
            }
            
            
            
        
        
    }
    MacUILib_printf("\n");


    

  }

    // game info and instructrions displayed
   
    MacUILib_printf("\nScore: %d\n", gameMechInstance->getScore());
    MacUILib_printf("A adds 2 to score\n");
    MacUILib_printf("a adds 3 to snake length\n");

    MacUILib_printf("Pressed Key: %c\n", gameMechInstance->getPrevInput());
    MacUILib_printf("Current state of FSM: %d\n",snakeHead->getFSMState());

    MacUILib_printf("\nInstructions:\n");
    MacUILib_printf("W - Move Up\n");
    MacUILib_printf("A - Move Left\n");
    MacUILib_printf("S - Move Down\n");
    MacUILib_printf("D - Move Right\n");
    MacUILib_printf("ESC - Exit Game\n");
      
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // using delay from above
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
    if(gameMechInstance->getLoseFlagStatus() == true ){     // if user loses

        MacUILib_printf ("Good Game! Please try again.");   
        MacUILib_printf("\nFinal Score: %d\n", gameMechInstance->getScore()); 
    }
    else {    // if something else happens (ie user exits game using escape command)
        MacUILib_printf("Leaving so soon? Please try again!");
        MacUILib_printf("\nFinal Score: %d\n", gameMechInstance->getScore());
    }

    delete gameMechInstance;
    delete snakeHead;
    delete snakesFood;

    MacUILib_uninit();
}
