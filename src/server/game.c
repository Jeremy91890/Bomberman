#include "../headers/game.h"
#include "../headers/server.h"
#include "../headers/map.h"

void go_logique_server(t_game *game, int actual, t_client_request *req) {
    printf("Actual : %d\n", actual);
    t_player_infos pi = game->player_infos[actual];
    printf("Current dir : %d\n", pi.current_dir);
    printf("Wanted dir : %d\n", req->dir);

    if (req->dir != pi.current_dir)
        turn_player(game, actual, req);
    // else if (req.x_pos != pi.x_pos || req.y_pos != pi.y_pos)
    //     game = move_player(game, actual, req);
    // else if (req.command == 1)
    //     game = put_bomb(game, actual, req);

    //TODO : Check map fire, explosion, player HP, ...
}

void turn_player(t_game *game, int actual, t_client_request *req) {
    game->player_infos[actual].current_dir = req->dir;
}

// t_game move_player(t_game game, int actual, t_client_request req) {
//     int wanted_x = req.x_pos;
//     int wanted_y = req.y_pos;
//     int wanted_index = NB_BLOCS_WIDTH * wanted_y + wanted_x;
//
//     if (game.map[wanted_index] == 0b00000111) {
//         game.player_infos[actual].x_pos = wanted_x;
//         game.player_infos[actual].y_pos = wanted_y;
//     }
//
//     return game;
// }
//
// t_game put_bomb(t_game game, int actual, t_client_request req) {
//
//
//     return game;
// }
