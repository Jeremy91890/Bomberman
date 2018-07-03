#include "../headers/server.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../headers/socket.h"
#include "../headers/generate_map.h"

void *main_server()
{
    SOCKET sock = init_connection();
    /* the index for the array */
    int actual = 0;
    int max = sock;

    fd_set rdfs;

    t_game game;
    init_map(game.map);
    int n = 0;
    while(n < sizeof(game.map)) {
        printf("%d ", game.map[n]);
        n = n + 1;
    }

    while(1) {
        int i = 0;
        FD_ZERO(&rdfs);

        /* add STDIN_FILENO */
        FD_SET(STDIN_FILENO, &rdfs);

        /* add the connection socket */
        FD_SET(sock, &rdfs);

        /* add socket of each client */
        for(i = 0; i < actual; i++) {
            FD_SET(game.player_infos[i].socket, &rdfs);
        }

        if(select(max + 1, &rdfs, NULL, NULL, NULL) == -1) {
            perror("select()");
            exit(errno);
        }

        /* something from standard input : i.e keyboard */
        if(FD_ISSET(STDIN_FILENO, &rdfs)) {
            /* stop process when type on keyboard */
            break;
        } else if(FD_ISSET(sock, &rdfs)) {
            /* new client */
            struct sockaddr_in csin = { 0 };
            socklen_t sinsize = sizeof(csin);
            int csock = accept(sock, (SOCKADDR *)&csin, &sinsize);
            if(csock == SOCKET_ERROR) {
                perror("accept()");
                continue;
            }

            /* after connecting the client sends its name */
            if(read_player(csock, game) == -1) {
                /* disconnected */
                continue;
            }

            /* what is the new maximum fd ? */
            max = csock > max ? csock : max;

            FD_SET(csock, &rdfs);

            printf("t_player_infos player_infos = add_new_player(actual); actual : ");
            printf("%d", actual);
            printf("\n");
            t_player_infos player_infos = add_new_player(actual);
            player_infos.socket = csock;
            game.player_infos[actual] = player_infos;
            
            actual++;
        } else {
            int i = 0;
            for(i = 0; i < actual; i++) {
                /* a client is talking */
                if(FD_ISSET(game.player_infos[i].socket, &rdfs)) {
                    int c = read_player(game.player_infos[i].socket, game);
                    /* client disconnected */
                    if(c == 0) {
                        //closesocket(clients[i].sock);
                        //remove_client(clients, i, &actual);
                        //strncpy(buffer, client.name, BUF_SIZE - 1);
                        //strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
                        send_game_to_all_players(actual, game);
                    } else {
                        send_game_to_all_players(actual, game);
                    }
                    break;
                }
            }
        }
    }

    //clear_clients(clients, actual);
    //end_connection(sock);

    printf("quit\n");
    //destroy the warning
    pthread_exit(NULL);
}

int init_connection()
{
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    SOCKADDR_IN sin = { 0 };

    if(sock == INVALID_SOCKET) {
        perror("socket()");
        exit(errno);
    }

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;

    if(bind(sock,(SOCKADDR *) &sin, sizeof sin) == SOCKET_ERROR) {
        perror("bind()");
        exit(errno);
    }

    if(listen(sock, MAX_PLAYERS) == SOCKET_ERROR) {
        perror("listen()");
        exit(errno);
    }

    return sock;
}

int read_player(SOCKET sock, t_game game)
{
    int n = 0;

    if((n = recv(sock, &game, sizeof(game) - 1, 0)) < 0) {
        perror("recv()");
        /* if recv error we disonnect the client */
        n = 0;
    }

    printf("player server \n %d", game.player_infos[0].x_pos);
    //game[n] = 0;

    return n;
}

void send_game_to_all_players(int actual, t_game game)
{
    printf("send game for all\n");

    int i = 0;

    for(i = 0; i < actual; i++) {
        printf("for(i = 0; i < actual; i++) de send game\n");
        write_player(game.player_infos[i].socket, game);
    }
}

void write_player(SOCKET sock, t_game game)
{
    printf("write player\n");
    if(send(sock, &game, sizeof(game), 0) < 0) {
        perror("send()");
        exit(errno);
    }
}


