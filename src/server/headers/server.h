#ifndef     _SERVER_H_
#define     _SERVER_H_

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

#define PORT            8083
#define MAX_PLAYERS     4
#define MAP_SIZE        195

#include "structs.h"

void *main_server();
int init_connection();
t_player_infos add_new_player(int index);

#endif
