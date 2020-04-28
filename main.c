//
// Created by Lili on 26/03/2020.
//

#include <stdio.h>
#include <stdbool.h>
#include "input_output.h"


int main() {

    // declaration of the players and the board
    player players[PLAYERS_NUM];
    square board[BOARD_SIZE][BOARD_SIZE];

    initialize_players(players);

    initialize_board(board);

    print_board(board);

    bool i = game_end(board,players);

        while(i == true){//checks if move is possible if it is, game is not over

            turns(board, players[0]);//move player 1
            i = game_end(board,players);

            if(i == true){//checking if move possible after the last move

                turns(board, players[1]);//move player 2
                i = game_end(board,players);//keeps checking if moves are possible
            }
        }



    return 0;
}
