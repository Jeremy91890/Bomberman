#ifndef     _ON_GAME_H_
#define     _ON_GAME_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "server.h"
#include "structs.h"

int         on_game(char *ip_text);
void        read_server(SOCKET sock, t_game *game);
int         change_dir(t_player_infos *player, int dir);
void        move(t_player_infos *player, int dir);
void        dir_pressed(int sock, t_player_infos *player, int dir);
void        bomb_pressed(int sock, t_player_infos *player);
void        enter_pressed(int sock, t_player_infos *player);
void        *map_update_process(void *args);
void        current_timestamp(char *s);

#endif
