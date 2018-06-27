#include "./headers/main.h"
#include "./headers/globals.h"
#include "./headers/menu.h"
#include "./headers/enter_ip.h"
#include "../server/headers/server.h"
#include "./headers/map.h"
#include "../socket.h"

SDL_Surface *SCREEN;
TTF_Font *FONT;
pthread_t SERVER_THREAD;

int on_server() {
    if (pthread_create(&SERVER_THREAD, NULL, main_server, NULL)) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }
    return GO_MENU;
}

int on_game(int ip) {
    if (ip == 0) {
        //return on_enter_ip(&ip);
                create_client(ip);

    }
    else {
        create_client(ip);
    }
    return GO_QUIT;
}

void init_globals()
{
    setenv("SDL_VIDEO_CENTERED", "SDL_VIDEO_CENTERED", 1);
    
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SCREEN = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (SCREEN == NULL)
    {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    FONT = TTF_OpenFont("./resources/polices/04B_30__.TTF", 32);
}

int main(int argc, char *argv[])
{
    int run = 1;
    int NEXT_ACTION = GO_MENU;

    init_globals();

    while(run) {
        switch (NEXT_ACTION)
        {
            case GO_MENU:
                NEXT_ACTION = on_menu();
                break;
            case GO_GAME_JOIN:
                //NEXT_ACTION = draw_map();
                NEXT_ACTION = on_game(0);
                break;
            case GO_GAME_HOST:
                NEXT_ACTION = on_game(1);
                break;
            case GO_SERVER:
                NEXT_ACTION = on_server();
                break;
            case GO_QUIT:
                pthread_cancel(SERVER_THREAD);
                run = 0;
                break;
        }
    }
    if (pthread_join(SERVER_THREAD, NULL)) {
        perror("pthread_join");
        return EXIT_FAILURE;
    }

    TTF_CloseFont(FONT);
    TTF_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

void create_client(int ip) {
    
    // creation du socket client
    SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock == INVALID_SOCKET)
    {
        perror("socket()");
        exit(errno);
    }

    // Connexion au serveur
    struct hostent *hostinfo = NULL;
    SOCKADDR_IN sin = { 0 }; /* initialise la structure avec des 0 */
    const char *hostname = "www.developpez.com";

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

    // Envoie de données
    char buffer[1024];

    if(send(sock, buffer, strlen(buffer), 0) < 0)
    {
        perror("send()");
        exit(errno);
    }

    // Fermeture
    closesocket(sock);

}