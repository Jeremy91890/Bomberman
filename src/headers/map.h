#ifndef _MAP_H_
#define _MAP_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "structs.h"

#define TILE_WIDTH 64 // hauteur et largeur des tiles.
#define TILE_HEIGHT 64

#define BMAN_WIDTH 64 // hauteur et largeur des tiles.
#define BMAN_HEIGHT 128

#define NB_BLOCS_WIDTH 15 // nombre a afficher en x et y
#define NB_BLOCS_HEIGHT 13

void display_map(t_game *game);
void display_character(t_game *game);

#endif