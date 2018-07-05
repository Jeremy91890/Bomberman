#include "../headers/menu.h"
#include "../headers/globals.h"
#include "../headers/map.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../headers/generate_map.h"
#include "../headers/structs.h"

SDL_Surface *INFO_TEXT_BOMB_LEFT = NULL;
SDL_Rect POS_INFO_TEXT_BOMB_LEFT;

void display_bomb_left(t_player_infos *player_infos) {

    int width_text_bomb_left;
    char text_to_display[14];
    char char_bomb_left[4];
    
    
    sprintf(char_bomb_left,"%d",player_infos->bombs_left);
    
    strcpy(text_to_display, "Bomb left : ");
    strcat(text_to_display, char_bomb_left);

    TTF_SizeText(FONT, text_to_display, &width_text_bomb_left, NULL);

    POS_INFO_TEXT_BOMB_LEFT.x = 14;
    POS_INFO_TEXT_BOMB_LEFT.y = 836;

    INFO_TEXT_BOMB_LEFT = TTF_RenderText_Blended(FONT, text_to_display, COLOR_TEXT_INPUT);
    SDL_BlitSurface(INFO_TEXT_BOMB_LEFT, NULL, SCREEN, &POS_INFO_TEXT_BOMB_LEFT);

    SDL_Flip(SCREEN);

}