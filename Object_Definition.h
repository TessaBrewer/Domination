//
// Created by Deven Brewer #19201772 on 27/03/2020.
//

#ifndef DOMINATION_OBJECTDEF_H
#define DOMINATION_OBJECTDEF_H

//The two possible colours in our game, every piece and player will be assigned one of these
enum colour {Red, Green};

//Represents wether or not a section of our 8x8 array is a valid spot on the game board
enum squareType {invalid, valid};

//Represents a player, we should have 2 of these total
struct player
{
    enum colour;
    //The number of pieces this player has in reserve, they get these by "capturing" their own pieces, a turn can be used to place one of these onto the board
    int reserve;
    //The number of pieces this player owns which belong to the other player, this is entirely unnecessary for the game's core functionality
    int capturedPieces;
};

//Represents one of the game pieces, we'll represent a stack of pieces as a one-way linked list
struct piece
{
    enum colour;
    //Which piece is currently on top of this piece, NULL if this is the top of it's stack
    struct piece* next;
};

//Represents one of the squares on the board
struct square
{
    //Valid or Invalid, invalid squares are part of the array, but not part of the board
    enum squareType;
    //Pointer to the piece on top of this square, NULL if this square is empty
    struct piece* stack;
    //The height of the stack stored on this square, we could just count the height of the stack whenever we need it, which would save memory for a negligible cost in processing time
    int stackHeight;
};

//Represents the game state, we'll be able to easily modify the game state by passing a pointer to this object back and forth between functions
struct board
{
    struct player player1, player2;
    struct square[8][8];
};
#endif //DOMINATION_OBJECTDEF_H
