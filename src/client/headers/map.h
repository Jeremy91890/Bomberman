#ifndef     _MAP_H_
#define     _MAP_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#define LARGEUR_TILE 64  // hauteur et largeur des tiles.
#define HAUTEUR_TILE 64 

#define NOMBRE_BLOCS_LARGEUR 15  // nombre a afficher en x et y
#define NOMBRE_BLOCS_HAUTEUR 13

int        draw_map();
void       display_map(char map[],int nombre_blocs_largeur,int nombre_blocs_hauteur);

#endif