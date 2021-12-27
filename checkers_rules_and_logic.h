#ifndef CHECKERS_RULES_AND_LOGIC_H_INCLUDED
#define CHECKERS_RULES_AND_LOGIC_H_INCLUDED

int **initiate();
void legal_action(int **board, int legal_attack[][4], int legal_move[][4], int size_of_board, int *what_number_legal_moves, int *what_number_legal_attacks, int whose_action);
#endif // CHECKERS_RULES_AND_LOGIC_H_INCLUDED
