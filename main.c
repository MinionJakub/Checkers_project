#include <stdio.h>
#include <stdlib.h>
#include "draw_in_command_console.h"
#include "checkers_rules_and_logic.h"

int main()
{
    int **board = initiate();
    draw_map_of_game(board,8,8);
    int legal_attack[50][4];
    int legal_move[50][4];
    int how_many_moves = 0;
    int how_many_attacks = 0;
    int whose_turn = -1;
    legal_action(board,legal_attack,legal_move,8,&how_many_moves,&how_many_attacks,whose_turn);
    show_legal_moves(legal_move,legal_attack,how_many_moves,how_many_attacks);
    move_action(board,legal_move[0]);
    putchar('\n');
    draw_map_of_game(board,8,8);
    exit (0);
}
