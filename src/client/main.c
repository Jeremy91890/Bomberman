#include "../headers/main.h"
#include "../headers/globals.h"
#include "../headers/menu.h"
#include "../headers/enter_ip.h"
#include "../headers/structs.h"
#include "../headers/server.h"
#include "../headers/map.h"
#include "../headers/socket.h"
#include "../headers/on_game.h"

SDL_Surface *SCREEN;
TTF_Font *FONT;
pthread_t SERVER_THREAD;

int on_server() {
    if (pthread_create(&SERVER_THREAD, NULL, main_server, NULL)) {
        perror("pthread_create");
        return EXIT_FAILURE;
    }
    //On sleep 1 seconde pour laisser le temps au server de d'init
    //Si pas assez mettre 2
    sleep(1);
    return GO_GAME_HOST;
}

void init_globals()
{
    setenv("SDL_VIDEO_CENTERED", "SDL_VIDEO_CENTERED", 1);
    
    if (SDL_Init(SDL_INIT_VIDEO) == -1) {
        fprintf(stderr, "Erreur d'initialisation de la SDL : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SCREEN = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    if (SCREEN == NULL) {
        fprintf(stderr, "Impossible de charger le mode vidéo : %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if(TTF_Init() == -1) {
        fprintf(stderr, "Erreur d'initialisation de TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }
    FONT = TTF_OpenFont("./resources/polices/04B_30__.TTF", 32);
}

int main(int argc, char *argv[])
{
    int run = 1;
    int NEXT_ACTION = GO_MENU;
    char ip_text[16] = "\0";

    init_globals();

    while(run) {
        switch (NEXT_ACTION) 
        {
            case GO_MENU:
                NEXT_ACTION = on_menu();
                break;
            case GO_ENTER_IP:
                NEXT_ACTION = on_enter_ip(ip_text);
                break;
            case GO_GAME_JOIN:
                //NEXT_ACTION = draw_map();
                NEXT_ACTION = on_game(ip_text);
                break;
            case GO_GAME_HOST:
                NEXT_ACTION = on_game("127.0.0.1");
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
