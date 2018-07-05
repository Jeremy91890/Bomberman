#include "../headers/server.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../headers/socket.h"
#include "../headers/generate_map.h"
#include "../headers/game.h"

t_bomb_timers bomb_timers;
t_flam_timers flam_timers;

void *main_server()
{
    SOCKET sock = init_connection();
    /* the index for the array */
    int actual = 0;
    int max = sock;

    bomb_timers.number_of_bombs = 0;
    flam_timers.number_of_flams = 0;
    //bomb_timers.bomb_timer = malloc(bomb_timers.number_of_bombs * sizeof(bomb_timers.bomb_timer));

    /*t_bomb_timer bomb_timer;
    bomb_timer.bomb_index = 1;
    bomb_timer.explosion_time = 1;*/

    /*bomb_timers->number_of_bombs = 1;
    bomb_timers = malloc(bomb_timers->number_of_bombs * sizeof(t_bomb_timers));
    bomb_timers->bomb_timer[bomb_timers->number_of_bombs].bomb_index = 1;
    bomb_timers->bomb_timer[bomb_timers->number_of_bombs].explosion_time = 1;*/


    /*bomb_timers[1].bomb_index = 1;
    bomb_timers[1].explosion_time = 1;*/



    fd_set rdfs;
    t_client_request req;
    t_game game;
    // state à 0 pour dire que la partie n'a pas encore commencé
    game.game_state = 0;

    int i;
    for (i = 0 ; i < MAX_PLAYERS ; i++)
        game.player_infos[i].socket = 0;
    init_map(game.map);
    int n = 0;
    while(n < sizeof(game.map)) {
        printf("%d ", game.map[n]);
        n = n + 1;
    }

    while(1) {
        //printf("Viens !!\n");
        int i = 0;
        FD_ZERO(&rdfs);

        /* add STDIN_FILENO */
        FD_SET(STDIN_FILENO, &rdfs);

        /* add the connection socket */
        FD_SET(sock, &rdfs);

        /* add socket of each client */
        for(i = 0; i < actual; i++) {
            FD_SET(game.player_infos[i].socket, &rdfs);
            // Check si le joueur est sur une flamme il meurt
            if (game.map[15 * game.player_infos[i].y_pos + game.player_infos[i].x_pos] == 0) {
              game.player_infos[i].alive = 0;
            }
        }

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 1000;

        if(select(max + 1, &rdfs, NULL, NULL, &tv) == -1) {
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
            printf("server client Socket %d\n", sock);
            printf("server csock %d\n", csock);

            if(csock == SOCKET_ERROR) {
                perror("accept()");
                continue;
            }
            else if(actual >= MAX_PLAYERS || game.game_state != 0) {
                close(csock);
                continue;
            }

            /* after connecting the client sends its name */
            // if(read_player(csock, req) == -1) {
            //     /* disconnected */
            //     continue;
            // }

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
            send_game_to_all_players(actual, game);
        } else {
            int i = 0;
            for(i = 0; i < actual; i++) {
                /* a client is talking */
                if(FD_ISSET(game.player_infos[i].socket, &rdfs)) {
                    //int c = read_player(game.player_infos[i].socket, req);

                    printf("\ndir actual : %d\n", game.player_infos[i].current_dir);
                    printf("x actual : %d\n", game.player_infos[i].x_pos);
                    printf("y actual : %d\n\n", game.player_infos[i].y_pos);
                    int n = 0;
                    if((n = recv(game.player_infos[i].socket, &req, sizeof(req) - 1, 0)) < 0) {
                        perror("recv()");
                        /* if recv error we disonnect the client */
                        n = 0;
                    }
                    printf("\ndir wanted : %d\n", req.dir);
                    printf("x wanted : %d\n", req.x_pos);
                    printf("y wanted : %d\n\n", req.y_pos);
                    /* client disconnected */
                    if(n == 0) {
                        //closesocket(clients[i].sock);
                        //remove_client(clients, i, &actual);
                        //strncpy(buffer, client.name, BUF_SIZE - 1);
                        //strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
                    } else {
                        game = go_logique_server(game, i, req);
                    }
                    send_game_to_all_players(actual, game);
                    break;
                }

                int f = 1;

                for (f = 1; f <= flam_timers.number_of_flams; f++) {
                    //Temps actuel egal ou sup a l explosion prevu
                    if ((unsigned)time(NULL) >= flam_timers.flam_timer[f].display_time) {

                        game.map[flam_timers.flam_timer[f].flam_index] = 0b00000111;

                        /*
                        Ici logique explosion bombe puis renvois de la game aux client
                        */
                        flam_timers.flam_timer[f] = flam_timers.flam_timer[f+1];
                        int c;
                        for (c = f; c < flam_timers.number_of_flams; c++) {
                            flam_timers.flam_timer[c] = flam_timers.flam_timer[c + 1];
                        }
                        flam_timers.number_of_flams = flam_timers.number_of_flams - 1;
                        send_game_to_all_players(actual, game);
                    }
                }
                //Ici check si bomb explose
                int b = 1;
                //printf("%d\n", bomb_timers.bomb_timer[1].explosion_time);
                //printf("%d\n", bomb_timers.bomb_timer[2].explosion_time);
                //printf("AVENT FOR\n");
                //int nb_bombs = bomb_timers.number_of_bombs;
                for (b = 1; b <= bomb_timers.number_of_bombs; b++) {
                    //Temps actuel egal ou sup a l explosion prevu
                    if ((unsigned)time(NULL) >= bomb_timers.bomb_timer[b].explosion_time) {
                        //printf("EXPLOOOOOOOOOOSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSSIONSSSS\n");
                        fprintf(stdout, "%u\n", (unsigned)time(NULL));
                        printf("%d", bomb_timers.bomb_timer[b].explosion_time);
                        //bomb_timers.bomb_timer = realloc(bomb_timers.bomb_timer, bomb_timers.number_of_bombs * sizeof(bomb_timers.bomb_timer));
                        game.map[bomb_timers.bomb_timer[b].bomb_index] = 0b00000111;

                        // Affichage du feu
                        int index;

                        index = bomb_timers.bomb_timer[b].bomb_index;
                        display_explosion(index, game.map, 3);

                        // Fin d'affichage du feu

                        /*
                        Ici logique explosion bombe puis renvois de la game aux client
                        */
                        bomb_timers.bomb_timer[b] = bomb_timers.bomb_timer[b+1];
                        int c;
                        for (c = b; c < bomb_timers.number_of_bombs; c++) {
                            bomb_timers.bomb_timer[c] = bomb_timers.bomb_timer[c + 1];
                        }
                        bomb_timers.number_of_bombs = bomb_timers.number_of_bombs - 1;
                        send_game_to_all_players(actual, game);
                    }
                }

                //Gestion fin partie
                if (game.game_state == 1) {
                    int i;
                    int n = 0;
                    for (i = 0; i < MAX_PLAYERS; i++) {
                        if (game.player_infos[i].alive == 1) {
                            n++;
                        }
                    }
                    if (n <= 1) {
                        game.game_state = 2;
                        send_game_to_all_players(actual, game);
                    }
                }
                //fin gestion fin partie
            }
        }
        //printf("Pars !!\n");
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

int read_player(SOCKET sock, t_client_request req)
{
    int n = 0;

    if((n = recv(sock, &req, sizeof(req) - 1, 0)) < 0) {
        perror("recv()");
        /* if recv error we disonnect the client */
        n = 0;
    }
    //printf("player server \n %d", game.player_infos[0].x_pos);
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
