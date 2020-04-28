//
// Created by Lili on 26/03/2020.
//

//
// Created by Lili on 24/03/2020.
//
#include <stdbool.h>
#include <stdio.h>
#include "input_output.h"


/* Function to print the board:
 * Invalid Squares are printed as | - |
 * Valid empty squares are printed as |   |
 * Valid squares with a GREEN piece are printed as | G |
 * Valid squares with a RED piece are printed as | R | */

void print_board(square board[BOARD_SIZE][BOARD_SIZE]){//prints board
    printf("\n****** The Board ******\n");
    for(int i = 0; i < BOARD_SIZE; i ++){
        printf("%d ",i);
        for (int j = 0; j < BOARD_SIZE; j++){
            if(board[i][j].type == VALID) {
                if(board[i][j].stack == NULL)
                    printf("|   ");
                else{
                    if (board[i][j].stack->p_color == GREEN)
                        printf("| G%d ",board[i][j].num_pieces);//this prints the amount of pieces in each square
                    else printf("| R%d ",board[i][j].num_pieces);
                }
            }
            else
                printf("| - ");
        }
        printf("| \n");
    }
    printf("  ");
    for(int i = 0; i < BOARD_SIZE;i++){
        printf("  %d  ",i);//prints x and y co-ordinates on the board
    }
}

bool game_end(square board[BOARD_SIZE][BOARD_SIZE],player players[PLAYERS_NUM]){
    bool move = true;
    int red = 0;
    int green = 0;
    for(int i = 0; i < BOARD_SIZE;i++){//checks if a move is possible by seeing if a players color is on top of a stack if it is then a move is possible
        for(int j = 0;j < BOARD_SIZE;j++){
            if(board[i][j].stack != NULL){//if its not empty
                if(board[i][j].stack->p_color == RED){//counts the color on the stack of every piece
                    red++;
                }else if(board[i][j].stack->p_color == GREEN){
                    green++;
                }
            }
        }
    }
        if(red > 0 && green > 0){//if red and green stacks exist a move is possible
            return move;
        }
        else if(red == 0 && players[0].pieces_owned == 0){//if a player has no stack to move and no pieces to capture other player wins
            move = false;
                printf("\n\nGreen Wins the Game!\n\n");
        }
            else if(green == 0 && players[1].pieces_owned == 0){//if a player has no stack to move and no pieces to capture other player wins
                printf("\n\nRed wins the game!\n\n");
            }
        return move;
}

void turns(square board[BOARD_SIZE][BOARD_SIZE],player players) {
    int x_coord, y_coord;//co-ordinates of piece,will be specified by user
    int x_move = 0, y_move = 0;//where to move piece,
    int ans;//user input stored

    start:
    print_board(board);//prints the current board
    printf("\nplayer %sturn:\n", players.name);//prints who's turn it is
    printf("\nEnter 1 if you want to move piece.\nEnter 2 if you want to place captured piece.\n");//user input,what the player wants to do
    scanf("%d", &ans);
    if (ans == 1) {
        goto move;//program will literally 'go to' the 'move' part of the function when user specifies it
    } else if (ans == 2) {
        goto cap;//program will literally 'go to' the 'cap' part of the function when user specifies it
    } else {
        printf("\ninvalid choice.\n");
        goto start;//if invalid choice it will print the board and ask the user what to do again
    }
    move://if user wants to move a piece
    printf("Enter coordinates of the piece you would like to move:\n");
    scanf("%d %d", &y_coord, &x_coord);//co-ordinates of the piece which will be moved
    if (board[x_coord][y_coord].stack->p_color != players.player_color) {
        printf("Error your piece is not on top\n");//if your piece is not on top i.e. you cant move it
        goto move;                                 //it will go to 'move', so it will ask you again
    } else {
        printf("\nYou have %d moves.\n", board[x_coord][y_coord].num_pieces);//based on the amount of pieces in the stack selected, thats how many moves you have
        for (int k = 0; k < board[x_coord][y_coord].num_pieces; k++) {//it will ask you for your input on where to move as many times as the amount of pieces in the stack
            int choice;
            printf("Enter 1 to move up.\nEnter 2 to move down.\n"
                   "Enter 3 to move left.\nEnter 4 to move right.\n"
                   "Enter 5 if you want to stop moving.\n");
            scanf("%d", &choice);
            if (choice == 5) {
                goto quit;
            } else {
                switch (choice) {//it will change the co-ordinates of where the piece is to be moved based on the users answer
                    case 1:
                        x_move -= 1;
                        break;
                    case 2:
                        x_move += 1;
                        break;
                    case 3:
                        y_move -= 1;
                        break;
                    case 4:
                        y_move += 1;
                        break;
                    default:
                        printf("invalid choice.");
                        goto move;//will ask user again
                }
            }
        }
        quit://if you do not want to make a move
        x_move += x_coord;
        y_move += y_coord;
    }
    if (board[x_move][y_move].type == INVALID) {//cant move a piece to an INVALID spot on the board
        printf("invalid move \n\n");
        goto move;//will ask again for user input

    } else if (board[x_move][y_move].num_pieces == 0) {//when there's no pieces at where u went to move it

        board[x_move][y_move].stack = board[x_coord][y_coord].stack;//moves the pieces
        board[x_move][y_move].num_pieces += board[x_coord][y_coord].num_pieces;//adds the added pieces to the number of pieces in that stack
        set_empty(&board[x_coord][y_coord]);
    } else if (board[x_coord][y_coord].num_pieces == 1) {//moving 1 piece

        *board[x_move][y_move].stack = push(board[x_coord][y_coord].stack, board[x_move][y_move].stack);//using the push function to add the piece on
        ++board[x_move][y_move].num_pieces;//when one piece is being moved the amount of pieces in the stack goes up by one
        set_empty(&board[x_coord][y_coord]);
    } else {//if moving stack

        *board[x_move][y_move].stack = merge(board[x_move][y_move].stack, board[x_coord][y_coord].stack);//the merge function will add a stack on
        board[x_move][y_move].num_pieces += board[x_coord][y_coord].num_pieces;//adds the added pieces to the number of pieces in that stack
        set_empty(&board[x_coord][y_coord]);
    }
    if (board[x_move][y_move].num_pieces > 5) {//a stack cant be more than 5 pieces

        int tot = board[x_move][y_move].num_pieces - 5;//finds the excess amount of pieces
        *board[x_move][y_move].stack = removep(tot, board[x_move][y_move].stack, players);//from the stack it will remove the excess amount of pieces in the stack
        board[x_move][y_move].num_pieces = 5;//the amount of pieces on the stack after removing excess pieces is 5
    }


    cap:
        if (players.pieces_owned == 0) {//if player has no captured pieces this message will appear and will ask the user again
            printf("You have no captured pieces!\n");
            goto start;
        } else {//if
            printf("Enter where you want to place the piece:\n");
            int x_cap, y_cap;//co-ordinates of where to place the piece
            scanf("%d %d", &x_cap, &y_cap);
            piece cap_piece;
            cap_piece.p_color = players.player_color;
            cap_piece.next = NULL;//its a single piece.
            *board[x_cap][y_cap].stack = push(&cap_piece, board[x_cap][y_cap].stack);//places the piece on the specified spot
            ++board[x_cap][y_cap].num_pieces;//adds that piece to the total amount of pieces on the board.
            --players.pieces_owned;//when piece is placed it will take that piece away from the amount of pieces a player has captured
        }
    }