//
// Created by Deven Brewer #19201772 on 30/03/2020.
//

#ifndef DOMINATION_ASCII_IO_H
#define DOMINATION_ASCII_IO_H

#include "Object_Definition.h"

#include <stdio.h>

//We'll use this function to print out the current gameState to stdout
void printGameState(struct gameState* currentGameState);

void printSquare(struct square* input);

//We'll use this to get user input, we return the selected origin and destination of a move, unless the user chooses an option which does not terminate their turn, in which case we'll call the appropriate functions from Game_Logic and prompt the user again
    //We DO NOT validate the moves with in this function, the user can select ANY square object for their origination and destination
void getMove(struct gameState* currentGameState, struct userMove* output);

#endif //DOMINATION_ASCII_IO_H
