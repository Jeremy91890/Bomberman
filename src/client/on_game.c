#include "../headers/main.h"
#include "../headers/globals.h"
#include "../headers/menu.h"
#include "../headers/enter_ip.h"
#include "../headers/structs.h"
#include "../headers/server.h"
#include "../headers/map.h"
#include "../headers/socket.h"
#include "../headers/on_game.h"
#include "../headers/infos.h"

pthread_t MAP_THREAD;

int on_game(char *ip_text)
{
    int actual_index;
    int i;
    int running;
    int n;

    size_t game_buff_length = 0;
    t_game *game;
    game = malloc(sizeof(t_game));
    if (game == NULL)
        return -1;
    game_buff_length += sizeof(t_game);

    //game_buff_length += sizeof(t_player_infos);

    t_player_infos player;

    running = 1;
    n = 0;

    SOCKET sock;

    // creation du socket client
    do {
        sock = socket(AF_INET, SOCK_STREAM, 0);
    } while (errno == EINTR);

    if (sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    //Connection au server
    struct hostent *hostinfo = NULL;
    SOCKADDR_IN sin = {0}; /* initialise la structure avec des 0 */
    //ICI METTRE IP_TEXT POUR UTILISER L'IP ENTREE PAR LE USER
    const char *hostname = ip_text;

    /* on récupère les informations de l'hôte auquel on veut se connecter */
    hostinfo = gethostbyname(hostname);
    /* l'hôte n'existe pas */
    if (hostinfo == NULL)
    {
        fprintf(stderr, "Unknown host %s.\n", hostname);
        exit(EXIT_FAILURE);
    }

    sin.sin_addr = *(IN_ADDR *)hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
    sin.sin_port = htons(PORT);                  /* on utilise htons pour le port */
    sin.sin_family = AF_INET;

    if (connect(sock, (SOCKADDR *)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        perror("connect()");
        exit(errno);
    }

    n = recv(sock, game, game_buff_length, 0);

    if (n < 0)
    {
        perror("recv()");
        exit(errno);
    }
    init_sprites();
    display_map(game->map);
    display_character(game->player_infos);
    //A terme la fonction draw_map va devoir afficher tout quelque soit l'élement

    for (i = 0; i < 4; i++)
    {
        // je fais sock + 1 juste pour que ça marche que pour le joueur 1 et pas rester bloqué,
        //il faut trouver le problème des sockets stockées dans la struct player_info
        if (game->player_infos[i].socket != 0)
        {
            actual_index = i;
        }
    }

    player = game->player_infos[actual_index];

    t_thread_params *args = malloc(sizeof(t_thread_params));
    args->sock = sock;
    args->game = game;
    args->game_size = game_buff_length;
    args->player = &player;
    args->actual_index = actual_index;

    if (pthread_create(&MAP_THREAD, NULL, map_update_process, args))
    {
        free(args);
        perror("pthread_create");
        return EXIT_FAILURE;
    }

    SDL_Event event;
    while (running)
    {
        //Dans ce block logique event, send action au serv, ...
        SDL_WaitEvent(&event);
        switch (event.type)
        {
        case SDL_QUIT:
            pthread_cancel(MAP_THREAD);
            closesocket(sock);
            return GO_QUIT;

        case SDL_KEYDOWN:
            switch (event.key.keysym.sym)
            {
            case SDLK_UP:
                dir_pressed(sock, &player, TOP);
                break;

            case SDLK_DOWN:
                dir_pressed(sock, &player, DOWN);
                break;

            case SDLK_LEFT:
                dir_pressed(sock, &player, LEFT);
                break;

            case SDLK_RIGHT:
                dir_pressed(sock, &player, RIGHT);
                break;

            case SDLK_SPACE:
                bomb_pressed(sock, &player);
                break;

            case SDLK_RETURN:
                enter_pressed(sock, &player);
                break;

            default:
                break;
            }

            break;
        }
    }

    if (pthread_join(MAP_THREAD, NULL))
    {
        perror("pthread_join");
        return EXIT_FAILURE;
    }
    closesocket(sock);

    return GO_QUIT;
}

void enter_pressed(int sock, t_player_infos *player)
{
    t_client_request *client_request;
    client_request = malloc(sizeof(t_client_request));
    client_request->command = 2;
    client_request->magic = player->socket;
    client_request->x_pos = player->x_pos;
    client_request->y_pos = player->y_pos;
    client_request->dir = player->current_dir;

    if (send(sock, client_request, sizeof(t_client_request), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }

    free(client_request);
}

void bomb_pressed(int sock, t_player_infos *player)
{
    // si le perso ne regarde deja dans direction on le fait avancer
    t_client_request *client_request;
    client_request = malloc(sizeof(t_client_request));
    client_request->x_pos = player->x_pos;
    client_request->y_pos = player->y_pos;
    client_request->dir = player->current_dir;
    client_request->magic = player->socket;
    client_request->command = 1;

    if (send(sock, client_request, sizeof(t_client_request), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }

    free(client_request);
}

// Quand une flèche est pressée
void dir_pressed(int sock, t_player_infos *player, int dir)
{
    // si le perso ne regarde deja dans direction on le fait avancer
    if (change_dir(player, dir) == 0)
    {
        move(player, dir);
    }
    t_client_request *client_request;
    client_request = malloc(sizeof(t_client_request));
    client_request->x_pos = player->x_pos;
    client_request->y_pos = player->y_pos;
    client_request->dir = player->current_dir;
    client_request->magic = player->socket;

    if (send(sock, client_request, sizeof(t_client_request), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }

    free(client_request);
}

// retourne 1 si la direction a changée
int change_dir(t_player_infos *player, int dir)
{
    if (player->current_dir == dir)
    {
        return 0;
    }
    player->current_dir = dir;
    return 1;
}

void move(t_player_infos *player, int dir)
{
    switch (dir)
    {
    case DOWN:
        player->y_pos += 1;
        break;
    case TOP:
        player->y_pos -= 1;
        break;
    case RIGHT:
        player->x_pos += 1;
        break;
    case LEFT:
        player->x_pos -= 1;
        break;
    default:
        break;
    }
}

void *map_update_process(void *args)
{
    t_thread_params *actual_args = args;

    while (actual_args->game->game_state != 2)
    {
        fd_set rdfs;

        FD_ZERO(&rdfs);
        FD_SET(actual_args->sock, &rdfs);

        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 1;

        int selectResult;

        do {
            selectResult = select(actual_args->sock + 1, &rdfs, NULL, NULL, &tv);
        } while (errno == EINTR);

        if (selectResult == -1) {
            perror("select()");
            exit(errno);
        }

        if (FD_ISSET(actual_args->sock, &rdfs))
        {
            int n = 0;

            n = recv(actual_args->sock, actual_args->game, actual_args->game_size, 0);

            if (n < 0)
            {
                perror("recv()");
                exit(errno);
            }
            *actual_args->player = actual_args->game->player_infos[actual_args->actual_index];
            display_map(actual_args->game->map);
            display_character(actual_args->game->player_infos);
            display_bomb_left(actual_args->player);
            display_game_state(actual_args->game);
            display_result_fight(actual_args->game, actual_args->player);
        }
    }

    free(actual_args);
    pthread_exit(NULL);
}
