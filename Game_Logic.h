//
// Created by Deven Brewer #19201772 on 30/03/2020.
//

#ifndef DOMINATION_GAME_LOGIC_H
#define DOMINATION_GAME_LOGIC_H

#include "Object_Definition.h"

enum colour getTopPieceColour(struct square* mySquare);

//Validates a move, including checking if it's in range, if the current user is allowed to move it, and if they selected a valid number of pieces, etc
    //Returns 1 if valid, 0 if not
int validateMove(struct gameState* currentGameState, struct userMove* target);

//This function will preform the actual move inputted by the user
    //Moves should always be validated before they are used, this function's behavior is undefined for invalid moves
int movePieces(struct gameState* currentGameState, struct userMove* move);

#endif //DOMINATION_GAME_LOGIC_H
