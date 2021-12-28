#include <stdio.h>
#include <stdlib.h>
#include "checkers_rules_and_logic.h"

const char *show_moves = "SHOWMOVES";
const char *surrender = "SURRENDER";

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
                if(row+1 < 7 && column+1 < 7 && board[row+1][column+1]*board[row][column] < 0 && board[row+2][column+2] == 0){
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
                if(row-1 > 0 && column+1 < 7 && board[row-1][column+1]*board[row][column] < 0 && board[row-2][column+2] == 0){
                    legal_attack[*what_number_legal_attacks][0] = column;
                    legal_attack[*what_number_legal_attacks][1] = row;
                    legal_attack[*what_number_legal_attacks][2] = column + 2;
                    legal_attack[*what_number_legal_attacks][3] = row - 2;
                    *what_number_legal_attacks += 1;
                }
            }
            else if(board[row][column] == 2 && whose_action*board[row][column] >= 0){
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
                if(row-1 > 0 && column+1 < 7 && board[row-1][column+1]*board[row][column] < 0 && board[row-2][column+2] == 0){
                    legal_attack[*what_number_legal_attacks][0] = column;
                    legal_attack[*what_number_legal_attacks][1] = row;
                    legal_attack[*what_number_legal_attacks][2] = column + 2;
                    legal_attack[*what_number_legal_attacks][3] = row - 2;
                    *what_number_legal_attacks += 1;
                }
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
                if(row+1 < 7 && column+1 < 7 && board[row+1][column+1]*board[row][column] < 0 && board[row+2][column+2] == 0){
                    legal_attack[*what_number_legal_attacks][0] = column;
                    legal_attack[*what_number_legal_attacks][1] = row;
                    legal_attack[*what_number_legal_attacks][2] = column + 2;
                    legal_attack[*what_number_legal_attacks][3] = row + 2;
                    *what_number_legal_attacks += 1;
                }
            }
        }
    }
}

void promotion(int **board, int size_of_board){
    for (int i = 0; i<size_of_board;i++) if (board[0][i] == -1) board[0][i] = -2;
    for (int i = 0; i<size_of_board;i++) if (board[size_of_board-1][i] == 1) board[0][i] = 2;
}

void move_action(int **board, int *coordinates){
    board[coordinates[3]][coordinates[2]] = board[coordinates[1]][coordinates[0]];
    board[coordinates[1]][coordinates[0]] = 0;
}

void attack_action(int **board, int *coordinates){
    int middle_row = (coordinates[3]+coordinates[1])/2;
    int middle_column = (coordinates[2]+coordinates[0])/2;
    board[coordinates[3]][coordinates[2]] = board[coordinates[1]][coordinates[0]];
    board[coordinates[1]][coordinates[0]] = 0;
    board[middle_row][middle_column] = 0;
}

int value_of_board(int **board,int size_of_board){
    int suma = 0;
    for(int i = 0; i < size_of_board; i++){
        for(int j = 0; j < size_of_board; j++) suma+= board[i][j];
    }
    return suma;
}

void who_is_winner(int **board,int size_of_board,int *end_the_game){
    int upper_player = 0;
    int bottom_player = 0;
    for(int i = 0; i < size_of_board; i++){
        for(int j = 0; j < size_of_board; j++){
            if (board[i][j]  < 0) bottom_player++;
            else if(board[i][j] > 0)upper_player++;
        }
    }
    if (bottom_player == 0){
        *end_the_game = 1;
        return;
    }
    if(upper_player == 0){
        *end_the_game = -1;
        return;
    }
    *end_the_game = 0;
}

int input_in_attack(int legal_attack[][4],int what_number_legal_attacks,int *input){
    for(int i = 0; i < what_number_legal_attacks;i++){
        if(legal_attack[i][0] == input[0] && legal_attack[i][1] == input[1] && legal_attack[i][2] == input[2] && legal_attack[i][3] == input[3]) return 1;
    }
    return 0;
}

int input_in_move(int legal_move[][4],int what_number_legal_move,int *input){
    for(int i = 0; i < what_number_legal_move;i++){
        if(legal_move[i][0] == input[0] && legal_move[i][1] == input[1] && legal_move[i][2] == input[2] && legal_move[i][3] == input[3]) return 1;
    }
    return 0;
}

int *read_move (int legal_attack[][4], int legal_move[][4],int what_number_legal_moves, int what_number_legal_attacks, int *correctness, char *entry){
    int *input = malloc(sizeof(int*)*4);
    int read_characters = 0;
    int sign = (int) entry[0];
    int iterat = 0;
    *correctness = 0;
    while(sign != '\n' && read_characters<5){
        if( 'A' <= sign && sign <= 'H') input[read_characters] = sign - 'A';
        if( 'a' <= sign && sign <= 'h') input[read_characters] = sign - 'a';
        if( '1' <= sign && sign <= '8') input[read_characters] = 7 - sign + '1';
        read_characters++;
        iterat++;
        sign = (int) entry[iterat];
    }
    if (read_characters < 3) return input;
    if (what_number_legal_attacks > 0 && input_in_attack(legal_attack,what_number_legal_attacks,input)) *correctness = 1;
    else if(what_number_legal_moves > 0 && input_in_move(legal_move,what_number_legal_moves,input)) *correctness = 1;
    return input;
}

void dynamic_array_of_chars(char *array, int *size){
    char *new_pointer = malloc(sizeof(char *)*(*size*2));
    for(int i = 0; i < *size; i++){
        new_pointer[i] = array[i];
    }
    array = new_pointer;
    *size = *size * 2;
}

void insert_to_dynamic_array(char *array, int *last_element, int *size, char what_to_insert){
    if(*last_element == *size){
        dynamic_array_of_chars(array,size);
    }
    array[*last_element] = what_to_insert;
    *last_element+=1;
}

int compare_arrays (char *array, const char *with_what_to_compare, int length){
    for(int i = 0; i < length; i++){
        if(array[i] != with_what_to_compare[i]) return 0;
    }
    return 1;
}

char *read_entry(int *operation){
    int size = 5;
    int last_element = 0;
    char *entry  = malloc(sizeof(char *)*size);
    int sign = getchar();
    while(sign != '\n'){
        if(sign != ' ')insert_to_dynamic_array(entry,&last_element,&size,(char)sign);
        sign = getchar();
    }
    insert_to_dynamic_array(entry,&last_element,&size,(char)sign);
    for (int i = 0; i < last_element;i++){
        if( 'a' <= entry[i] && entry[i] <= 'z') entry[i] = (char) ((int)entry[i] - 'a' + 'A');
    }
    if (compare_arrays(entry,show_moves,9)){
        *operation = 1;
        return entry;
    }
    if (compare_arrays(entry,surrender,9)){
        *operation = 2;
        return entry;
    }
    *operation = 3;
    return entry;
}
