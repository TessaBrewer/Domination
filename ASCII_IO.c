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

    printf("%03d        ", currentGameState->redPlayer->reserve->stackHeight);
    printBoardRow(currentGameState, 3);
    printf("%03d\n", currentGameState->greenPlayer->reserve->stackHeight);

    leftSpacing();
    printBlankRow();
    printf("\n");

    leftSpacing();
    printBoardRow(currentGameState, 4);
    printf("\n");

    printf("CAPTURED:  ");
    printBlankRow();
    printf("CAPTURED:\n");

    printf("%03d        ", currentGameState->redPlayer->capturedPieces);
    printBoardRow(currentGameState, 5);
    printf("%03d\n", currentGameState->greenPlayer->capturedPieces);

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

void printSquare(struct square* input)
{
    if(input->canHaveStack == invalid)
    {
        printf("Invalid Square\n");
    } else
    {
        if(input->stack == NULL)
        {
            printf("Empty Square\n");
        } else //At this point we know that input IS valid, and IS NOT empty
        {
            //Print out the guide eg | 1 | 2 | 3 | 4 | 5 |
            printf("|");
            for(int i = 0; i < input->stackHeight; i++)
                printf(" %i |", i);
            printf("\n");

            //Print out the actual contents of the stack eg | R | G | G | R | R |
            printf("|");
            struct piece* currentPiece = input->stack;
            while(currentPiece != NULL)
            {
                if(currentPiece->pieceColour == Red)
                {
                    printf(" R |");
                } else
                {
                    printf(" G |");
                }

                currentPiece = currentPiece->next;
            }
            printf("\n");
        }
    }
}

//The following code handles user input

//Gets a user move, handles the event where a user asks for the contents of a stack, makes a reserve move, or makes a standard move
    //We DO NOT validate a user's move here, we only make sure we receive valid input, ie the user enters the correct number of ints, and that they're in range, NOT if the user's move follows the games rules
    //validateMove() should be called on the userMove object that we return from this function
void getMove(struct gameState* currentGameState, struct userMove* output)
{
    int x1, y1; //Coordinates of the origination
    int x2, y2; //Coordinates of the destination
    int pieceCount; //The number of pieces the user wants to move
    int inputCount; //We'll use this to make sure scanf is getting the right number of values
    int quitFlag = 0;

    while(!quitFlag)
    {
        //Prompt the user for input
        printf("?: ");

        switch (getchar())
        {
            //Handles the case where the user wants to print out the contents of a stack
            case '?':
                inputCount = scanf("%*c%i%*c %i%*c ", &x1, &y1);

                if(inputCount != 2)
                {
                    printf("Error: incorrect formatting, please format input as \"?(x, y)\" where x and y are integers between 0 & 7 (inclusive)\n");
                }

                if(x1 >= 8 || y1 >= 8 || x1 < 0 || y1 < 0) //Make sure user input is in range
                {
                    printf("Error: all values must be between 0 & 7 (inclusive)\n");
                    break;
                }

                printSquare(currentGameState->board[x1][y1]);
                break;
            //Handles the event that the user wants to move a piece from their reserve
            case 'R':
                inputCount = scanf("%*c%i%*c %i%*c ", &x2, &y2);

                if(inputCount != 2) //Make sure we received the correct number of inputs
                {
                    printf("Error: incorrect formatting, please format input as \"R(x, y)\" where x and y are integers between 0 & 7 (inclusive)\n");
                    break;
                }

                if(x2 >= 8 || y2 >= 8 || x2 < 0 || y2 < 0) //Make sure user input is in range
                {
                    printf("Error: all values must be between 0 & 7 (inclusive)\n");
                    break;
                }

                if(currentGameState->currentTurn == Red)
                {
                    output->origination = currentGameState->redPlayer->reserve;
                } else
                {
                    output->origination = currentGameState->greenPlayer->reserve;
                }
                output->destination = currentGameState->board[x2][y2];
                output->pieceCount = 1; //The user can only move 1 piece out of their reserve at a time
                quitFlag = 1;
                break;
            //Handles the event that the user wants to make a standard move
            case '(':
                inputCount = scanf("%i%*c %i%*c %*c%i%*c %i%*c %i ", &x1, &y1, &x2, &y2, &pieceCount);

                if(inputCount != 5) //Make sure we received the correct number of inputs
                {
                    printf("Error: incorrect formatting, please format input as \"(x1, y1) (x2, y2) z\" where x1, y1, x2, and y2 are integers between 0 & 7 (inclusive) and z is an integer between 0 & 5 (inclusive)\n");
                    break;
                }

                if(x1 >= 8 || y1 >= 8 || x2 >= 8 || y2 >= 8 || x1 < 0 || y1 < 0 || x2 < 0 || y2 < 0) //Make sure the grid selection is in range
                {
                    printf("Error: x1, y1, x2, and y2 must be between 0 & 7 (inclusive)\n");
                    break;
                }

                if(pieceCount < 0 || pieceCount > 5) //Make sure that the user is selecting a valid number of pieces
                {
                    printf("Error: z must be between 0 & 5 (inclusive)\n");
                    break;
                }

                output->origination = currentGameState->board[x1][y1];
                output->destination = currentGameState->board[x2][y2];
                output->pieceCount = pieceCount;

                quitFlag = 1;
                break;
        }
    }
}