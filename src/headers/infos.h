#ifndef     _INFO_H_
#define     _INFO_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "server.h"
#include "structs.h"

void display_bomb_left(t_player_infos *player_infos);
void display_game_state(t_game *game);
void display_result_fight(t_game *game, t_player_infos *player_infos);

#endif
