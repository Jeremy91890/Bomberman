#include "./headers/menu.h"
#include "./headers/globals.h"
#include "./headers/map.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "../server/headers/generate_map.h"
      
void Afficher(SDL_Surface* screen,char map[],int nombre_blocs_largeur,int nombre_blocs_hauteur)
{
	int i,j;
    SDL_Surface *tileset;
	SDL_Rect Rect_dest;
	SDL_Rect Rect_source;
	Rect_source.w = LARGEUR_TILE;
	Rect_source.h = HAUTEUR_TILE;
    
    printf("before i");
    int n = 0;
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
                tileset = IMG_Load("./resources/sprites/blocks/BackgroundTile.png");
            }
            else if (map[i+j] == 0b01100111) {
                // destructible
                                printf("dest");
                tileset = IMG_Load("./resources/sprites/blocks/ExplodableBlock.png");
            }
            else if (map[i+j] == 0b01000111) {
                // indestructible
                                printf("indest");
                tileset = IMG_Load("./resources/sprites/blocks/SolidBlock.png");
            }
            if (!tileset)
            {
                printf("Echec de chargement tileset1.bmp\n");
                SDL_Quit();
                system("pause");
                exit(-1);
            }
            SDL_BlitSurface(tileset,&Rect_source,screen,&Rect_dest);
		}
        n++;
	}
	SDL_Flip(screen);
}

int draw_map()
{

    SDL_Surface* screen;
	screen = SDL_SetVideoMode(LARGEUR_TILE*NOMBRE_BLOCS_LARGEUR, HAUTEUR_TILE*NOMBRE_BLOCS_HAUTEUR, 32,SDL_HWSURFACE|SDL_DOUBLEBUF);

    char map[195];
    init_map(map);

	Afficher(screen,map,NOMBRE_BLOCS_LARGEUR,NOMBRE_BLOCS_HAUTEUR);

    SDL_Event event;
 
    do  // attend qu'on appuie sur une touche.
	{
		SDL_WaitEvent(&event);
	} while (event.type!=SDL_KEYDOWN);
	
	SDL_FreeSurface(screen);
	SDL_Quit();
    return 0;
}