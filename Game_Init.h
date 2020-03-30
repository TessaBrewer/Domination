//
// Created by Deven Brewer #19201772 on 27/03/2020.
//

#ifndef DOMINATION_GAMEINIT_H
#define DOMINATION_GAMEINIT_H

#include "Object_Definition.h"

//Initializes a piece object (including memory allocation) and assignment of default values, returns NULL if this fails
struct piece* initPiece(enum colour pieceColour);
//Frees any memory allocated in initPiece()
void freePiece(struct piece* pieceInstance);

//Initializes a square and the piece that begins on top of it (if isValid == valid && initPieceColour != None), including memory allocation and default values, returns NULL if this fails
struct square* initSquare(enum squareType isValid, enum colour initPieceColour);
//Frees memory allocated for a square object and ALL pieces stacked on top of this square
void freeSquare(struct square* squareInstance);

//Initializes a player object (including allocating memory) and assigning correct default values, returns NULL if this fails
struct player* initPlayer(enum colour playerColour);
//Frees any memory allocated in initPlayer()
void freePlayer(struct player* playerInstance);

//Initializes a gameState object, including memory allocation and default values, returns NULL if this fails
struct gameState* initGameState();
//Frees a gameState object, including all allocated memory
void freeGameState(struct gameState* gameStateInstance);

#endif //DOMINATION_GAMEINIT_H
