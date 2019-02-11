#ifndef _GAME_H_
#define _GAME_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "structs.h"

void go_logique_server(t_game *game, int actual, t_client_request *req);
void turn_player(t_game *game, int actual, t_client_request *req);
void move_player(t_game *game, int actual, t_client_request *req);
void place_bomb(t_game *game, int actual);
void start_game(t_game *game);
int get_nb_players(t_game *game);
void add_flames(int bomb_index, char *map, int max_index, int iterator);
void display_explosion(int bomb_index, char *map, int nb_case);

#endif
