#include <stdio.h>
#include <stdlib.h>
#include "draw_in_command_console.h"
#include "checkers_rules_and_logic.h"
#include <unistd.h>
#include <time.h>
#include "bot.h"

// king_piece_white = "\u2654";
// king_piece_black = "\u265A";
// man_piece_white = "\u2659";
// man_piece_black = "\u265F";
// bottom_lane = "\uFF3F";

void draw_map_of_game(int **map_of_game,int length_of_map, int size_of_line){
    #ifdef __linux__
        system("clear");
        system("gsettings set org.gnome.desktop.interface text-scaling-factor 2");
    #endif // __linux__*/
    for (int i = 0; i < length_of_map; i++){
        printf("%d ",8-i);
        for (int j = 0; j < size_of_line; j++){
            if(map_of_game[i][j] == 0)printf("_");
            else if(map_of_game[i][j] == 1) printf("\u2659");
            else if(map_of_game[i][j]==-1) printf("\u265F");
            else if (map_of_game[i][j]==2) printf("\u2654");
            else if (map_of_game[i][j]==-2)printf("\u265A");
        }
        putchar('\n');
    }
    printf("  ");
    for (int i = 0; i < 8; i++)putchar('A'+i);
    putchar('\n');
    /*#ifdef __linux__
        system("gsettings reset org.gnome.desktop.interface text-scaling-factor");
    #endif // __linux_*/
}

/*
legal_move[*what_number_legal_moves][0] = (char) 'A' + column;
legal_move[*what_number_legal_moves][1] = (char) '8' - row;
*/

void show_legal_moves(int legal_move[][4], int legal_attack[][4],int what_number_legal_moves, int what_number_legal_attacks){
    if (what_number_legal_attacks != 0){
        for (int i = 0; i < what_number_legal_attacks; i++){
            putchar('A'+legal_attack[i][0]);
            putchar('8'-legal_attack[i][1]);
            putchar('A'+legal_attack[i][2]);
            putchar('8'-legal_attack[i][3]);
            putchar('\n');
        }
        return;
    }
    for (int i = 0; i < what_number_legal_moves; i++){
            putchar('A'+legal_move[i][0]);
            putchar('8'-legal_move[i][1]);
            putchar('A'+legal_move[i][2]);
            putchar('8'-legal_move[i][3]);
            putchar('\n');
    }
}
void draw_end(int winner){
     #ifdef __linux__
        system("clear");
        system("gsettings reset org.gnome.desktop.interface text-scaling-factor");
    #endif // __linux_*/
    //printf("%d",winner);
    if(winner > 0)printf("Upper player is a winner");
    else if(winner < 0)printf("Bottom Player is a winner");
    else printf("Remis\n");
    /*#ifdef __linux__
        system("sleep 1");
    #endif // __linux__*/
}

void PvP_console(){
    int **board = initiate();
    int legal_attack[50][4];
    int legal_move[50][4];
    int how_many_moves = 0;
    int how_many_attacks = 0;
    int whose_turn = -1;
    if(time(NULL)%2) whose_turn = 1;
    int operation = 0;
    int end_the_game = 0;
    char *command;
    int correctness = 0;
    int *action;
    while(!end_the_game && operation != 2){
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
                int what_type_of_attack = -1;
                if (action[1]-action[3] < 0) what_type_of_attack = 1;
                continue_attack(board,action[3],action[2],legal_attack,&how_many_attacks,what_type_of_attack);
                while(how_many_attacks != 0){
                    if(how_many_attacks == 1){
                        attack_action(board,legal_attack[0]);
                        continue_attack(board,action[3],action[2],legal_attack,&how_many_attacks,what_type_of_attack);
                    }
                    else{
                        command = read_entry(&operation);
                        correctness = 0;
                        if(operation == 1) show_legal_moves(legal_move,legal_attack,how_many_moves,how_many_attacks);
                        else if(operation == 2){
                            end_the_game = -whose_turn;
                            //draw_end(end_the_game);
                            //printf("%d ",end_the_game);
                            //exit(0);
                        }
                        else{
                            action = read_move(legal_attack,legal_move,how_many_moves,how_many_attacks,&correctness,command);
                            if(correctness){
                                attack_action(board,action);
                                continue_attack(board,action[3],action[2],legal_attack,&how_many_attacks,what_type_of_attack);
                            }
                        }
                    }
                }
                whose_turn *= -1;
            }
            else if(correctness && how_many_moves){
                move_action(board,action);
                whose_turn *= -1;
            }
        }
        if(operation == 2){
            end_the_game = -whose_turn;
            break;
        }
        who_is_winner(board,8,&end_the_game);
    }
    free(board);
    draw_end(end_the_game);
    exit (0);
}

