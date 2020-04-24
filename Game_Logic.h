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
    //Returns 1 if an error is encountered, 0 if successful
int movePieces(struct gameState* currentGameState, struct userMove* move);

//Swaps who's turn it is (if it's currently green's turn then it becomes red's and vice versa
void swapTurn(struct gameState* currentGameState);

//Returns 1 if the current player can make a move, 0 if not
    //If a player can not move then they lose
int canMove(struct gameState* currentGameState);

#endif //DOMINATION_GAME_LOGIC_H
