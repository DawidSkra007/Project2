//
// Created by Dawid Skraba on 28/04/2020.
//

#ifndef FOCUS_STACK_H
#define FOCUS_STACK_H

#endif //FOCUS_STACK_H

#include "game_init.h"

//function to add a piece
piece push(piece *new , piece *top);
//function to merge stacks
piece merge(piece *top, piece *top2);
//function to remove pieces
piece removep(int tot,piece *top,player players);
