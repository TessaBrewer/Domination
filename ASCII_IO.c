//
// Created by Deven Brewer #19201772 on 30/03/2020.
//

#include "Game_Logic.h"
#include <stdio.h>
#include "ASCII_IO.h"

//We'll call this is the space on the left is blank to keep everything lined up
#define leftSpacing() printf("           ")

//This is what we'll use to print off the top and bottom row of numbers
#define printHeaderRow() printf("  | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 |")

#define printBlankRow() printf("--+---+---+---+---+---+---+---+---+-- ")

static void printBoardRow(struct gameState* currentGameState, int rowNumber)
{
    printf("%i ", rowNumber);
    for(int i = 0; i < 8; i++)
    {
        if(currentGameState->board[rowNumber][i]->canHaveStack == invalid)
        {
            printf("| X ");
        }else
        {
            enum colour tempColour = getTopPieceColour(currentGameState->board[rowNumber][i]);
            if(tempColour == Red)
            {
                printf("| R ");
            } else if (tempColour == Green)
            {
                printf("| G ");
            } else
            {
                printf("|   ");
            }
        }
    }
    printf("| %i ", rowNumber);
}

void printGameState(struct gameState* currentGameState)
{
    //Print first line of numbers
    leftSpacing();
    printHeaderRow();
    printf("\n");

    leftSpacing();
    printBlankRow();
    printf("\n");

    leftSpacing();
    printBoardRow(currentGameState, 0);
    printf("\n");

    printf("RED PLAYER ");
    printBlankRow();
    printf("GREEN PLAYER");
    printf("\n");

    if(currentGameState->currentTurn == Red)
    {
        printf("========== ");
        printBoardRow(currentGameState, 1);
        printf("\n");
    } else
    {
        leftSpacing();
        printBoardRow(currentGameState, 1);
        printf("============\n");
    }

    leftSpacing();
    printBlankRow();
    printf("\n");

    leftSpacing();
    printBoardRow(currentGameState, 2);
    printf("\n");

    printf("RESERVE:   ");
    printBlankRow();
    printf("RESERVE:\n");

    printf("%03d        ", currentGameState->player1->reserveCount);
    printBoardRow(currentGameState, 3);
    printf("%03d\n", currentGameState->player2->reserveCount);

    leftSpacing();
    printBlankRow();
    printf("\n");

    leftSpacing();
    printBoardRow(currentGameState, 4);
    printf("\n");

    printf("CAPTURED:  ");
    printBlankRow();
    printf("CAPTURED:\n");

    printf("%03d        ", currentGameState->player1->capturedPieces);
    printBoardRow(currentGameState, 5);
    printf("%03d\n", currentGameState->player2->capturedPieces);

    leftSpacing();
    printBlankRow();
    printf("\n");

    leftSpacing();
    printBoardRow(currentGameState, 6);
    printf("\n");

    leftSpacing();
    printBlankRow();
    printf("\n");

    leftSpacing();
    printBoardRow(currentGameState, 7);
    printf("\n");

    leftSpacing();
    printBlankRow();
    printf("\n");

    //Print Last line of numbers
    leftSpacing();
    printHeaderRow();
    printf("\n");
}