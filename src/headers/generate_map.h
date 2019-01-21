#ifndef     _GENERATE_MAP_H_
#define     _GENERATE_MAP_H_

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

char get_random_destructable_bloc();
void delete_blocs_around_players(char map[], int pos[]);
void init_map(char map[]);

#endif