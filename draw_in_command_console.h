#ifndef DRAW_IN_COMMAND_CONSOLE_H_INCLUDED
#define DRAW_IN_COMMAND_CONSOLE_H_INCLUDED

void draw_map_of_game(int **map_of_game,int length_of_map, int size_of_line);
void show_legal_moves(int legal_move[][4], int legal_attack[][4],int what_number_legal_moves, int what_number_legal_attacks);
void draw_end(int winner);
#endif // DRAW_IN_COMMAND_CONSOLE_H_INCLUDED
