#include <stdio.h>
#include <stdlib.h>
#include "draw_in_command_console.h"
#include "checkers_rules_and_logic.h"
#include <unistd.h>
#include <time.h>

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
void draw_end(){
     #ifdef __linux__
        system("clear");
        system("gsettings reset org.gnome.desktop.interface text-scaling-factor");
    #endif // __linux_*/
}
