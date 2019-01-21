#ifndef     _MENU_H_
#define     _MENU_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

void        switch_menu_color(int menu_selection);
int         get_menu_event(int menu_selection);
void        free_menu(SDL_Surface *img_title, SDL_Surface *MENU_TEXT_PLAY, SDL_Surface *MENU_TEXT_SERVER, SDL_Surface *MENU_TEXT_QUIT);
int         on_menu();

#endif