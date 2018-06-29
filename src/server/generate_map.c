#include "../headers/generate_map.h"
#include "../headers/server.h"

char get_random_destructable_bloc()
{
    int r = rand() % ((2+1) - 1) + 1;

    printf("%d\n", r);

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
    
    // AFFICHAGE EN ASCII DE LA MAP, A SUPPRIMER C'EST JUSTE POUR TEST
    /*int n = 0;
    while (n < 195) {
        if (n % 15 == 0) {
            printf("\n");
        }
        if (map[n] == 0b01000111) {
            printf("[]");
            //indestructible
        } else if (map[n] == 0b00000111) {
            printf("  ");
            // herbe
        } else if (map[n] == 0b01100111) {
            printf("<>");
            //destructible
        }
        
        n++;
    }
    */
}