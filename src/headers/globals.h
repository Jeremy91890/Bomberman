#ifndef     _GLOBALS_H_
#define     _GLOBALS_H_

#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <pthread.h>

//Global variables
extern SDL_Surface *SCREEN;
extern TTF_Font *FONT;
extern pthread_t SERVER_THREAD;

static const SDL_Color COLOR_TEXT_SELECTED = {255, 220, 0};
static const SDL_Color COLOR_TEXT_UNSELECTED = {255, 255, 255};
static const SDL_Color COLOR_TEXT_INPUT = {200, 200, 200};
static const int SCREEN_WIDTH = 960;
static const int SCREEN_HEIGHT = 892;

enum NEXT_ACTION {
    GO_MENU,
    GO_ENTER_IP,
    GO_GAME_JOIN,
    GO_GAME_HOST,
    GO_SERVER,
    GO_QUIT
};

#endif