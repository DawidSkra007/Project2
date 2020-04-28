
//
// Created by Lili on 24/03/2020.
//

#ifndef FOCUS_INPUT_OUTPUT_H
#define FOCUS_INPUT_OUTPUT_H

#endif //FOCUS_INPUT_OUTPUT_H

#include "Stack.h"

//Function to print the board
void print_board(square board[BOARD_SIZE][BOARD_SIZE]);
//function that implements the logic of the game
void turns(square board[BOARD_SIZE][BOARD_SIZE],player players);
//function to check if game is over
bool game_end(square boards[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM]);