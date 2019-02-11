#include "generate_map.h"
#include "server.h"

char get_random_destructable_bloc()
{
    int r = rand() % ((2+1) - 1) + 1;

    if (r == 1) {
        // mur destructible
        return DESTRUCTABLE_WALL;
    } else {
        // herbe
        return GROUND;
    }
}

// Libère les cases autour du joueur
void delete_blocs_around_players(char map[], int pos[])
{
    int index = 0;

    while (index < 4) {
        int posJoueur = pos[index];
        int n = 0;
        int i = posJoueur - 16;

        while (i < (posJoueur + 16)) {
            if (map[i] == DESTRUCTABLE_WALL) {
                map[i] = GROUND;
            }
            if (n < 2) {
                i++;
                n++;
            } else {
                i = i + 13;
                n = 0;
            }
        } 
        
        index++;
    }
}

void init_map(char map[])
{
    srand(time(NULL));

    int playerPos[4] = {16, 28, 178, 166};
    int blocPerLine = 15;
    int nbLine = 13;
    int i = 0;
    int firstRowBloc = 0;

    while (i < 195) {
        if (i < blocPerLine || i >= (blocPerLine * (nbLine - 1)) || i == (firstRowBloc + 14)) {
            // incassable
            map[i] = UNDESTRUCTABLE_WALL; 
        } else {
            if (i % blocPerLine == 0) {
                firstRowBloc = i;
                // incassable
                map[i] = UNDESTRUCTABLE_WALL;
            } else {
                if (firstRowBloc % 2 == 0) {
                    if (i % 2 == 0) {
                        // incassable
                        map[i] = UNDESTRUCTABLE_WALL;
                    } else {
                        //random
                        map[i] = get_random_destructable_bloc(); 
                    }
                } else {
                    //random
                    map[i] = get_random_destructable_bloc(); 
                }
            }
        }
        i++;
    }
    map[195] = '\0';
    
    delete_blocs_around_players(map, playerPos);
}