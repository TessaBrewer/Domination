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

int main(void)
{
    struct gameState* myGameState = initGameState();

    printGameState(myGameState);

    freeGameState(myGameState);

    return 0;
}