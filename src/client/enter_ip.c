#include "../headers/enter_ip.h"
#include "../headers/globals.h"

SDL_Surface *ENTER_IP_TEXT_IP = NULL, *ENTER_IP_TEXT_PLAY = NULL, *ENTER_IP_TEXT_BACK = NULL;
SDL_Rect POS_ENTER_IP_TEXT_IP, POS_ENTER_IP_TEXT_PLAY, POS_ENTER_IP_TEXT_BACK;

void switch_enter_ip_color(int enter_ip_selection)
{
    switch (enter_ip_selection)
    {
        case 0:
            ENTER_IP_TEXT_PLAY = TTF_RenderText_Blended(FONT, "Play", COLOR_TEXT_SELECTED);
            SDL_BlitSurface(ENTER_IP_TEXT_PLAY, NULL, SCREEN, &POS_ENTER_IP_TEXT_PLAY);

            ENTER_IP_TEXT_BACK = TTF_RenderText_Blended(FONT, "Back", COLOR_TEXT_UNSELECTED);
            SDL_BlitSurface(ENTER_IP_TEXT_BACK, NULL, SCREEN, &POS_ENTER_IP_TEXT_BACK);
            break;
        case 1:
            ENTER_IP_TEXT_PLAY = TTF_RenderText_Blended(FONT, "Play", COLOR_TEXT_UNSELECTED);
            SDL_BlitSurface(ENTER_IP_TEXT_PLAY, NULL, SCREEN, &POS_ENTER_IP_TEXT_PLAY);

            ENTER_IP_TEXT_BACK = TTF_RenderText_Blended(FONT, "Back", COLOR_TEXT_SELECTED);
            SDL_BlitSurface(ENTER_IP_TEXT_BACK, NULL, SCREEN, &POS_ENTER_IP_TEXT_BACK);
            break;
    }
    SDL_Flip(SCREEN);
}

void refresh_text_ip(char *ip_text)
{
    int width_text_ip;

    SDL_FillRect(SCREEN, &POS_ENTER_IP_TEXT_IP, 0x000000);
    TTF_SizeText(FONT, ip_text, &width_text_ip, NULL);

    POS_ENTER_IP_TEXT_IP.x = ((SCREEN_WIDTH / 2) - (width_text_ip / 2));
    
    ENTER_IP_TEXT_IP = TTF_RenderText_Blended(FONT, ip_text, COLOR_TEXT_INPUT);
    SDL_BlitSurface(ENTER_IP_TEXT_IP, NULL, SCREEN, &POS_ENTER_IP_TEXT_IP);

    SDL_Flip(SCREEN);
}

void free_enter_ip(SDL_Surface *img_title, SDL_Surface *ENTER_IP_TEXT_IP, SDL_Surface *ENTER_IP_TEXT_PLAY, SDL_Surface *ENTER_IP_TEXT_BACK) {
    SDL_FreeSurface(img_title);
    SDL_FreeSurface(ENTER_IP_TEXT_IP);
    SDL_FreeSurface(ENTER_IP_TEXT_PLAY);
    SDL_FreeSurface(ENTER_IP_TEXT_BACK);
}

void update_value_ip(char *ip_text, char *c) {
    if (strlen(ip_text) < 15) {
        strcat(ip_text, c);
    }
}

