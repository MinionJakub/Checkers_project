#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "bot.h"
#include "checkers_rules_and_logic.h"

//static int deep = 10;

// co funkcja bedzie potrzebowac planszy, glebi, kto ma ture, wartosciowania sytuacji,
// co funkcja ma zwracac ruch?, evaluacje
//podzial na dwie funkcje jedna do zwracania najlepszego ruchu, druga do ewaluacji!!! - pierwszy pomysl

int evaluation_of_move(int **board, int size_of_board, int whose_turn, int enemy_value, int my_value, int deep){
    if(deep <= 0){
        //print_board(board);
        //putchar('\n');
        return value_of_board(board,size_of_board);
    }
    int legal_attack[20][4];
    int legal_move[20][4];
    int how_many_attacking_moves = 0;
    int how_many_moves = 0;
    legal_action(board,legal_attack,legal_move,size_of_board,&how_many_moves,&how_many_attacking_moves,whose_turn);
    int end_the_game = 0;

    if(how_many_attacking_moves == 0 && how_many_moves == 0){
        who_is_winner(board,8,&end_the_game);
        return end_the_game*10000;
    }

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
            promotion(copy_of_board,size_of_board);
            if(end_the_game == enemy_value){
                actual_val = -10000*whose_turn;
            }
            else if(end_the_game == my_value){
                actual_val = 10000*whose_turn;
            }
            else actual_val = evaluation_of_move(copy_of_board,size_of_board,-whose_turn,enemy_value,my_value,deep-1)*whose_turn;
            if (actual_val > max_val_for_actual_player) max_val_for_actual_player = actual_val;
        }
        free(copy_of_board);
        //printf("%d %d\n",max_val_for_actual_player*whose_turn,deep);
        return(max_val_for_actual_player*whose_turn);
    }

    else{
        int max_val_for_actual_player = -10000;
        int actual_val;
        int **copy_of_board;
        copy_of_board = malloc(sizeof(int*)*size_of_board);
        for (int i = 0; i < size_of_board;i++){
            copy_of_board[i]= malloc(sizeof(int*)*size_of_board);
        }
        for(int i = 0; i<how_many_moves;i++){
            for(int j = 0;j<size_of_board;j++){
                for(int k = 0; k < size_of_board;k++){
                    copy_of_board[j][k]=board[j][k];
                }
            }
            move_action(copy_of_board,legal_move[i]);
            promotion(copy_of_board,size_of_board);
            actual_val = evaluation_of_move(copy_of_board,size_of_board,-whose_turn,enemy_value,my_value,deep-1)*whose_turn;
            if(max_val_for_actual_player < actual_val) max_val_for_actual_player = actual_val;
        }
        free(copy_of_board);
        //printf("%d %d\n",max_val_for_actual_player*whose_turn,deep);
        return(max_val_for_actual_player*whose_turn);
    }
}

