#include "../headers/menu.h"
#include "../headers/globals.h"
#include "../headers/map.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../headers/generate_map.h"
#include "../headers/structs.h"

SDL_Surface *INFO_TEXT_BOMB_LEFT = NULL, *INFO_TEXT_GAME_STATE = NULL, *INFO_TEXT_RESULT_FIGHT = NULL;
SDL_Rect POS_INFO_TEXT_BOMB_LEFT, POS_INFO_TEXT_GAME_STATE, POS_INFO_TEXT_RESULT_FIGHT;

void display_bomb_left(t_player_infos *player_infos) {

    int width_text_bomb_left;
    char text_to_display[16];
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

void display_game_state(t_game *game) {
    int width_text_game_state;
    char text_to_display[8] = "waiting\0";

    if (game->game_state == 1) {
        strcpy(text_to_display,"fight");
    } else if (game->game_state == 2) {
        strcpy(text_to_display,"end");
    }

    TTF_SizeText(FONT, text_to_display, &width_text_game_state, NULL);

    POS_INFO_TEXT_GAME_STATE.x = 500;
    POS_INFO_TEXT_GAME_STATE.y = 836;

    INFO_TEXT_GAME_STATE = TTF_RenderText_Blended(FONT, text_to_display, COLOR_TEXT_INPUT);
    SDL_BlitSurface(INFO_TEXT_GAME_STATE, NULL, SCREEN, &POS_INFO_TEXT_GAME_STATE);

    SDL_Flip(SCREEN);
}

void display_result_fight(t_game *game, t_player_infos *player_infos) {
    int width_text_result_fight;
    char text_to_display[7] = "\0";

    if (game->game_state == 2 && player_infos->alive == 1) {
        strcpy(text_to_display,"winner");
    } else if (player_infos->alive == 0) {
        strcpy(text_to_display,"loser");
    }

    TTF_SizeText(FONT, text_to_display, &width_text_result_fight, NULL);

    POS_INFO_TEXT_RESULT_FIGHT.x = 650;
    POS_INFO_TEXT_RESULT_FIGHT.y = 836;

    INFO_TEXT_RESULT_FIGHT = TTF_RenderText_Blended(FONT, text_to_display, COLOR_TEXT_INPUT);
    SDL_BlitSurface(INFO_TEXT_RESULT_FIGHT, NULL, SCREEN, &POS_INFO_TEXT_RESULT_FIGHT);

    SDL_Flip(SCREEN);
}
