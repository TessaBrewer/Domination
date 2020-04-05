//
// Created by Deven Brewer #19201772 on 27/03/2020.
//

#include "Game_Init.h"
//So we can print error messages
#include <stdio.h>
//For memory allocation and freeing
#include <stdlib.h>

//Initializes a piece object (including memory allocation) and assignment of default values, returns NULL if this fails
struct piece* initPiece(enum colour pieceColour)
{
    struct piece* output = (struct piece*) malloc(sizeof(struct piece));
    if(output == NULL)
        return fprintf(stderr, "Error allocating memory in initPiece()\n"), NULL;

    output->pieceColour = pieceColour;
    output->next = NULL;

    return output;
}
//Frees any memory allocated in initPiece()
void freePiece(struct piece* pieceInstance)
{
    free(pieceInstance);
}

//Initializes a square AND the piece that begins on top of it, including memory allocation and default values, returns NULL if this fails
    //It is assumed that this square object is a valid square
struct square* initSquare(enum squareType isValid, enum colour initPieceColour)
{
    //Allocate memory for a square object and handle the potential error
    struct square* output = (struct square*) malloc(sizeof(struct square));
    if(output == NULL)
        return fprintf(stderr, "Error allocating memory in initSquare(enum colour)\n"), NULL;

    output->canHaveStack = isValid;
    if(isValid == valid && initPieceColour != None)
    {
        output->stack = initPiece(initPieceColour);
        if (output->stack == NULL)
            return free(output), fprintf(stderr, "Error declaring initial game piece in initSquare(enum colour)\n"), NULL;
        output->stackHeight = 1;
    }else
    {
        output->stack = NULL;
        output->stackHeight = 0;
    }

    return output;
}
//Frees memory allocated for a square object and ALL pieces stacked on top of this square
void freeSquare(struct square* squareInstance)
{
    //Free the stack of pieces on this square, if it's empty then this code does nothing
    struct piece* currentPieceInStack = squareInstance->stack;
    struct piece* nextPieceInStack;
    while(currentPieceInStack != NULL)
    {
        nextPieceInStack = currentPieceInStack->next;
        freePiece(currentPieceInStack);
        currentPieceInStack = nextPieceInStack;
    }

    free(squareInstance);
}

//Initializes a player object (including allocating memory) and assigning correct default values, returns NULL if this fails
struct player* initPlayer(enum colour playerColour)
{
    //Allocate memory and handle the potential error
    struct player* output = (struct player*) malloc(sizeof(struct player));
    if(output == NULL)
        return fprintf(stderr, "Error allocating memory for player object in initPlayer()\n"), NULL;

    //Initialize all values
    output->playerColour = playerColour;
    output->reserve = initSquare((enum squareType)valid, (enum colour)None);
    if(output->reserve == NULL) //Handle potential error from initSquare()
        return free(output), fprintf(stderr, "Error declaring player reserve stack in initPlayer()\n"), NULL;
    output->capturedPieces = 0;

    //Return a pointer to the memory holding the initialized object
    return output;
}
//Frees any memory allocated in initPlayer()
void freePlayer(struct player* playerInstance)
{
    freeSquare(playerInstance->reserve);
    free(playerInstance);
}

//Frees all memory allocated in initGameState() up to a point (denoted by x & y) in case we run into an error half way through allocating memory for the board
static void abortInitGameState(struct gameState* input, int row, int column)
{
    for(int i = 0; i <= row; i++)
        for(int j = 0; (j < 8 && i != row) || (j <= column && i == row); j++)
            freeSquare(input->board[i][j]);

    freePlayer(input->redPlayer);
    freePlayer(input->greenPlayer);

    free(input);
}
//Initializes a gameState object, including memory allocation and default values, returns NULL if this fails
struct gameState* initGameState()
{
    struct gameState* output = (struct gameState*) malloc(sizeof(struct gameState));
    if(output == NULL)
        return fprintf(stderr, "Error allocating memory for board in initGameState()\n"), NULL;

    //Initialize the player objects
    output->redPlayer = initPlayer((enum colour)Red);
    if(output->redPlayer == NULL)
        return fprintf(stderr, "Error initializing redPlayer in initGameState()\n"), free(output), NULL;
    output->greenPlayer = initPlayer((enum colour)Green);
    if(output->greenPlayer == NULL)
        return fprintf(stderr, "Error initializing greenPlayer in initGameState()\n"), freePlayer(output->redPlayer), free(output), NULL;
    output->currentTurn = (enum colour)Red;

    struct{enum squareType sT; enum colour c;} InitialGameState [8][8]=
            {
                    {{invalid, None}, {invalid, None}, {valid, None},  {valid, None},  {valid, None},  {valid, None},  {invalid, None}, {invalid, None}},
                    {{invalid, None}, {valid, Red},    {valid, Red},   {valid, Green}, {valid, Green}, {valid, Red},   {valid, Red},    {invalid, None}},
                    {{valid, None},   {valid, Green},  {valid, Green}, {valid, Red},   {valid, Red},   {valid, Green}, {valid, Green},  {valid, None}},
                    {{valid, None},   {valid, Red},    {valid, Red},   {valid, Green}, {valid, Green}, {valid, Red},   {valid, Red},    {valid, None}},
                    {{valid, None},   {valid, Green},  {valid, Green}, {valid, Red},   {valid, Red},   {valid, Green}, {valid, Green},  {valid, None}},
                    {{valid, None},   {valid, Red},    {valid, Red},   {valid, Green}, {valid, Green}, {valid, Red},   {valid, Red},    {valid, None}},
                    {{invalid, None}, {valid, Green},  {valid, Green}, {valid, Red},   {valid, Red},   {valid, Green}, {valid, Green},  {invalid, None}},
                    {{invalid, None}, {invalid, None}, {valid, None},  {valid, None},  {valid, None},  {valid, None},  {invalid, None}, {invalid, None}}
            };

    for(int row = 0; row < 8; row++)
    {
        for(int column = 0; column < 8; column++)
        {
            //Init the square
            output->board[row][column] = initSquare(InitialGameState[row][column].sT, InitialGameState[row][column].c);
            if(output->board[row][column] == NULL)
                return abortInitGameState(output, row, column), freePlayer(output->redPlayer), freePlayer(output->greenPlayer), NULL;
        }
    }

    return output;
}
//Frees a board object, including all allocated memory
void freeGameState(struct gameState* gameStateInstance)
{
    freePlayer(gameStateInstance->redPlayer);
    freePlayer(gameStateInstance->greenPlayer);

    for(int i = 0; i < 8; i++)
    {
        for(int j = 0; j < 8; j++)
        {
            freeSquare(gameStateInstance->board[i][j]);
        }
    }
}