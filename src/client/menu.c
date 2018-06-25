#include "./headers/menu.h"
#include "./headers/globals.h"

//Global menu variables
SDL_Surface *MENU_TEXT_PLAY = NULL, *MENU_TEXT_SERVER = NULL, *MENU_TEXT_QUIT = NULL;
SDL_Rect POS_MENU_TEXT_PLAY, POS_MENU_TEXT_SERVER, POS_MENU_TEXT_QUIT;

void switch_menu_color(int menu_selection)
{
    switch (menu_selection)
    {
        case 0:
            MENU_TEXT_PLAY = TTF_RenderText_Blended(FONT, "Play", COLOR_TEXT_SELECTED);
            SDL_BlitSurface(MENU_TEXT_PLAY, NULL, SCREEN, &POS_MENU_TEXT_PLAY);

            MENU_TEXT_SERVER = TTF_RenderText_Blended(FONT, "Server", COLOR_TEXT_UNSELECTED);
            SDL_BlitSurface(MENU_TEXT_SERVER, NULL, SCREEN, &POS_MENU_TEXT_SERVER);

            MENU_TEXT_QUIT = TTF_RenderText_Blended(FONT, "Quit", COLOR_TEXT_UNSELECTED);
            SDL_BlitSurface(MENU_TEXT_QUIT, NULL, SCREEN, &POS_MENU_TEXT_QUIT);
            break;
        case 1:
            MENU_TEXT_PLAY = TTF_RenderText_Blended(FONT, "Play", COLOR_TEXT_UNSELECTED);
            SDL_BlitSurface(MENU_TEXT_PLAY, NULL, SCREEN, &POS_MENU_TEXT_PLAY);

            MENU_TEXT_SERVER = TTF_RenderText_Blended(FONT, "Server", COLOR_TEXT_SELECTED);
            SDL_BlitSurface(MENU_TEXT_SERVER, NULL, SCREEN, &POS_MENU_TEXT_SERVER);

            MENU_TEXT_QUIT = TTF_RenderText_Blended(FONT, "Quit", COLOR_TEXT_UNSELECTED);
            SDL_BlitSurface(MENU_TEXT_QUIT, NULL, SCREEN, &POS_MENU_TEXT_QUIT);
            break;
        case 2:
            MENU_TEXT_PLAY = TTF_RenderText_Blended(FONT, "Play", COLOR_TEXT_UNSELECTED);
            SDL_BlitSurface(MENU_TEXT_PLAY, NULL, SCREEN, &POS_MENU_TEXT_PLAY);

            MENU_TEXT_SERVER = TTF_RenderText_Blended(FONT, "Server", COLOR_TEXT_UNSELECTED);
            SDL_BlitSurface(MENU_TEXT_SERVER, NULL, SCREEN, &POS_MENU_TEXT_SERVER);

            MENU_TEXT_QUIT = TTF_RenderText_Blended(FONT, "Quit", COLOR_TEXT_SELECTED);
            SDL_BlitSurface(MENU_TEXT_QUIT, NULL, SCREEN, &POS_MENU_TEXT_QUIT);
            break;
    }
    SDL_Flip(SCREEN);
}

int get_menu_event(int menu_selection)
{
    int running = 1;
    SDL_Event event;
 
    while (running)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                return 2;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (menu_selection > 0)
                        {
                            menu_selection -= 1;
                            switch_menu_color(menu_selection);
                        }
                        break;
                    case SDLK_DOWN:
                        if (menu_selection < 2)
                        {
                            menu_selection += 1;
                            switch_menu_color(menu_selection);
                        }
                        break;
                    case SDLK_RETURN:
                        return menu_selection;
                    default:
                        break;
                }
                break;
        }
    }
    return 2;
}


void free_menu(SDL_Surface *img_title, SDL_Surface *MENU_TEXT_PLAY, SDL_Surface *MENU_TEXT_SERVER, SDL_Surface *MENU_TEXT_QUIT) {
    SDL_FreeSurface(img_title);
    SDL_FreeSurface(MENU_TEXT_PLAY);
    SDL_FreeSurface(MENU_TEXT_SERVER);
    SDL_FreeSurface(MENU_TEXT_QUIT);
}

int on_menu()
{
    SDL_Surface *img_title = NULL;
    SDL_Rect pos_title;

    int width_text_play, width_text_server, width_text_quit;
    int menu_selection = 0;

    SDL_FillRect(SCREEN, NULL, 0x000000);

    pos_title.x = ((SCREEN_WIDTH / 2) - (320 / 2));
    pos_title.y = 20;

    TTF_SizeText(FONT, "Play", &width_text_play, NULL);
    POS_MENU_TEXT_PLAY.x = ((SCREEN_WIDTH / 2) - (width_text_play / 2));
    POS_MENU_TEXT_PLAY.y = 160;

    TTF_SizeText(FONT, "Server", &width_text_server, NULL);
    POS_MENU_TEXT_SERVER.x = ((SCREEN_WIDTH / 2) - (width_text_server / 2));
    POS_MENU_TEXT_SERVER.y = 200;

    TTF_SizeText(FONT, "Quit", &width_text_quit, NULL);
    POS_MENU_TEXT_QUIT.x = ((SCREEN_WIDTH / 2) - (width_text_quit / 2));
    POS_MENU_TEXT_QUIT.y = 240;

    img_title = IMG_Load("./resources/images/bomberman_title_320.png");
    SDL_BlitSurface(img_title, NULL, SCREEN, &pos_title);

    MENU_TEXT_PLAY = TTF_RenderText_Blended(FONT, "Play", COLOR_TEXT_SELECTED);
    SDL_BlitSurface(MENU_TEXT_PLAY, NULL, SCREEN, &POS_MENU_TEXT_PLAY);

    MENU_TEXT_SERVER = TTF_RenderText_Blended(FONT, "Server", COLOR_TEXT_UNSELECTED);
    SDL_BlitSurface(MENU_TEXT_SERVER, NULL, SCREEN, &POS_MENU_TEXT_SERVER);

    MENU_TEXT_QUIT = TTF_RenderText_Blended(FONT, "Quit", COLOR_TEXT_UNSELECTED);
    SDL_BlitSurface(MENU_TEXT_QUIT, NULL, SCREEN, &POS_MENU_TEXT_QUIT);

    SDL_Flip(SCREEN);

    
    menu_selection = get_menu_event(menu_selection);

    switch (menu_selection)
    {
        case 0:
            printf("Go play\n");
            free_menu(img_title, MENU_TEXT_PLAY, MENU_TEXT_SERVER, MENU_TEXT_QUIT);
            return GO_GAME_JOIN;
        case 1:
            printf("Go server\n");
            free_menu(img_title, MENU_TEXT_PLAY, MENU_TEXT_SERVER, MENU_TEXT_QUIT);
            return GO_SERVER;
        case 2:
            printf("Go quit\n");
            free_menu(img_title, MENU_TEXT_PLAY, MENU_TEXT_SERVER, MENU_TEXT_QUIT);
            return GO_QUIT;
    }
    
    return GO_QUIT;
}