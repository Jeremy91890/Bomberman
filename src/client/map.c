#include "../headers/menu.h"
#include "../headers/globals.h"
#include "../headers/map.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../headers/generate_map.h"
#include "../headers/structs.h"

void display_map(char map[])
{
	int i,j;
    SDL_Surface *background_tile, *explodable_block, *solid_block, *bomb_block, *fire_block;
	SDL_Rect Rect_dest;
	SDL_Rect Rect_source;
	Rect_source.w = TILE_WIDTH;
	Rect_source.h = TILE_HEIGHT;

    SDL_FillRect(SCREEN, NULL, 0x000000);

    int n = 0;

    background_tile = IMG_Load("./resources/sprites/blocks/BackgroundTile.png");
    explodable_block = IMG_Load("./resources/sprites/blocks/ExplodableBlock.png");
    solid_block = IMG_Load("./resources/sprites/blocks/SolidBlock.png");
    bomb_block = IMG_Load("./resources/sprites/bomb/Bomb_f01.png");
    fire_block = IMG_Load("./resources/sprites/flame/Flame_f00.png");

	for(i=0;i<195;i+= 15)
	{
		for(j=0;j<15;j++)
		{
			Rect_source.x = 0;
			Rect_source.y = 0;
            Rect_dest.x = j*TILE_WIDTH;
			Rect_dest.y = n*TILE_HEIGHT;
            if (map[i+j] == 0b00000111) {
                // ground
                SDL_BlitSurface(background_tile, &Rect_source, SCREEN, &Rect_dest);
            }
            else if (map[i+j] == 0b01100111) {
                // destructable
                SDL_BlitSurface(explodable_block, &Rect_source, SCREEN, &Rect_dest);
            }
            else if (map[i+j] == 0b01000111) {
                // undestructable
                SDL_BlitSurface(solid_block, &Rect_source, SCREEN, &Rect_dest);
            }
            else if (map[i+j] == 0b00010111) {
                // bomb sur case
                SDL_BlitSurface(background_tile, &Rect_source, SCREEN, &Rect_dest);
                Rect_dest.x =  Rect_dest.x + 8;
                Rect_dest.y = Rect_dest.y + 8;
                SDL_BlitSurface(bomb_block, &Rect_source, SCREEN, &Rect_dest);
            }
            else if (map[i+j] == 0) {
                // case en flamme
                //printf("FFFFFFFFFFFFFFFFFFFFFFLLLLLLLLLLLLLLLLLLLLLAAAAAAAAAAAAAAAAAAAAMMMMMMMMMMMMMMMMMMMMMMMMMMMMEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE");
                SDL_BlitSurface(background_tile, &Rect_source, SCREEN, &Rect_dest);
                Rect_dest.x =  Rect_dest.x + 8;
                Rect_dest.y = Rect_dest.y + 8;
                SDL_BlitSurface(fire_block, &Rect_source, SCREEN, &Rect_dest);
            }
		}
        n++;
	}
	SDL_Flip(SCREEN);
}

