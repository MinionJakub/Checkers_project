#include <stdio.h>
#include <stdlib.h>
#include "checkers_rules_and_logic.h"
#include <unistd.h>
#include <time.h>
#include "bot.h"
#include "draw_in_SDL.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <string.h>

const int SCREEN_HEIGHT = 800;
const int SCREEN_WIDTH = 800;

extern void dynamic_array_of_chars(char *array, int *size);

extern void insert_to_dynamic_array(char *array, int *last_element, int *size, char what_to_insert);

int game_SDL(int what_type_of_game)
{
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

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0){
        printf("Error of initialization: %s\n",SDL_GetError());
        return 1;
    }
    if(TTF_Init() != 0){
        printf("Error of initializing TTF: %s\n",TTF_GetError());
        return 1;
    }
    SDL_Window* mainWindow = SDL_CreateWindow("Checkers",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,0);
    if(!mainWindow){
        printf("Error of creating the main window: %s\n",SDL_GetError());
        SDL_Quit();
        return 2;
    }
    SDL_Renderer* mainRenderer = SDL_CreateRenderer(mainWindow,-1,SDL_RENDERER_ACCELERATED);
    if(!mainRenderer){
        printf("Error of creating the main renderer: %s\n",SDL_GetError());
        SDL_DestroyWindow(mainWindow);
        SDL_Quit();
        return 3;
    }

    int after_first_loop = 0;
    SDL_Rect pola[64];
    SDL_Rect rect_in_side[64];
    SDL_Rect rect_numbers[8];
    SDL_Rect rect_letters[8];
    SDL_Event event;
    SDL_Texture* white_pawn = IMG_LoadTexture(mainRenderer,"Assets/Chess_plt45.svg");
    SDL_Texture* black_pawn = IMG_LoadTexture(mainRenderer,"Assets/Chess_prt45.svg");
    SDL_Texture* white_king = IMG_LoadTexture(mainRenderer,"Assets/Chess_klt45.svg");
    SDL_Texture* black_king = IMG_LoadTexture(mainRenderer,"Assets/Chess_krt45.svg");
    SDL_Texture* numbers[8] = {IMG_LoadTexture(mainRenderer,"Assets/Number_1.svg"),IMG_LoadTexture(mainRenderer,"Assets/Number_2.svg"),IMG_LoadTexture(mainRenderer,"Assets/Number_3.svg"),
                                IMG_LoadTexture(mainRenderer,"Assets/Number_4.svg"),IMG_LoadTexture(mainRenderer,"Assets/Number_5.svg"),IMG_LoadTexture(mainRenderer,"Assets/Number_6.svg"),
                                IMG_LoadTexture(mainRenderer,"Assets/Number_7.svg"),IMG_LoadTexture(mainRenderer,"Assets/Number_8.svg")};
    SDL_Texture* letters[8] = {IMG_LoadTexture(mainRenderer,"Assets/Litera_A.svg"),IMG_LoadTexture(mainRenderer,"Assets/Litera_B.svg"),IMG_LoadTexture(mainRenderer,"Assets/Litera_C.svg"),
                                IMG_LoadTexture(mainRenderer,"Assets/Litera_D.svg"),IMG_LoadTexture(mainRenderer,"Assets/Litera_E.svg"),IMG_LoadTexture(mainRenderer,"Assets/Litera_F.svg"),
                                IMG_LoadTexture(mainRenderer,"Assets/Litera_G.svg"),IMG_LoadTexture(mainRenderer,"Assets/Litera_H.svg")};
    while(mainWindow != NULL && !end_the_game){
        while(SDL_PollEvent(&event)){
            if(event.type==SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE){

                if(SDL_GetWindowFromID(event.window.windowID) == mainWindow){
                    SDL_DestroyTexture(white_king);
                    SDL_DestroyTexture(black_king);
                    SDL_DestroyTexture(black_pawn);
                    SDL_DestroyTexture(white_pawn);
                    SDL_DestroyRenderer(mainRenderer);
                    SDL_DestroyWindow(mainWindow);
                    SDL_Quit();
                    return 0;
                }
            }
        }
        SDL_RenderClear( mainRenderer );
        for(int i = 0; i < 8;i++){
            for(int j = 0; j < 8; j++){
                pola[(i+1)*j].h = 80;
                pola[(i+1)*j].w = 80;
                pola[(i+1)*j].x = j*80+80;
                pola[(i+1)*j].y = i*80+80;
                if((i+j)%2)SDL_SetRenderDrawColor(mainRenderer,0,0,0,SDL_ALPHA_OPAQUE);
                else SDL_SetRenderDrawColor(mainRenderer,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
                SDL_RenderFillRect(mainRenderer,&pola[(i+1)*j]);
                SDL_RenderDrawRect(mainRenderer,&pola[(i+1)*j]);
            }
        }
        SDL_SetRenderDrawColor(mainRenderer,0,0,0,SDL_ALPHA_OPAQUE);
        for (int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                int c = (i+1)*j;
                rect_in_side[c].h = 45;
                rect_in_side[c].w = 45;
                rect_in_side[c].x = j*80+80+18;
                rect_in_side[c].y = i*80+18+80;
                if(board[i][j]== 1)SDL_RenderCopy(mainRenderer,black_pawn,NULL,&rect_in_side[c]);
                if(board[i][j]== 2)SDL_RenderCopy(mainRenderer,black_king,NULL,&rect_in_side[c]);
                if(board[i][j]== -1)SDL_RenderCopy(mainRenderer,white_pawn,NULL,&rect_in_side[c]);
                if(board[i][j]== -2)SDL_RenderCopy(mainRenderer,white_king,NULL,&rect_in_side[c]);
                if(board[i][j])SDL_RenderDrawRect(mainRenderer,&rect_in_side[c]);
            }
        }
        SDL_SetRenderDrawColor(mainRenderer,218,165,32,SDL_ALPHA_OPAQUE);
        for(int i = 0; i < 8;i++){
            rect_numbers[i].h = 50;
            rect_numbers[i].w = 50;
            rect_numbers[i].x = 10;
            rect_numbers[i].y = i*80+10+80;
            SDL_RenderCopy(mainRenderer,numbers[7-i],NULL,&rect_numbers[i]);
            SDL_RenderDrawRect(mainRenderer,&rect_numbers[i]);
        }
        for(int i = 0; i < 8; i++){
            rect_letters[i].h = 50;
            rect_letters[i].w = 50;
            rect_letters[i].x = 80+80*i+20;
            rect_letters[i].y = 80*8+20+80;
            SDL_RenderCopy(mainRenderer,letters[i],NULL,&rect_letters[i]);
            SDL_RenderDrawRect(mainRenderer,&rect_letters[i]);
        }

        legal_action(board,legal_attack,legal_move,8,&how_many_moves,&how_many_attacks,whose_turn);


        SDL_SetRenderDrawColor(mainRenderer,218,165,32,SDL_ALPHA_OPAQUE);
        SDL_RenderPresent( mainRenderer );
        SDL_Delay(2000);

        int size = 5;
        char *text = malloc(sizeof(char*)*size);
        int last_element = 0;
        for(int i = 0; i < size; i++){
            text[i] = 0;
        }

        if(after_first_loop){
            SDL_GetKeyboardState(NULL);
            TTF_Font* font;
            font = TTF_OpenFont("font.ttf",24);
            if(!font){
                printf("Failed to load font: %s\n",TTF_GetError());
            }
            SDL_Window* InputWindow = SDL_CreateWindow("Input",SDL_WINDOWPOS_CENTERED+2*SCREEN_WIDTH,SDL_WINDOWPOS_CENTERED,1000,100,0);
            int ending_loop = 0;
            if(!InputWindow){
                printf("Error of creating Input Window: %s\n",SDL_GetError());
            }
            else{
                SDL_Renderer* InputRenderer = SDL_CreateRenderer(InputWindow,-1,SDL_RENDERER_ACCELERATED);
                if(!InputRenderer || !font){
                    printf("Error of creating Input Renderer %s\n",SDL_GetError());
                    SDL_DestroyWindow(InputWindow);
                }
                else{
                    while(InputWindow && !ending_loop){
                        SDL_RenderClear(InputRenderer);
                        SDL_SetRenderDrawColor(InputRenderer,0xff,0xff,0xff,SDL_ALPHA_OPAQUE);
                        SDL_Texture* Uppet_text_texture;
                        SDL_Surface* Upper_text_print;
                        SDL_Color color = {0,0,0,SDL_ALPHA_OPAQUE};
                        Upper_text_print = TTF_RenderText_Solid(font,"Wprowadz ruch lub komende",color);
                        Uppet_text_texture = SDL_CreateTextureFromSurface(InputRenderer,Upper_text_print);
                        SDL_Rect Upper;
                        Upper.h = Upper_text_print->h;
                        Upper.w = Upper_text_print->w;
                        Upper.x = 0;
                        Upper.y = 0;
                        SDL_RenderCopy(InputRenderer,Uppet_text_texture,NULL,&Upper);
                        SDL_DestroyTexture(Uppet_text_texture);
                        SDL_FreeSurface(Upper_text_print);
                        //SDL_RenderPresent(InputRenderer);
                        while(SDL_PollEvent(&event)){
                            if(event.type==SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE){
                                if(SDL_GetWindowFromID(event.window.windowID) == mainWindow){
                                    SDL_DestroyTexture(white_king);
                                    SDL_DestroyTexture(black_king);
                                    SDL_DestroyTexture(black_pawn);
                                    SDL_DestroyTexture(white_pawn);
                                    SDL_DestroyRenderer(InputRenderer);
                                    SDL_DestroyWindow(InputWindow);
                                    SDL_DestroyRenderer(mainRenderer);
                                    SDL_DestroyWindow(mainWindow);
                                    SDL_Quit();
                                    return 0;
                                }
                                else if(SDL_GetWindowFromID(event.window.windowID) == InputWindow){
                                    SDL_DestroyRenderer(InputRenderer);
                                    SDL_DestroyWindow(InputWindow);
                                    ending_loop = 1;
                                }
                            }
                            else if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_BACKSPACE && last_element){
                                last_element--;
                                text[last_element] = 0;
                            }
                            else if(event.type == SDL_KEYDOWN && (event.key.keysym.sym == SDLK_ESCAPE || event.key.keysym.sym == SDLK_EXECUTE || event.key.keysym.sym == SDLK_KP_ENTER)){
                                SDL_DestroyRenderer(InputRenderer);
                                SDL_DestroyWindow(InputWindow);
                                ending_loop = 1;
                            }
                            else if(event.type == SDL_KEYDOWN){
                                char pom = (char) event.key.keysym.sym;
                                if(event.key.keysym.sym == '\n'){
                                    SDL_DestroyRenderer(InputRenderer);
                                    SDL_DestroyWindow(InputWindow);
                                    ending_loop = 1;
                                }
                                if(event.key.keysym.sym != SDLK_LSHIFT)insert_to_dynamic_array(text,&last_element,&size,pom);
                            }
                        }
                        if(last_element){
                            printf("%s\n",text);
                            SDL_Texture* text_texture;
                            SDL_Surface* text_print;
                            SDL_Color color = {0,0,0,SDL_ALPHA_OPAQUE};
                            text_print = TTF_RenderText_Solid(font,text,color);
                            text_texture = SDL_CreateTextureFromSurface(InputRenderer,text_print);
                            SDL_Rect dest;
                            dest.h = text_print->h;
                            dest.w = text_print->w;
                            dest.x = 0;
                            dest.y = 10+text_print->h;
                            SDL_RenderCopy(InputRenderer,text_texture,NULL,&dest);
                            SDL_DestroyTexture(text_texture);
                            SDL_FreeSurface(text_print);
                        }
                        SDL_RenderPresent(InputRenderer);
                        SDL_Delay(2000);
                    }
                }
            }
        }
        command = read_entry_from_text(&operation,text,last_element);
        if(operation == 2){
            end_the_game =-whose_turn;
            break;
        }
        else{
            action = read_move(legal_attack,legal_move,how_many_moves,how_many_attacks,&correctness,command);
        }
        SDL_Delay(2000/80/*1000/80*/);
        after_first_loop = 1;
    }
    return 0;
}