int on_enter_ip(char ip_text[]) {
    SDL_Surface *img_title = NULL;
    SDL_Rect pos_title;

    int width_text_ip, width_text_play, width_text_back;
    int running = 1;
    int enter_ip_selection = 0;

    SDL_FillRect(SCREEN, NULL, 0x000000);

    pos_title.x = ((SCREEN_WIDTH / 2) - (320 / 2));
    pos_title.y = 20;

    TTF_SizeText(FONT, "Enter an IP", &width_text_ip, NULL);
    POS_ENTER_IP_TEXT_IP.x = ((SCREEN_WIDTH / 2) - (width_text_ip / 2));
    POS_ENTER_IP_TEXT_IP.y = 160;

    TTF_SizeText(FONT, "Play", &width_text_play, NULL);
    POS_ENTER_IP_TEXT_PLAY.x = ((SCREEN_WIDTH / 2) - (width_text_play / 2));
    POS_ENTER_IP_TEXT_PLAY.y = 200;

    TTF_SizeText(FONT, "Back", &width_text_back, NULL);
    POS_ENTER_IP_TEXT_BACK.x = ((SCREEN_WIDTH / 2) - (width_text_back / 2));
    POS_ENTER_IP_TEXT_BACK.y = 240;

    img_title = IMG_Load("./resources/images/bomberman_title_320.png");
    SDL_BlitSurface(img_title, NULL, SCREEN, &pos_title);

    ENTER_IP_TEXT_IP = TTF_RenderText_Blended(FONT, "Enter an IP", COLOR_TEXT_INPUT);
    SDL_BlitSurface(ENTER_IP_TEXT_IP, NULL, SCREEN, &POS_ENTER_IP_TEXT_IP);

    
    ENTER_IP_TEXT_PLAY = TTF_RenderText_Blended(FONT, "Play", COLOR_TEXT_SELECTED);
    SDL_BlitSurface(ENTER_IP_TEXT_PLAY, NULL, SCREEN, &POS_ENTER_IP_TEXT_PLAY);

    ENTER_IP_TEXT_BACK = TTF_RenderText_Blended(FONT, "Back", COLOR_TEXT_UNSELECTED);
    SDL_BlitSurface(ENTER_IP_TEXT_BACK, NULL, SCREEN, &POS_ENTER_IP_TEXT_BACK);

    SDL_Flip(SCREEN);

    SDL_Event event;
 
    while (running)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                return GO_MENU;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        if (enter_ip_selection > 0)
                        {
                            enter_ip_selection -= 1;
                            switch_enter_ip_color(enter_ip_selection);
                        }
                        break;
                    case SDLK_DOWN:
                        if (enter_ip_selection < 1)
                        {
                            enter_ip_selection += 1;
                            switch_enter_ip_color(enter_ip_selection);
                        }
                        break;
                    case SDLK_RETURN:
                        switch (enter_ip_selection)
                        {
                            case 0:
                                printf("Go game join\n");
                                free_enter_ip(img_title, ENTER_IP_TEXT_IP, ENTER_IP_TEXT_PLAY, ENTER_IP_TEXT_BACK);
                                return GO_GAME_JOIN;
                            case 1:
                                printf("Go back to menu\n");
                                free_enter_ip(img_title, ENTER_IP_TEXT_IP, ENTER_IP_TEXT_PLAY, ENTER_IP_TEXT_BACK);
                                return GO_MENU;
                        }
                    case SDLK_KP_PERIOD:
                        update_value_ip(ip_text, ".");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP0:
                        update_value_ip(ip_text, "0");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP1:
                        update_value_ip(ip_text, "1");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP2:
                        update_value_ip(ip_text, "2");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP3:
                        update_value_ip(ip_text, "3");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP4:
                        update_value_ip(ip_text, "4");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP5:
                        update_value_ip(ip_text, "5");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP6:
                        update_value_ip(ip_text, "6");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP7:
                        update_value_ip(ip_text, "7");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP8:
                        update_value_ip(ip_text, "8");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_KP9:
                        update_value_ip(ip_text, "9");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_BACKSPACE:
                        ip_text[strlen(ip_text)-1] = '\0';
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_SEMICOLON:
                        update_value_ip(ip_text, ".");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_p:
                        update_value_ip(ip_text, "0");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_a:
                        update_value_ip(ip_text, "1");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_z:
                        update_value_ip(ip_text, "2");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_e:
                        update_value_ip(ip_text, "3");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_r:
                        update_value_ip(ip_text, "4");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_t:
                        update_value_ip(ip_text, "5");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_y:
                        update_value_ip(ip_text, "6");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_u:
                        update_value_ip(ip_text, "7");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_i:
                        update_value_ip(ip_text, "8");
                        refresh_text_ip(ip_text);
                        break;
                    case SDLK_o:
                        update_value_ip(ip_text, "9");
                        refresh_text_ip(ip_text);
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    return GO_MENU;
}