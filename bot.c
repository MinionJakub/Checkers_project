#include <stdio.h>
#include <stdlib.h>
#include "bot.h"
#include "checkers_rules_and_logic.h"

//static int deep = 10;

// co funkcja bedzie potrzebowac planszy, glebi, kto ma ture, wartosciowania sytuacji,
// co funkcja ma zwracac ruch?, evaluacje
//podzial na dwie funkcje jedna do zwracania najlepszego ruchu, druga do ewaluacji!!! - pierwszy pomysl

/*int evaluation_of_move(int **board, int size_of_board, int whose_turn, int enemy_value, int my_value, int deep){
    if(deep <= 0) return value_of_board(board,size_of_board);
    int legal_attack[20][4];
    int legal_move[20][4];
    int how_many_attacking_moves = 0;
    int how_many_moves = 0;
    legal_action(board,legal_attack,legal_move,size_of_board,&how_many_moves,&how_many_attacking_moves,whose_turn);
    int end_the_game = 0;

    if(how_many_attacking_moves){
        int max_val_for_actual_player = -10000;
        int actual_val;
        int **copy_of_board;
        copy_of_board = malloc(sizeof(int*)*size_of_board);
        for (int i = 0; i < size_of_board;i++){
            copy_of_board[i]= malloc(sizeof(int*)*size_of_board);
        }
        for(int i = 0; i < how_many_attacking_moves; i++){
            for(int j = 0;j<size_of_board;j++){
                for(int k = 0; k < size_of_board;k++){
                    copy_of_board[j][k]=board[j][k];
                }
            }
            attack_action(copy_of_board,legal_attack[i]);
            int what_type_of_attack = -1;
            if (legal_attack[i][1]-legal_attack[i][3] < 0) what_type_of_attack = 1;
            continue_attack(copy_of_board,legal_attack[i][3],legal_attack[i][2],legal_attack,&how_many_attacking_moves,what_type_of_attack);
            while(how_many_attacking_moves){
                attack_action(copy_of_board,legal_attack[0]);
                continue_attack(copy_of_board,legal_attack[0][3],legal_attack[0][2],legal_attack,&how_many_attacking_moves,what_type_of_attack);
            }
            who_is_winner(copy_of_board,size_of_board,&end_the_game);
            promotion(copy_of_board,size_of_board)
            if(end_the_game == enemy_value){
                max_val_for_actual_player = 10000;
                actual_val =
            }
            else if(end_the_game == my_value);
            else return evaluation_of_move(copy_of_board,size_of_board,-whose_turn,enemy_value,my_value,deep-1);
        }
    }
    else{

    }
}*/
