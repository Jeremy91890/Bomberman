#ifndef _SERVER_H_
#define _SERVER_H_

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <errno.h>
#include "socket.h"

#define PORT 8083

#define FLAME_SEC 1
#define BOMB_SEC 5

#include "structs.h"

extern t_flam_timers flam_timers;
extern t_bomb_timers bomb_timers;

void *main_server();
int init_connection();
t_player_infos add_new_player(int index);
int read_player(SOCKET sock, t_client_request *req);
void send_game_to_all_players(int actual, t_game *game);
void write_player(SOCKET sock, t_game *game);

#endif
