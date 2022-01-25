#ifndef CHECKERS_RULES_AND_LOGIC_H_INCLUDED
#define CHECKERS_RULES_AND_LOGIC_H_INCLUDED

int **initiate();
void legal_action(int **board, int legal_attack[][4], int legal_move[][4], int size_of_board, int *what_number_legal_moves, int *what_number_legal_attacks, int whose_action);
void promotion(int **board,int size_of_board);
void move_action(int **board,int *coordinates);
void attack_action(int **board, int *coordinates);
void who_is_winner(int **board,int size_of_board,int *end_the_game);
int *read_move (int legal_attack[][4], int legal_move[][4],int what_number_legal_moves, int what_number_legal_attacks, int *correctness,char *entry);
char *read_entry(int *operation);
void continue_attack(int **board, int row, int column, int legal_attack[][4],int *what_number_legal_attacks, int what_type_attack);
int value_of_board(int **board,int size_of_board);
char *read_entry_from_text(int *operation,char *text,int last_element);
#endif // CHECKERS_RULES_AND_LOGIC_H_INCLUDED
