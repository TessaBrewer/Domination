//
// Created by Deven Brewer on 24/04/2020.
//

#include "Unit_Tests.h"

//Modules for required for unit tests
#include <CUnit/CUnit.h>
#include <CUnit/Basic.h>

#include "Object_Definition.h"

//The modules we'll be testing
#include "Game_Init.h"

//Contains all of the tests for our initiation code
static void testInit(void)
{
    //Test if we initialize pieces correctly
    struct piece examplePiece = {Red, NULL};
    struct piece* testPiece = initPiece(Red);
    CU_ASSERT_EQUAL(testPiece->next, examplePiece.next);
    CU_ASSERT_EQUAL(testPiece->pieceColour, examplePiece.pieceColour);
    freePiece(testPiece);

    //Test if we initialize squares correctly
    struct square exampleSquare = {valid, NULL, 0};
    struct square* testSquare = initSquare(valid, None);
    CU_ASSERT_EQUAL(testSquare->canHaveStack, exampleSquare.canHaveStack);
    CU_ASSERT_EQUAL(testSquare->stack, exampleSquare.stack);
    CU_ASSERT_EQUAL(testSquare->stackHeight, exampleSquare.stackHeight);
    freeSquare(testSquare);

    //Test if we initialize players correctly
    struct player examplePlayer = {Red, &exampleSquare, 0};
    struct player* testPlayer = initPlayer(Red);
    CU_ASSERT_EQUAL(testPlayer->playerColour, examplePlayer.playerColour);
        CU_ASSERT_EQUAL(testPlayer->reserve->canHaveStack, examplePlayer.reserve->canHaveStack);
        CU_ASSERT_EQUAL(testPlayer->reserve->stack, examplePlayer.reserve->stack);
        CU_ASSERT_EQUAL(testPlayer->reserve->stackHeight, examplePlayer.reserve->stackHeight);
    CU_ASSERT_EQUAL(testPlayer->capturedPieces, examplePlayer.capturedPieces);
    freePlayer(testPlayer);

    struct gameState* testState = initGameState();
    CU_ASSERT_EQUAL(testState->currentTurn, Red);
    CU_ASSERT_EQUAL(testState->redPlayer->playerColour, Red);
    CU_ASSERT_EQUAL(testState->greenPlayer->playerColour, Green);
    CU_ASSERT_EQUAL(testState->board[0][0]->canHaveStack, invalid);
    CU_ASSERT_EQUAL(testState->board[1][1]->stack->pieceColour, Red);
    freeGameState(testState);
}

//Calls all of the unit tests
void preformTests(void)
{
    CU_initialize_registry();

    CU_pSuite init_suite = CU_add_suite("init_test", 0, 0);
    CU_add_test(init_suite, "init_test", testInit);

    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
}