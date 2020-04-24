//
// Created by Deven Brewer #19201772 on 27/03/2020.
//

//Gives us the ability to print error messages
#include <stdio.h>
//Where we've defined all of our structs and enums
#include "Object_Definition.h"
//Where we've defined various functions for analyzing the data structures defined in Object_Definition.h
#include "Game_Logic.h"
//Where we've defined all of the custom logic for our game
#include "Game_Init.h"
//Where we've defined all of our I/O functions
#include "ASCII_IO.h"
//Gives us our unit tests
#include "Unit_Tests.h"

int main(void)
{
    preformTests();

    struct gameState* myGameState = initGameState();

    struct userMove moveObject;

    while(canMove(myGameState))
    {
        //Print Board
        printGameState(myGameState);

        //Get Move
        do {
            getMove(myGameState, &moveObject);
        }while(!validateMove(myGameState, &moveObject));

        //Execute Move
        if(movePieces(myGameState, &moveObject))
            return fprintf(stderr, "Error in movePieces()\n"), 1;

        //Swap Turn
        swapTurn(myGameState);
    }

    //We reach this point when the current player can not move, ie they've lost
    if(myGameState->currentTurn == Red)
    {
        printf("Green Player Wins\n");
    } else
    {
        printf("Red Player Wins\n");
    }

    freeGameState(myGameState);

    return 0;
}