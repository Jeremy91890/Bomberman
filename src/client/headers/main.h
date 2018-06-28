#ifndef     _MAIN_H_
#define     _MAIN_H_

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include "../../server/headers/server.h"
#include "../../server/headers/structs.h"

void        init_globals();
int         on_server();
int         on_game(int ip);
void        create_client(int ip);
int         read_server(SOCKET sock, t_game game);
void        write_server(SOCKET sock, t_game game);

#endif