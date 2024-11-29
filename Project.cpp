#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "Player.h"
#include "GameMechs.h"
#include <time.h>
#include "Food.h"


using namespace std;

#define DELAY_CONST 120000

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

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

GameMechs* gameMechInstance = new GameMechs(20,10);

Player* snakeHead = new Player(gameMechInstance);

Food* snakesFood = nullptr;
Food* newSnakesFood = nullptr;

int wipeFood;


int main(void)
{

    Initialize();

    while(gameMechInstance->getExitFlagStatus() == false && gameMechInstance->getLoseFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
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
    snakesFood->generateFood(snakeHead->getPlayerPos());
    exitFlag = false;
}

void GetInput(void)
{
    if (MacUILib_hasChar())
    {
    gameMechInstance->setInput(MacUILib_getChar());

    }

   
}

void RunLogic(void)
{
    if (gameMechInstance->getInput()== 27){
        gameMechInstance->setExitTrue();
    }
    snakeHead->updatePlayerDir();
    snakeHead->movePlayer(snakesFood);

    gameMechInstance->clearInput();  
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();  

    objPosArrayList* myCharacter = snakeHead->getPlayerPos();

    for (int i =0; i<gameMechInstance->getBoardSizeY();i++){
        for (int j=0; j<gameMechInstance->getBoardSizeX(); j++){
            int printed =0; 

            for (int  k = 0; k<myCharacter->getSize(); k++){
            objPos snake = myCharacter->getElement(k);
            //if the character position is met in the gameboard, print character
            if (snake.pos->x== j && snake.pos->y == i){
                MacUILib_printf("%c", snake.getSymbol());
                printed = 1; 
            }
            }
             if (printed!=1){
                for (int foodIndex =0; foodIndex < snakesFood->bucketSize(); foodIndex++){

                    objPos foodGeneration = snakesFood->getFromBucket(foodIndex);

                    if(foodGeneration.pos->x == j && foodGeneration.pos->y == i)
                    {   printed =1; 
                        MacUILib_printf("%c", foodGeneration.getSymbol());
                        break; 
                    }
                }
            }

            if (printed!=1){
                MacUILib_printf("%c", gameBoard[i][j]);
                 
            }
            
            
            
        
        
    }
    MacUILib_printf("\n");


    

  }


   
    MacUILib_printf("Score: %d\n", gameMechInstance->getScore());
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
    // delete gameMechInstance;
    // delete snakeHead;
    // delete snakesFood;



    MacUILib_clearScreen();    
    if(gameMechInstance->getLoseFlagStatus() == true ){

        MacUILib_printf ("Tough Luck, try again!"); 
    }
    else {
        MacUILib_printf("Bye, buddy"); 
    }

    delete gameMechInstance;
    delete snakeHead;
    delete snakesFood;

    MacUILib_uninit();
}