int *bot_make_decision(int **board,int size_of_board,int whose_turn,int enemy_value,int my_value,int deep){
    int *input = malloc(sizeof(int*)*4);
    int legal_attack[20][4];
    int legal_move[20][4];
    int how_many_attacking_moves = 0;
    int how_many_moves = 0;
    legal_action(board,legal_attack,legal_move,size_of_board,&how_many_moves,&how_many_attacking_moves,whose_turn);
    int end_the_game = 0;
    int value_table[20];
    if(how_many_attacking_moves){
        int actual_val;
        int **copy_of_board;
        copy_of_board = malloc(sizeof(int*)*size_of_board);
        for (int i = 0; i < size_of_board;i++){
            copy_of_board[i]= malloc(sizeof(int*)*size_of_board);
        }
        for(int i = 0; i < how_many_attacking_moves; i++){
            int max_val_for_actual_player = -10000;
            for(int j = 0;j<size_of_board;j++){
                for(int k = 0; k < size_of_board;k++){
                    copy_of_board[j][k]=board[j][k];
                }
            }
            attack_action(copy_of_board,legal_attack[i]);
            int what_type_of_attack = -1;
            if (legal_attack[i][1]-legal_attack[i][3] < 0) what_type_of_attack = 1;
            int check_attack[2][4];
            int check_how_many_attacks = 0;
            continue_attack(copy_of_board,legal_attack[i][3],legal_attack[i][2],check_attack,&check_how_many_attacks,what_type_of_attack);
            while(check_how_many_attacks){
                attack_action(copy_of_board,check_attack[0]);
                continue_attack(copy_of_board,check_attack[0][3],check_attack[0][2],check_attack,&check_how_many_attacks,what_type_of_attack);
            }
            who_is_winner(copy_of_board,size_of_board,&end_the_game);
            promotion(copy_of_board,size_of_board);
            if(end_the_game == enemy_value){
                actual_val = -10000*whose_turn;
            }
            else if(end_the_game == my_value){
                actual_val = 10000*whose_turn;
            }
            else actual_val = evaluation_of_move(copy_of_board,size_of_board,-whose_turn,enemy_value,my_value,deep-1)*whose_turn;
            if (actual_val > max_val_for_actual_player) max_val_for_actual_player = actual_val;
            value_table[i]=max_val_for_actual_player;
        }
        free(copy_of_board);

    }
    else{
        int actual_val;
        int **copy_of_board;
        copy_of_board = malloc(sizeof(int*)*size_of_board);
        for (int i = 0; i < size_of_board;i++){
            copy_of_board[i]= malloc(sizeof(int*)*size_of_board);
        }
        for(int i = 0; i<how_many_moves;i++){
            for(int j = 0;j<size_of_board;j++){
                for(int k = 0; k < size_of_board;k++){
                    copy_of_board[j][k]=board[j][k];
                }
            }
            int max_val_for_actual_player = -10000;
            move_action(copy_of_board,legal_move[i]);
            promotion(copy_of_board,size_of_board);
            actual_val = evaluation_of_move(copy_of_board,size_of_board,-whose_turn,enemy_value,my_value,deep-1)*whose_turn;
            if(max_val_for_actual_player < actual_val) max_val_for_actual_player = actual_val;
            value_table[i]=max_val_for_actual_player;
        }
        free(copy_of_board);
    }
    int max_val_for_table = value_table[0];
    int how_many_the_best_moves = 1;
    for(int i = 0; i < how_many_attacking_moves;i++){
        if (max_val_for_table < value_table[i]){
            max_val_for_table=value_table[0];
            how_many_the_best_moves = 1;
        }
        else if(max_val_for_table == value_table[i])how_many_the_best_moves++;
    }
    if(how_many_attacking_moves == 0){
        for(int i = 0; i < how_many_moves;i++){
            if (max_val_for_table < value_table[i]){
                max_val_for_table=value_table[0];
                how_many_the_best_moves = 1;
            }
            else if(max_val_for_table == value_table[i])how_many_the_best_moves++;
        }
    }
    time_t t = difftime(time(NULL),clock());
    srand((unsigned) time(&t));
    int i = 0;
    int j = 0;
    int losowa = rand()%how_many_the_best_moves;
    losowa = rand()%how_many_the_best_moves;
    printf("%d ",losowa);
    while(i < losowa-1 || value_table[j] != max_val_for_table){
        if(max_val_for_table == value_table[j])i++;
        j++;
    }
    printf("%d\n",j);
    if(how_many_attacking_moves){
        input[0] = legal_attack[j][0];
        input[1] = legal_attack[j][1];
        input[2] = legal_attack[j][2];
        input[3] = legal_attack[j][3];
        return input;
    }
    input[0] = legal_move[j][0];
    input[1] = legal_move[j][1];
    input[2] = legal_move[j][2];
    input[3] = legal_move[j][3];
    return input;
}