void PvComputer_console(){
    int **board = initiate();
    int legal_attack[50][4];
    int legal_move[50][4];
    int how_many_moves = 0;
    int how_many_attacks = 0;
    int whose_turn = -1;
    if (time(NULL)%2) whose_turn = 1;
    int operation = 0;
    int end_the_game = 0;
    char *command;
    int correctness = 0;
    int *action;
    while(!end_the_game && operation != 2){
        if(operation != 1)draw_map_of_game(board,8,8);
        //if(whose_turn == 1 && operation != 1)printf("Move has upper player\n");
        if(whose_turn == 1){
            legal_action(board,legal_attack,legal_move,8,&how_many_moves,&how_many_attacks,whose_turn);
            action = bot_make_decision(board,8,whose_turn,-1,1,10);
            if(how_many_attacks){
                attack_action(board,action);
                int what_type_of_attack = -1;
                if (action[1]-action[3] < 0) what_type_of_attack = 1;
                continue_attack(board,action[3],action[2],legal_attack,&how_many_attacks,what_type_of_attack);
                while(how_many_attacks){
                    attack_action(board,legal_attack[0]);
                    continue_attack(board,action[3],action[2],legal_attack,&how_many_attacks,what_type_of_attack);
                }
            }
            else if(how_many_moves && !how_many_attacks){
                move_action(board,action);
            }
            who_is_winner(board,8,&end_the_game);
            whose_turn *= -1;
        }
        else if(whose_turn == -1){
            if(operation != 2)printf("Your turn\n");
            legal_action(board,legal_attack,legal_move,8,&how_many_moves,&how_many_attacks,whose_turn);
            command = read_entry(&operation);
            if(operation == 1)show_legal_moves(legal_move,legal_attack,how_many_moves,how_many_attacks);
            else if(operation == 2) end_the_game = 1;
            else{
                correctness = 0;
                action = read_move(legal_attack,legal_move,how_many_moves,how_many_attacks,&correctness,command);
                if(correctness && how_many_attacks){
                    attack_action(board,action);
                    int what_type_of_attack = -1;
                    if (action[1]-action[3] < 0) what_type_of_attack = 1;
                    continue_attack(board,action[3],action[2],legal_attack,&how_many_attacks,what_type_of_attack);
                    while(how_many_attacks != 0){
                        if(how_many_attacks == 1){
                            attack_action(board,legal_attack[0]);
                            continue_attack(board,action[3],action[2],legal_attack,&how_many_attacks,what_type_of_attack);
                        }
                        else{
                            command = read_entry(&operation);
                            correctness = 0;
                            if(operation == 1) show_legal_moves(legal_move,legal_attack,how_many_moves,how_many_attacks);
                            else if(operation == 2){
                                end_the_game = -whose_turn;
                                //draw_end(end_the_game);
                                //printf("%d ",end_the_game);
                                //exit(0);
                            }
                            else{
                                action = read_move(legal_attack,legal_move,how_many_moves,how_many_attacks,&correctness,command);
                                if(correctness){
                                    attack_action(board,action);
                                    continue_attack(board,action[3],action[2],legal_attack,&how_many_attacks,what_type_of_attack);
                                }
                            }
                        }
                    }
                    whose_turn *= -1;
                }
                else if(correctness && how_many_moves){
                    move_action(board,action);
                    whose_turn *= -1;
                }
            }
            if(operation == 2){
                end_the_game = -whose_turn;
                break;
            }
            who_is_winner(board,8,&end_the_game);
        }
    }
    free(board);
    draw_end(end_the_game);
    exit (0);
}
