#ifndef     _MAIN_H_
#define     _MAIN_H_

#include <sys/time.h>

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "server.h"
#include "structs.h"

void        init_globals();
int         on_server();
void        init_sprites();

#endif