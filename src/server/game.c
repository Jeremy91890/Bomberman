#include "../headers/game.h"
#include "../headers/server.h"
#include "../headers/map.h"

t_game go_logique_server(t_game game, int actual, t_client_request req) {
    //printf("Actual : %d\n", actual);
    t_player_infos pi = game.player_infos[actual];


    if (req.dir != 0 && req.dir != pi.current_dir)
        game = turn_player(game, actual, req);
    else if (req.x_pos != pi.x_pos || req.y_pos != pi.y_pos)
        game = move_player(game, actual, req);
    else if (req.command == 1) 
        game = place_bomb(game, actual, req);

    //TODO : Check map fire, explosion, player HP, ...

    return game;
}

t_game turn_player(t_game game, int actual, t_client_request req) {
    printf("Current dir : %d\n", game.player_infos[actual].current_dir);
    printf("Wanted dir : %d\n", req.dir);
    game.player_infos[actual].current_dir = req.dir;
    return game;
}

t_game move_player(t_game game, int actual, t_client_request req) {
    int wanted_x = req.x_pos;
    int wanted_y = req.y_pos;
    int wanted_index = NB_BLOCS_WIDTH * wanted_y + wanted_x;

    printf("Current x : %d\n", game.player_infos[actual].x_pos);
    printf("Current y : %d\n", game.player_infos[actual].y_pos);
    printf("Wanted x : %d\n", req.x_pos);
    printf("Wanted y : %d\n", req.y_pos);

    if (game.map[wanted_index] == 0b00000111) {
        game.player_infos[actual].x_pos = wanted_x;
        game.player_infos[actual].y_pos = wanted_y;
    }

    return game;
}

t_game place_bomb(t_game game, int actual, t_client_request req) {
    int wanted_bomb_index = NB_BLOCS_WIDTH * game.player_infos[actual].y_pos + game.player_infos[actual].x_pos;
    printf("Bomb left : ");
    printf("%d\n", game.player_infos[actual].bombs_left);
    if (game.player_infos[actual].bombs_left > 0 && game.map[wanted_bomb_index] != 0b00010111) {
        game.player_infos[actual].bombs_left -= 1;
        game.map[wanted_bomb_index] = 0b00010111;
        
        /*bomb_timers.number_of_bombs = bomb_timers.number_of_bombs + 1;
        bomb_timers.bomb_timer = realloc(bomb_timers.bomb_timer, bomb_timers.number_of_bombs * sizeof(bomb_timers.bomb_timer));
        bomb_timers.bomb_timer[bomb_timers.number_of_bombs].bomb_index = wanted_bomb_index;
        bomb_timers.bomb_timer[bomb_timers.number_of_bombs].explosion_time = (unsigned)time(NULL) + BOMB_SEC;*/
    }
    return game;
}