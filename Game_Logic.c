//
// Created by Deven Brewer #19201772 on 30/03/2020.
//
#include <stdlib.h>

#include "Game_Logic.h"

#include "Object_Definition.h"

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