#ifndef _GENERATE_MAP_H_
#define _GENERATE_MAP_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "structs.h"

char get_random_destructable_bloc();
void delete_blocs_around_players(t_game *game, int pos[]);
void init_map(t_game *game);

#endif