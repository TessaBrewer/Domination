//
// Created by Deven Brewer #19201772 on 27/03/2020.
//

#ifndef DOMINATION_OBJECTDEF_H
#define DOMINATION_OBJECTDEF_H

//The two possible colours in our game, every piece and player will be assigned one of these
    //None should only be used to describe nonexistent pieces
enum colour {Red, Green, None};

//Represents whether or not a square object is a valid place to store game pieces, the game board & player reserves should be valid, the empty corners of the 8x8 array should be invalid
enum squareType {invalid, valid};

//Represents one of the game pieces, we'll represent a stack of pieces as a one-way linked list
struct piece
{
    enum colour pieceColour;
    //Which piece is currently on top of this piece, NULL if this is the top of it's stack
    struct piece* next;
};

//Represents one of the squares on the board
struct square
{
    //Valid or Invalid, invalid squares are part of the array, but not part of the board
    enum squareType canHaveStack;
    //Pointer to the piece on top of this square, NULL if this square is empty
    struct piece* stack;
    //The height of the stack stored on this square, we could just count the height of the stack whenever we need it, which would save memory for a negligible cost in processing time
    int stackHeight;
};

//Represents a player, we should have 2 of these total
struct player
{
    enum colour playerColour;
    //The number of pieces this player has in reserve, they get these by "capturing" their own pieces, a turn can be used to place one of these onto the board
    int reserveCount;
    //Where we'll store all of the reserve pieces incase they need to be replaced to the board, this allows us to avoid having to constantly free and reallocate pieces as they enter/leave a player's reserve
    struct square* reserve;
    //The number of pieces this player owns which belong to the other player, this is entirely unnecessary for the game's core functionality
    int capturedPieces;
};

//Represents the game state, we'll be able to easily modify the game state by passing a pointer to this object back and forth between functions
struct gameState
{
    struct player* player1, *player2;
    struct square* board[8][8];
};
#endif //DOMINATION_OBJECTDEF_H
