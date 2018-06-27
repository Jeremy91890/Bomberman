#ifndef     _MAP_H_
#define     _MAP_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define TILE_WIDTH 64  // hauteur et largeur des tiles.
#define TILE_HEIGHT 64 

#define NB_BLOCS_WIDTH 15  // nombre a afficher en x et y
#define NB_BLOCS_HEIGHT 13

int        draw_map();
void       display_map(char map[],int nombre_blocs_largeur,int nombre_blocs_hauteur);

#endif