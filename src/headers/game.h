#ifndef     _GAME_H_
#define     _GAME_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "structs.h"

t_game go_logique_server(t_game game, int actual, t_client_request req);
t_game turn_player(t_game game, int actual, t_client_request req);
t_game move_player(t_game game, int actual, t_client_request req);
t_game place_bomb(t_game game, int actual, t_client_request req);

#endif
