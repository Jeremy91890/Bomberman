#include "../headers/server.h"

t_player_infos add_new_player(int index)
{
    t_player_infos pi;
    pi.alive = 1;
    pi.connected = 1;
    pi.bombs_capacity = 10;
    pi.bombs_left = 10;
    pi.frags = 0;
    //ToComplete

    switch (index) {
        case 0:
            pi.x_pos = 0;
            pi.y_pos = 0;
            pi.current_dir = 1;
            break;
        case 1:
            pi.x_pos = 14;
            pi.y_pos = 0;
            pi.current_dir = 2;
            break;
        case 2:
            pi.x_pos = 14;
            pi.y_pos = 12;
            pi.current_dir = 3;
            break;
        case 3:
            pi.x_pos = 0;
            pi.y_pos = 12;
            pi.current_dir = 4;
            break;
    }

    return pi;
}
