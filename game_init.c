//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "game_init.h"

void initialize_players(player players[PLAYERS_NUM]){
    int i,j;
    int pl = 1;
    // implement here the functionality to initialize the players
    for(i = 0;i < PLAYERS_NUM;i++){
        printf("What is the name of player %d:\n",pl);
        fgets(players[i].name, PLAYER_NAME_LENGTH, stdin);
        pl++;
    }
    //assigning color to players
    players[0].player_color = RED;
    players[1].player_color = GREEN;
    //printing to console which player is which colour
    for(j = 0;j < PLAYERS_NUM;j++){
        printf("\n%syour color is:\n",players[j].name);
        if(players[j].player_color == RED){
            printf("Red\n");
        }
        if(players[j].player_color == GREEN){
            printf("Green\n");
        }
    }

}



//Set Invalid Squares (where it is not possible to place stacks)
square set_invalid(square * s){
s->type = INVALID;
s->stack = NULL;
s->num_pieces = 0;
return *s;
}

//Set Empty Squares (with no pieces/stacks)
square set_empty(square * s){
s->type = VALID;
s->stack = NULL;
s->num_pieces = 0;
return *s;
}

//Set squares  with a GREEN piece
square set_green(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = GREEN;
s->stack->next = NULL;
s->num_pieces = 1;
return *s;
}

//Set squares with a RED piece
square set_red(square * s){
s->type = VALID;
s->stack = (piece *) malloc (sizeof(piece));
s->stack->p_color = RED;
s->stack->next = NULL;
s->num_pieces = 1;
return *s;
}

//initializes the board
void initialize_board(square board [BOARD_SIZE][BOARD_SIZE]){

    for(int i = 0; i< BOARD_SIZE; i++){
        for(int j = 0; j< BOARD_SIZE; j++){
            //invalid squares
            if((i==0 && (j==0 || j==1 || j==6 || j==7)) ||
               (i==1 && (j==0 || j==7)) ||
               (i==6 && (j==0 || j==7)) ||
               (i==7 && (j==0 || j==1 || j==6 || j==7)))
                set_invalid(&board[i][j]);

            else{
                //squares with no pieces
                if(i==0 || i ==7 || j==0 || j == 7)
                    set_empty(&board[i][j]);
                else{
                    //squares with red pieces
                    if((i%2 == 1 && (j < 3 || j> 4)) ||
                       (i%2 == 0 && (j == 3 || j==4)))
                        set_red(&board[i][j]);
                        //green squares
                    else set_green(&board[i][j]);
                }
            }
        }


    }


}

