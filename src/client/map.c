#include "./headers/menu.h"
#include "./headers/globals.h"
#include "./headers/map.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../server/headers/generate_map.h"
      
void Afficher(char map[],int nombre_blocs_largeur,int nombre_blocs_hauteur)
{
	int i,j;
    SDL_Surface *background_tile, *explodable_block, *solid_block;
	SDL_Rect Rect_dest;
	SDL_Rect Rect_source;
	Rect_source.w = LARGEUR_TILE;
	Rect_source.h = HAUTEUR_TILE;

    SDL_FillRect(SCREEN, NULL, 0x000000);
    
    printf("before i");
    int n = 0;

    background_tile = IMG_Load("./resources/sprites/blocks/BackgroundTile.png");
    explodable_block = IMG_Load("./resources/sprites/blocks/ExplodableBlock.png");
    solid_block = IMG_Load("./resources/sprites/blocks/SolidBlock.png");

	for(i=0;i<195;i+= 15)
	{
		for(j=0;j<15;j++)
		{
			Rect_dest.x = j*LARGEUR_TILE;
			Rect_dest.y = n*HAUTEUR_TILE;
			Rect_source.x = 0;
			Rect_source.y = 0;
            if (map[i+j] == 0b00000111) {
                // herbe
                printf("herbe");
                SDL_BlitSurface(background_tile, &Rect_source, SCREEN, &Rect_dest);
            }
            else if (map[i+j] == 0b01100111) {
                // destructible
                printf("dest");
                SDL_BlitSurface(explodable_block, &Rect_source, SCREEN, &Rect_dest);
            }
            else if (map[i+j] == 0b01000111) {
                // indestructible
                printf("indest");
                SDL_BlitSurface(solid_block, &Rect_source, SCREEN, &Rect_dest);
            }
		}
        n++;
	}
	SDL_Flip(SCREEN);
}

int draw_map()
{
    char map[195];
    int running = 1;
    SDL_Event event;
    init_map(map);

	Afficher(map,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR);
 
    while (running)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                return GO_QUIT;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                    case SDLK_UP:
                        printf("SDLK_UP");
                        break;
                    case SDLK_DOWN:
                        printf("SDLK_DOWN");
                        break;
                    default:
                        break;
                }
                break;
        }
    }
    return GO_QUIT;
}