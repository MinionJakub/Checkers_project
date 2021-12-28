#include <stdio.h>
#include <stdlib.h>
#include "draw_in_command_console.h"
#include "checkers_rules_and_logic.h"

int main()
{
    int **board = initiate();
    int legal_attack[50][4];
    int legal_move[50][4];
    int how_many_moves = 0;
    int how_many_attacks = 0;
    int whose_turn = -1;
    int operation = 0;
    int end_the_game = 0;
    char *command;
    int correctness = 0;
    int *action;
    while(!end_the_game){
        if(operation != 1)draw_map_of_game(board,8,8);
        if(whose_turn == 1 && operation != 1)printf("Move has upper player\n");
        else if (operation != 1)printf("Move has bottom player\n");
        legal_action(board,legal_attack,legal_move,8,&how_many_moves,&how_many_attacks,whose_turn);
        command = read_entry(&operation);
        if(operation == 1)show_legal_moves(legal_move,legal_attack,how_many_moves,how_many_attacks);
        else if(operation == 2) end_the_game = 1;
        else{
            correctness = 0;
            action = read_move(legal_attack,legal_move,how_many_moves,how_many_attacks,&correctness,command);
            if(correctness && how_many_attacks){
                attack_action(board,action);
                whose_turn *= -1;
            }
            else if(correctness && how_many_moves){
                move_action(board,action);
                whose_turn *= -1;
            }
        }
        who_is_winner(board,8,&end_the_game);
    }
    exit (0);
}
