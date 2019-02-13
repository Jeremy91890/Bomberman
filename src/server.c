#include "server.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "socket.h"
#include "generate_map.h"
#include "game.h"

t_bomb_timers bomb_timers;
t_flam_timers flam_timers;

size_t game_buff_length;

void *main_server()
{
    int sock = init_connection();
    /* the index for the array */
    int actual = 0;
    int max = sock;

    bomb_timers.number_of_bombs = 0;
    flam_timers.number_of_flams = 0;

    fd_set rdfs;
    fd_set wdfs;
    t_client_request *req;
    req = malloc(sizeof(t_client_request));

    t_game *game;
    game = malloc(sizeof(t_game));
    if (game == NULL)
        return NULL;
    game_buff_length += sizeof(t_game);

    //game_buff_length += sizeof(t_player_infos);

    // state à 0 pour dire que la partie n'a pas encore commencé
    game->game_state = 0;

    int i;
    for (i = 0; i < MAX_PLAYERS; i++)
    {
        game->player_infos[i].socket = 0;
    }

    init_map(game->map);

    while (1)
    {
        int i = 0;
        FD_ZERO(&rdfs);
        FD_ZERO(&wdfs);


        /* add STDIN_FILENO */
        //FD_SET(STDIN_FILENO, &rdfs);
        //FD_SET(STDIN_FILENO, &wdfs);

        /* add the connection socket */
        FD_SET(sock, &rdfs);
        FD_SET(sock, &wdfs);

        /* add socket of each client */
        for (i = 0; i < actual; i++)
        {
            FD_SET(game->player_infos[i].socket, &rdfs);
            FD_SET(game->player_infos[i].socket, &wdfs);
            // Check si le joueur est sur une flamme il meurt
            if (game->map[15 * game->player_infos[i].y_pos + game->player_infos[i].x_pos] == 0)
            {
                game->player_infos[i].alive = 0;
            }
        }

        /*struct timeval tv;
        tv.tv_sec = 60;
        tv.tv_usec = 0;*/
        struct timeval tv = {60, 0};

        if(select(max + 1, &rdfs, &wdfs, NULL, &tv) == SOCKET_ERROR) {
            #if defined WIN32
                printf("select() returned with error %d\n", WSAGetLastError());
            #else
                printf("select() returned with error");
            #endif
            exit(errno);
        }

        /* something from standard input : i.e keyboard */
        if (FD_ISSET(STDIN_FILENO, &rdfs))
        {
            /* stop process when type on keyboard */
            break;
        }
        else if (FD_ISSET(sock, &rdfs))
        {
            /* new client */
            struct sockaddr_in csin = {0};
            socklen_t sinsize = sizeof(csin);
            int csock = accept(sock, (SOCKADDR *)&csin, &sinsize);

            if (csock == SOCKET_ERROR)
            {
                perror("accept()");
                continue;
            }
            else if (actual >= MAX_PLAYERS || game->game_state != 0)
            {
                close(csock);
                continue;
            }

            /* what is the new maximum fd ? */
            max = csock > max ? csock : max;

            FD_SET(csock, &rdfs);

            t_player_infos player_infos = add_new_player(actual);
            player_infos.socket = csock;
            game->player_infos[actual] = player_infos;

            actual++;
            send_game_to_all_players(actual, game);
        }
        else
        {
            int i = 0;
            for (i = 0; i < actual; i++)
            {
                /* a client is talking */
                if (FD_ISSET(game->player_infos[i].socket, &rdfs))
                {
                    int n = 0;

                    n = recv(game->player_infos[i].socket, (char *)req, sizeof(t_client_request) - 1, 0);

                    if (n < 0)
                    {
                        perror("recv()");
                        /* if recv error we disonnect the client */
                        n = 0;
                    }

                    if (n != 0)
                    {
                        go_logique_server(game, i, req);
                    }

                    send_game_to_all_players(actual, game);
                    break;
                }

                int f = 1;

                for (f = 1; f <= flam_timers.number_of_flams; f++)
                {
                    //Temps actuel egal ou sup a l explosion prevu
                    if ((unsigned)time(NULL) >= flam_timers.flam_timer[f].display_time)
                    {

                        game->map[flam_timers.flam_timer[f].flam_index] = 0b00000111;

                        /* Ici logique explosion bombe puis renvois de la game aux client */
                        flam_timers.flam_timer[f] = flam_timers.flam_timer[f + 1];
                        int c;
                        for (c = f; c < flam_timers.number_of_flams; c++)
                        {
                            flam_timers.flam_timer[c] = flam_timers.flam_timer[c + 1];
                        }
                        flam_timers.number_of_flams = flam_timers.number_of_flams - 1;
                        send_game_to_all_players(actual, game);
                    }
                }
                //Ici check si bomb explose
                int b = 1;
                for (b = 1; b <= bomb_timers.number_of_bombs; b++)
                {
                    //Temps actuel egal ou sup a l explosion prevu
                    if ((unsigned)time(NULL) >= bomb_timers.bomb_timer[b].explosion_time)
                    {
                        game->map[bomb_timers.bomb_timer[b].bomb_index] = 0b00000111;

                        // Affichage du feu
                        int index;

                        index = bomb_timers.bomb_timer[b].bomb_index;
                        display_explosion(index, game->map, 3);

                        // Fin d'affichage du feu

                        /* Ici logique explosion bombe puis renvois de la game aux client */
                        bomb_timers.bomb_timer[b] = bomb_timers.bomb_timer[b + 1];
                        int c;
                        for (c = b; c < bomb_timers.number_of_bombs; c++)
                        {
                            bomb_timers.bomb_timer[c] = bomb_timers.bomb_timer[c + 1];
                        }
                        bomb_timers.number_of_bombs = bomb_timers.number_of_bombs - 1;
                        send_game_to_all_players(actual, game);
                    }
                }

                //Gestion fin partie
                if (game->game_state == 1)
                {
                    int i;
                    int n = 0;
                    for (i = 0; i < MAX_PLAYERS; i++)
                    {
                        if (game->player_infos[i].alive == 1)
                        {
                            n++;
                        }
                    }
                    if (n <= 1)
                    {
                        game->game_state = 2;
                        send_game_to_all_players(actual, game);
                    }
                }
                //fin gestion fin partie
            }
        }
    }

    //destroy the warning
    pthread_exit(NULL);
    return (NULL);
}

