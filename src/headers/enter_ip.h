#ifndef     _ENTER_IP_H_
#define     _ENTER_IP_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

int         on_enter_ip(char ip_text[]);
void        switch_enter_ip_color(int enter_ip_selection);
void        update_value_ip(char *ip_text, char *c);
void        refresh_text_ip(char *ip_text);
void        free_enter_ip(SDL_Surface *img_title, SDL_Surface *ENTER_IP_TEXT_IP, SDL_Surface *MENU_TEXT_PLAY, SDL_Surface *ENTER_IP_TEXT_BACK);

#endif