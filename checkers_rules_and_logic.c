#include <stdio.h>
#include <stdlib.h>
#include "checkers_rules_and_logic.h"

int absolute_value(int number){
    if (number < 0) number = -number;
    return number;
}

int **initiate(){
    static int map_start_64[8][8]= {{0,1,0,1,0,1,0,1},{1,0,1,0,1,0,1,0},{0,1,0,1,0,1,0,1},{0,0,0,0,0,0,0,0},{0,0,0,0,0,0,0,0},{-1,0,-1,0,-1,0,-1,0},{0,-1,0,-1,0,-1,0,-1},{-1,0,-1,0,-1,0,-1,0}};
    int **board;
    board = malloc(sizeof(int*)*8);
    for(int i = 0; i < 8; i++){
        board[i] = malloc(sizeof(int*)*8);
    }
    for(int i = 0; i < 8; i++){
        for (int j = 0; j < 8; j++){
            board[i][j] = map_start_64[i][j];
        }
    }
    return board;
}



void legal_action(int **board, int legal_attack[][4], int legal_move[][4], int size_of_board, int *what_number_legal_moves, int *what_number_legal_attacks,int whose_action){
    *what_number_legal_moves = 0;
    *what_number_legal_attacks = 0;
    for(int row = 0; row < size_of_board; row++){
        for(int column = 0; column < size_of_board;column++){
            if(board[row][column] == 1 && whose_action == 1){
                if(row+1 <= 7 &&  column-1 >= 0 && board[row+1][column-1] == 0){
                    legal_move[*what_number_legal_moves][0] = column;
                    legal_move[*what_number_legal_moves][1] = row;
                    legal_move[*what_number_legal_moves][2] = column - 1;
                    legal_move[*what_number_legal_moves][3] = row + 1;
                    *what_number_legal_moves += 1;
                }
                if(row+1 <= 7 &&  column+1 <= 7 && board[row+1][column+1] == 0){
                    legal_move[*what_number_legal_moves][0] = column;
                    legal_move[*what_number_legal_moves][1] = row;
                    legal_move[*what_number_legal_moves][2] = column + 1;
                    legal_move[*what_number_legal_moves][3] = row + 1;
                    *what_number_legal_moves += 1;
                }
                if(row+1 < 7 && column-1 > 0 && board[row+1][column-1]*board[row][column] < 0 && board[row+2][column-2] == 0){
                    legal_attack[*what_number_legal_attacks][0] = column;
                    legal_attack[*what_number_legal_attacks][1] = row;
                    legal_attack[*what_number_legal_attacks][2] = column - 2;
                    legal_attack[*what_number_legal_attacks][3] = row + 2;
                    *what_number_legal_attacks += 1;
                }
                if(row+1 < 7 && column+1 < 7 && board[row+1][column-1]*board[row][column] < 0 && board[row+2][column-2] == 0){
                    legal_attack[*what_number_legal_attacks][0] = column;
                    legal_attack[*what_number_legal_attacks][1] = row;
                    legal_attack[*what_number_legal_attacks][2] = column + 2;
                    legal_attack[*what_number_legal_attacks][3] = row + 2;
                    *what_number_legal_attacks += 1;
                }
            }
            else if(board[row][column] == -1 && whose_action == -1){
                if(row-1 >= 0 &&  column-1 >= 0 && board[row-1][column-1] == 0){
                    legal_move[*what_number_legal_moves][0] = column;
                    legal_move[*what_number_legal_moves][1] = row;
                    legal_move[*what_number_legal_moves][2] = column - 1;
                    legal_move[*what_number_legal_moves][3] = row - 1;
                    *what_number_legal_moves += 1;
                }
                if(row-1 >= 0 &&  column+1 <= 7 && board[row-1][column+1] == 0){
                    legal_move[*what_number_legal_moves][0] = column;
                    legal_move[*what_number_legal_moves][1] = row;
                    legal_move[*what_number_legal_moves][2] = column + 1;
                    legal_move[*what_number_legal_moves][3] = row - 1;
                    *what_number_legal_moves += 1;
                }
                if(row-1 > 0 && column-1 > 0 && board[row-1][column-1]*board[row][column] < 0 && board[row-2][column-2] == 0){
                    legal_attack[*what_number_legal_attacks][0] = column;
                    legal_attack[*what_number_legal_attacks][1] = row;
                    legal_attack[*what_number_legal_attacks][2] = column - 2;
                    legal_attack[*what_number_legal_attacks][3] = row - 2;
                    *what_number_legal_attacks += 1;
                }
                if(row-1 > 0 && column+1 < 7 && board[row-1][column-1]*board[row][column] < 0 && board[row-2][column-2] == 0){
                    legal_attack[*what_number_legal_attacks][0] = column;
                    legal_attack[*what_number_legal_attacks][1] = row;
                    legal_attack[*what_number_legal_attacks][2] = column + 2;
                    legal_attack[*what_number_legal_attacks][3] = row - 2;
                    *what_number_legal_attacks += 1;
                }
            }
        }
    }
}
