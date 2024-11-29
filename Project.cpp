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

GameMechs* instance = new GameMechs(20,10);

Player* snakeHead = new Player(instance);

Food* snakesFood = nullptr;
Food* newSnakesFood = nullptr;



int main(void)
{

    Initialize();

    while(exitFlag == false)  
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

    exitFlag = false;
}

void GetInput(void)
{
   
}

void RunLogic(void)
{
    
}

void DrawScreen(void)
{
    MacUILib_clearScreen();    
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // using delay from above
}


void CleanUp(void)
{
    MacUILib_clearScreen();    

    MacUILib_uninit();
}
