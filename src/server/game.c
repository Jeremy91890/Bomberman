#include "../headers/game.h"
#include "../headers/server.h"
#include "../headers/map.h"

t_game go_logique_server(t_game game, int actual, t_client_request req) {
    t_player_infos pi = game.player_infos[actual];

    if (req.x_pos != pi.x_pos || req.y_pos != pi.y_pos)
        game = move_player(game, pi, req);
    else if (req.command == 1)
        game = put_bomb(game, pi, req);

    //TODO : Check map fire, explosion, player HP, ...

    return game;
}

t_game move_player(t_game game, int actual, t_client_request req) {
    t_player_infos pi = game.player_infos[actual];
    int next_dir;

    int current_x = pi.x_pos;
    int current_y = pi.y_pos;
    int current_index = NB_BLOCS_WIDTH * current_y + current_x;

    int wanted_x = req.x_pos;
    int wanted_y = req.y_pos;
    int wanted_index = NB_BLOCS_WIDTH * wanted_y + wanted_x;

    if (wanted_x - current_x = 1)
        next_dir = 1;
    else if (wanted_x - current_x = -1)
        next_dir = 3;
    else {
        if (wanted_y - current_y = 1)
            next dir = 2;
        else if (wanted_y - current_y = -1)
            next_dir = 4;
    }

    if (game.map[wanted_index] == 0b00000111) {
        //OK
    }
    else {
        //KO
    }

    return game;
}

t_game put_bomb(t_game game, int actual, t_client_request req) {


    return game;
}