int init_connection()
{
    int s;
	struct sockaddr_in sin;
    

	if ((s = socket(PF_INET, SOCK_STREAM, 0)) == -1) {
		printf("error on socket\n");
		return (0);
	}
	# ifdef __WIN32__
		if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
				   &(char){ 1 }, sizeof(int)) < 0) {
		printf("error on win setsockopt\n");
		return (0);
	}
	# else
	if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR,
				   &(int){ 1 }, sizeof(int)) < 0) {
		printf("error on linux or mac setsockopt\n");
		return (0);
	}
	# endif
	sin.sin_family = AF_INET;
	sin.sin_port = htons(PORT);
	sin.sin_addr.s_addr = INADDR_ANY;
	if (bind(s, (struct sockaddr *) &sin, sizeof(sin)) == -1) {
		printf("error on bind\n");
		return (0);
	}
	if (listen(s, 10) == -1) {
		printf("error on listen\n");
		return (0);
	}
	return s;
}

int read_player(SOCKET sock, t_client_request *req)
{
    int n = 0;

    n = recv(sock, (char *)req, sizeof(t_client_request) - 1, 0);

    if (n < 0)
    {
        perror("recv()");
        /* if recv error we disonnect the client */
        n = 0;
    }

    return n;
}

void send_game_to_all_players(int actual, t_game *game)
{
    int i = 0;

    for (i = 0; i < actual; i++)
    {
        write_player(game->player_infos[i].socket, game);
    }
}

void write_player(SOCKET sock, t_game *game)
{
    if (send(sock, (char *)game, game_buff_length, 0) < 0)
    {
        perror("send()");
        exit(errno);
    }
}
