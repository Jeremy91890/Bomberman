#include "../headers/main.h"
#include "../headers/globals.h"
#include "../headers/menu.h"
#include "../headers/enter_ip.h"
#include "../headers/structs.h"
#include "../headers/server.h"
#include "../headers/map.h"
#include "../headers/socket.h"
#include "../headers/on_game.h"

int on_game(char *ip_text) {
    printf(ip_text);

    // creation du socket client
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }
    // --- end

    //Connection au server
    struct hostent *hostinfo = NULL;
    SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */
    const char *hostname = "127.0.0.1"; //ICI METTRE IP_TEXT POUR UTILISER L'IP ENTREE PAR LE USER

    hostinfo = gethostbyname(hostname); /* on récupère les informations de l'hôte auquel on veut se connecter */
    if (hostinfo == NULL) /* l'hôte n'existe pas */
    {
        fprintf (stderr, "Unknown host %s.\n", hostname);
        exit(EXIT_FAILURE);
    }

    sin.sin_addr = *(IN_ADDR *) hostinfo->h_addr; /* l'adresse se trouve dans le champ h_addr de la structure hostinfo */
    sin.sin_port = htons(PORT); /* on utilise htons pour le port */
    sin.sin_family = AF_INET;

    if(connect(sock,(SOCKADDR *) &sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
    {
        perror("connect()");
        exit(errno);
    }
    // --- end

    t_game game;

    if(send(sock, &game, sizeof(game), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }

    int n = 0;

    if((n = recv(sock, &game, sizeof(game), 0)) < 0)
    {
        perror("recv()");
        exit(errno);
    }

    display_map(game.map);
    display_character(game.player_infos);
    //A terme la fonction draw_map va devoir afficher tout quelque soit l'élement

    t_player_infos player;

    // On récupère le bon joueur dans la liste des joueurs connectés
    int i;
    printf("SOCKET \n %d", sock);
    printf("SOCKET player 0 \n %d", game.player_infos[0].socket);
    printf("SOCKET player 1 \n %d", game.player_infos[1].socket);
    printf("SOCKET player 2 \n %d", game.player_infos[2].socket);
    printf("SOCKET player 3 \n %d", game.player_infos[3].socket);

    for(i = 0; i < 4; i++) {
        if(game.player_infos[i].socket == sock) {
            player = game.player_infos[i];
            printf("i = \n %d", i);
            printf("first x pos \n%d", game.player_infos[i].x_pos);
        }
    }

    int running = 1;
    SDL_Event event;
    while (running)
    {
        //Dans ce block logique event, send action au serv, ...
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                closesocket(sock);
                return GO_QUIT;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                         printf("x pos \n%d", player.x_pos);
                         printf("y pos \n%d", player.y_pos);
                    
                         printf("x pos game \n%d", game.player_infos[0].x_pos);
                         printf("y pos game \n%d", game.player_infos[0].y_pos);
                        if(change_dir(&player, TOP) == 1) {
                            game.player_infos[0] = player;
                           // display_map(game.map);
                            display_character(game.player_infos);
                        }
                        printf("SDLK_UP");
                        break;
                    case SDLK_DOWN:
                        if(change_dir(&player, DOWN) == 1) {
                            game.player_infos[0] = player;
                            //display_map(game.map);
                            display_character(game.player_infos);
                        }
                        printf("SDLK_DOWN");
                        break;
                    default:
                        break;
                }
                break;
        }
        //Attention cette fonction bloque l'affichage car on est en attente de la réponse du serv
        /*if((n = recv(sock, &game, sizeof(game), 0)) < 0)
        {
            perror("recv()");
            exit(errno);
        }*/
    }

    closesocket(sock);

    return GO_QUIT;
}

// retourne 1 si la direction a changée
int change_dir(t_player_infos *player, int dir) {
    if(player->current_dir == dir) {
        return 0;
    }
    player->current_dir = dir;
    return 1;
}

// void move(int dir) {

// }