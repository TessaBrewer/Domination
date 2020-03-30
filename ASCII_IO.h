//
// Created by Deven Brewer #19201772 on 30/03/2020.
//

#ifndef DOMINATION_ASCII_IO_H
#define DOMINATION_ASCII_IO_H

#include "Object_Definition.h"

#include <stdio.h>

//We'll use this function to print out the current gameState to stdout
void printGameState(struct gameState* currentGameState);

//We'll use this to get user input, ideally we'll call this twice per turn
void promptUser(struct point* returnValue);

#endif //DOMINATION_ASCII_IO_H
