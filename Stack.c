//
// Created by Dawid Skraba on 28/04/2020.
//

#include "Stack.h"
#include <mm_malloc.h>
#include <stdio.h>

piece push(piece *new, piece *top){
    piece *curr = top;
    top = malloc(sizeof(piece));
    top->p_color = new->p_color;
    top->next = curr;
    return *top;
}

piece merge(piece *top, piece *top2){
    piece *curr = top2;
    if(top2->next == NULL){
        curr->next = top;
    }
    while(curr->next != NULL){
        curr = curr->next;
    }
    curr->next = top;
    return *top;
}

piece removep(int tot, piece *top,player players){
    piece *last = top;
    int i;
    for(i = 0;i < 5;i++){
        last = last->next;
    }
    last->next = NULL;
    return *top;
}