//Jakub Chomiczewski Projekt C

#include <stdio.h>
#include <stdlib.h>
#include "draw_in_command_console.h"
#include "checkers_rules_and_logic.h"
#include "bot.h"

int main()
{
    int mode = -1;
    while(mode){
        #ifdef __linux__
            system("clear");
        #endif // __linux__
        printf("Choose mode to play:\n");
        printf("(1)In console two players\n");
        printf("(2)In console player vs computer\n");
        printf("(0)Turn off program\n");
        if(mode == 1) {
            PvP_console();
            mode = -1;
        }
        if(mode == 2) {
            PvComputer_console();
            mode = -1;
        }
        scanf("%d",&mode);
    }
    exit(0);
}