void display_character(t_player_infos *player_infos)
{
    SDL_Surface *sprite_Bman_01_B, *sprite_Bman_01_F, *sprite_Bman_01_L, *sprite_Bman_01_R;
    SDL_Surface *sprite_Bman_02_B, *sprite_Bman_02_F, *sprite_Bman_02_L, *sprite_Bman_02_R;
    SDL_Surface *sprite_Bman_03_B, *sprite_Bman_03_F, *sprite_Bman_03_L, *sprite_Bman_03_R;
    SDL_Surface *sprite_Bman_04_B, *sprite_Bman_04_F, *sprite_Bman_04_L, *sprite_Bman_04_R;
    SDL_Rect Rect_dest;

    //A terme -> mettre dans un init et en global pour pas avoir à les recharger
    sprite_Bman_01_B = IMG_Load("./resources/sprites/bomberman/Back/Bman01_B_f00.png");
    sprite_Bman_01_F = IMG_Load("./resources/sprites/bomberman/Front/Bman01_F_f00.png");
    sprite_Bman_01_L = IMG_Load("./resources/sprites/bomberman/Left/Bman01_L_f00.png");
    sprite_Bman_01_R = IMG_Load("./resources/sprites/bomberman/Right/Bman01_R_f00.png");

    sprite_Bman_02_B = IMG_Load("./resources/sprites/bomberman/Back/Bman02_B_f00.png");
    sprite_Bman_02_F = IMG_Load("./resources/sprites/bomberman/Front/Bman02_F_f00.png");
    sprite_Bman_02_L = IMG_Load("./resources/sprites/bomberman/Left/Bman02_L_f00.png");
    sprite_Bman_02_R = IMG_Load("./resources/sprites/bomberman/Right/Bman02_R_f00.png");

    sprite_Bman_03_B = IMG_Load("./resources/sprites/bomberman/Back/Bman03_B_f00.png");
    sprite_Bman_03_F = IMG_Load("./resources/sprites/bomberman/Front/Bman03_F_f00.png");
    sprite_Bman_03_L = IMG_Load("./resources/sprites/bomberman/Left/Bman03_L_f00.png");
    sprite_Bman_03_R = IMG_Load("./resources/sprites/bomberman/Right/Bman03_R_f00.png");

    sprite_Bman_04_B = IMG_Load("./resources/sprites/bomberman/Back/Bman04_B_f00.png");
    sprite_Bman_04_F = IMG_Load("./resources/sprites/bomberman/Front/Bman04_F_f00.png");
    sprite_Bman_04_L = IMG_Load("./resources/sprites/bomberman/Left/Bman04_L_f00.png");
    sprite_Bman_04_R = IMG_Load("./resources/sprites/bomberman/Right/Bman04_R_f00.png");

    int i = 0;
    while(i < (MAX_PLAYERS)) {
        //printf("enter while affichage players : %d\n", player_infos[i].connected);

        //Un switch bien moche -> a terme le decouper
        switch(i) {
            case 0:
                //printf("case 0\n");
                switch(player_infos[i].current_dir) {
                    case 1:
                        //printf("player info x pos : %d\n", player_infos[i].x_pos);
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_01_R, NULL, SCREEN, &Rect_dest);
                        break;
                    case 2:
                                            //printf("player info x pos : %d\n", player_infos[i].x_pos);
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_01_F, NULL, SCREEN, &Rect_dest);
                        break;
                    case 3:
                                            //printf("player info x pos : %d\n", player_infos[i].x_pos);

                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_01_L, NULL, SCREEN, &Rect_dest);
                        break;
                    case 4:
                                            //printf("player info x pos : %d\n", player_infos[i].x_pos);

                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_01_B, NULL, SCREEN, &Rect_dest);
                        break;
                    default:
                        break;
                }
                break;
            case 1:
                //printf("case 1\n");
                switch(player_infos[i].current_dir) {
                    case 1:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_02_R, NULL, SCREEN, &Rect_dest);
                        break;
                    case 2:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_02_F, NULL, SCREEN, &Rect_dest);
                        break;
                    case 3:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_02_L, NULL, SCREEN, &Rect_dest);
                        break;
                    case 4:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_02_B, NULL, SCREEN, &Rect_dest);
                        break;
                    default:
                        break;
                }
                break;
            case 2:
                //printf("case 2\n");
                switch(player_infos[i].current_dir) {
                    case 1:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_03_R, NULL, SCREEN, &Rect_dest);
                        break;
                    case 2:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_03_F, NULL, SCREEN, &Rect_dest);
                        break;
                    case 3:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_03_L, NULL, SCREEN, &Rect_dest);
                        break;
                    case 4:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_03_B, NULL, SCREEN, &Rect_dest);
                        break;
                    default:
                        break;
                }
                break;
            case 3:
                //printf("case 3\n");
                switch(player_infos[i].current_dir) {
                    case 1:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_04_R, NULL, SCREEN, &Rect_dest);
                        break;
                    case 2:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_04_F, NULL, SCREEN, &Rect_dest);
                        break;
                    case 3:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_04_L, NULL, SCREEN, &Rect_dest);
                        break;
                    case 4:
                        Rect_dest.x = player_infos[i].x_pos * BMAN_WIDTH;
			            Rect_dest.y = (player_infos[i].y_pos * (BMAN_HEIGHT / 2)) - (BMAN_HEIGHT / 2);
                        SDL_BlitSurface(sprite_Bman_04_B, NULL, SCREEN, &Rect_dest);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
        i = i + 1;
    }
    SDL_Flip(SCREEN);
}
