//
// Created by Deven Brewer #19201772 on 30/03/2020.
//
#include <stdlib.h>
#include <math.h>
#include <stdio.h>

#include "Game_Logic.h"
#include "Object_Definition.h"

//So we can free captured pieces
#include "Game_Init.h"

#define MAX_STACK_HEIGHT 5

enum colour getTopPieceColour(struct square* mySquare)
{
    if(mySquare->canHaveStack == None || mySquare->stack == NULL)
        return (enum colour)None;

    struct piece* currentPieceInStack = mySquare->stack;
    struct piece* nextPieceInStack = currentPieceInStack->next;
    while(nextPieceInStack != NULL)
    {
        currentPieceInStack = nextPieceInStack;
        nextPieceInStack = currentPieceInStack->next;
    }
    return currentPieceInStack->pieceColour;
}

//Returns the Manhattan Distance between 2 points, valid moves have a distance < the number of pieces being moved
#define manDis(x1, y1, x2, y2) (abs(x1 - x2) + abs(y1 - y2))

//Validates a move, including checking if it's in range, if the current user is allowed to move it, and if they selected a valid number of pieces, etc
    //Returns 1 if valid, 0 if not
int validateMove(struct gameState* currentGameState, struct userMove* target)
{
    //Check if the 2 squares selected are both valid
    if(target->origination.storage->canHaveStack == invalid || target->destination.storage->canHaveStack == invalid)
    {
        printf("Invalid destination or origination\n");
        return 0;
    }

    //Check if the origination square is of the wrong colour
    if(getTopPieceColour(target->origination.storage) != currentGameState->currentTurn)
    {
        printf("Stack has wrong colour\n");
        return 0;
    }

    //Check if there's enough pieces in the origination stack
    if(target->pieceCount > target->destination.storage->stackHeight)
    {
        printf("Stack is too small\n");
        return 0;
    }

    //Check if the origination is the reserve (if it is then we don't need to check distance)
    if(target->origination.row == -1 && target->origination.column == -1)
        return 1;

    //Check if the move is within the valid range
    if(manDis(target->origination.row, target->origination.column, target->destination.row, target->destination.column) <= target->pieceCount)
        return 1;

    printf("Out of range\n");
    return 0;
}

static void shiftStack(struct piece** from, struct piece** to)
{
    (*to)->next = (*from)->next;
    (*from) = NULL;
}

//This function will preform the actual move inputted by the user
    //Moves should always be validated before they are used, this function's behavior is undefined for invalid moves
    //Returns NULL upon encountering an error
int movePieces(struct gameState* currentGameState, struct userMove* move)
{
    if(move->origination.storage->stackHeight < move->pieceCount) //Minor error handling, this should be taken care of in validateMove(), but we could do some really bad things here if that fails or if we forget to call it, so we're going to go ahead and build in some extra protection
        return fprintf(stderr, "Error: Originating stack height must be greater than or equal to the number of pieces moved\n"), NULL;

    //Move pieces
        //We're using pointers to pointers so that we may modify the values of the pointers regardless of where they're being stored
    struct piece** from = &(move->origination.storage->stack);
    struct piece** to = &(move->destination.storage->stack);

    for(int i = 0; i < move->origination.storage->stackHeight - move->pieceCount; i++) //Find the pointer pointing to the bottom-most piece in the stack we're moving
        from = &((*from)->next);

    while(*(to) != NULL) //Find the pointer leading out of the top most piece in our destination stack
        to = &((*to)->next);

    shiftStack(from, to);

    //Update stack heights
    move->origination.storage->stackHeight -= move->pieceCount; //Update the height of our originating stack, this should never be negative

    move->destination.storage->stackHeight += move->pieceCount; //Update the height of our destination stack

    //Move pieces to reserve and captured squares
    if(move->destination.storage->stackHeight > MAX_STACK_HEIGHT)
    {
        //Get a pointer to where we'll store the reserved pieces
        struct piece* topOfReserve;
        //We're using int pointers here to avoid having conditional code within a loop
        int* reserveHeight;
        int* captureCount;
        if(currentGameState->currentTurn == Red) //Get the stack's base
        {
            topOfReserve = currentGameState->redPlayer->reserve->stack;
            reserveHeight = &(currentGameState->redPlayer->reserve->stackHeight);
            captureCount = &(currentGameState->redPlayer->capturedPieces);
        } else
        {
            topOfReserve = currentGameState->greenPlayer->reserve->stack;
            reserveHeight = &(currentGameState->greenPlayer->reserve->stackHeight);
            captureCount = &(currentGameState->greenPlayer->capturedPieces);
        }
        while(topOfReserve->next != NULL) //Find the top of the reserve stack
            topOfReserve = topOfReserve->next;

        struct piece* current; //The current piece at the bottom of the stack we're looking at
        struct piece* next = move->destination.storage->stack; //The piece directly above current
        while(move->destination.storage->stackHeight > MAX_STACK_HEIGHT)
        {
            current = next;
            next = current->next;
            if(current->pieceColour == currentGameState->currentTurn) //If we need to reserve the bottom-most piece
            {
                topOfReserve->next = current;//Move the current piece to the top of the reserve
                topOfReserve = topOfReserve->next;//Point topOfReserve to the new top of the reserve
                topOfReserve->next = NULL; //Re-terminate the reserve
                *(reserveHeight) += 1;
                move->destination.storage->stack = next; //Place the remainder of the stack back onto its square
                move->destination.storage->stackHeight -= 1;
            }else //If the bottom-most piece is captured
            {
                current->next = NULL; //Prep the piece to be freed
                freePiece(current); //Delete the piece
                move->destination.storage->stack = next; //Place the remainder of the stack back onto it's square
                move->destination.storage->stackHeight -= 1;
            }
        }
    }

    return 1;
}