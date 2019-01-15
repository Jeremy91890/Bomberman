#include "../headers/server.h"

t_player_infos *add_new_player(int index)
{
    t_player_infos *pi;
    pi = malloc(sizeof(t_player_infos));
    pi->alive = 1;
    pi->connected = 1;
    pi->bombs_capacity = 100;
    pi->bombs_left = 100;
    pi->frags = 0;

    switch (index)
    {
    case 0:
        pi->x_pos = 1;
        pi->y_pos = 1;
        pi->current_dir = 1;
        break;
    case 1:
        pi->x_pos = 13;
        pi->y_pos = 1;
        pi->current_dir = 2;
        break;
    case 2:
        pi->x_pos = 13;
        pi->y_pos = 11;
        pi->current_dir = 3;
        break;
    case 3:
        pi->x_pos = 1;
        pi->y_pos = 11;
        pi->current_dir = 4;
        break;
    }

    return pi;
}
