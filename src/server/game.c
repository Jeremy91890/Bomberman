#include "../headers/game.h"
#include "../headers/server.h"
#include "../headers/map.h"

t_game go_logique_server(t_game game, int actual, t_client_request req)
{
    t_player_infos pi = game.player_infos[actual];

    if (pi.alive == 1) {
        if (game.game_state == 1) {
            if (req.dir != 0 && req.dir != pi.current_dir) {
                game = turn_player(game, actual, req);
            } else if (req.x_pos != pi.x_pos || req.y_pos != pi.y_pos) {
                game = move_player(game, actual, req);
            } else if (req.command == 1) {
                game = place_bomb(game, actual, req);
            }
        } else if (req.command == 2 && actual == 0 && game.game_state == 0) {
            game = start_game(game);
        }
    }

    return game;
}

t_game turn_player(t_game game, int actual, t_client_request req)
{
    game.player_infos[actual].current_dir = req.dir;
    return game;
}

t_game move_player(t_game game, int actual, t_client_request req)
{
    int wanted_x = req.x_pos;
    int wanted_y = req.y_pos;
    int wanted_index = NB_BLOCS_WIDTH * wanted_y + wanted_x;

    if (game.map[wanted_index] != 0b01100111 && game.map[wanted_index] != 0b01000111 && game.map[wanted_index] != 0b00010111) {
        game.player_infos[actual].x_pos = wanted_x;
        game.player_infos[actual].y_pos = wanted_y;
    }

    return game;
}

t_game place_bomb(t_game game, int actual, t_client_request req) {
    int wanted_bomb_index = NB_BLOCS_WIDTH * game.player_infos[actual].y_pos + game.player_infos[actual].x_pos;

    if (game.player_infos[actual].bombs_left > 0 && game.map[wanted_bomb_index] != 0b00010111) {
        game.player_infos[actual].bombs_left -= 1;
        game.map[wanted_bomb_index] = 0b00010111;

        bomb_timers.number_of_bombs = bomb_timers.number_of_bombs + 1;
        bomb_timers.bomb_timer[bomb_timers.number_of_bombs].bomb_index = wanted_bomb_index;
        bomb_timers.bomb_timer[bomb_timers.number_of_bombs].explosion_time = (unsigned)time(NULL) + BOMB_SEC;
    }
    return game;
}

t_game start_game(t_game game)
{
    if (get_nb_players(game) > 1) {
        game.game_state = 1;
    }
    return game;
}

int get_nb_players(t_game game)
{
    int i;
    int nb;
    nb = 0;

    for (i = 0; i < MAX_PLAYERS; i++) {
        if (game.player_infos[i].socket != 0)
            nb += 1;
    }

    return nb;
}

void display_explosion(int bomb_index, char *map, int nb_case)
{
    // ajout de chaque direction
    add_flames(bomb_index, map, nb_case, -nb_case, -1);
    add_flames(bomb_index, map, nb_case, nb_case, 1);
    add_flames(bomb_index, map, nb_case, nb_case * (-15), -15);
    add_flames(bomb_index, map, nb_case, nb_case * 15, 15);
}

void add_flames(int bomb_index, char *map, int nb_case, int max_index, int iterator)
{
    int i;

    if (max_index > 0) {
        for (i = 0; i <= max_index; i+= iterator) {
            if (map[bomb_index + i] != 0b00010111) {
                if (map[bomb_index + i] == DESTRUCTABLE_WALL) {
                    map[bomb_index + i] = 0;
                    flam_timers.number_of_flams = flam_timers.number_of_flams + 1;
                    flam_timers.flam_timer[flam_timers.number_of_flams].flam_index = bomb_index + i;
                    flam_timers.flam_timer[flam_timers.number_of_flams].display_time = (unsigned)time(NULL) + 1;
                    i = max_index;
                } else if (map[bomb_index + i] != UNDESTRUCTABLE_WALL) {
                    map[bomb_index + i] = 0;
                    flam_timers.number_of_flams = flam_timers.number_of_flams + 1;
                    flam_timers.flam_timer[flam_timers.number_of_flams].flam_index = bomb_index + i;
                    flam_timers.flam_timer[flam_timers.number_of_flams].display_time = (unsigned)time(NULL) + 1;
                } else {
                    break;
                }

                if (i == max_index) {
                    break;
                }
            }
        }
    } else {
        for (i = 0; i >= max_index; i+= iterator) {
            if (map[bomb_index + i] != 0b00010111) {
                if (map[bomb_index + i] == DESTRUCTABLE_WALL) {
                    map[bomb_index + i] = 0;
                    flam_timers.number_of_flams = flam_timers.number_of_flams + 1;
                    flam_timers.flam_timer[flam_timers.number_of_flams].flam_index = bomb_index + i;
                    flam_timers.flam_timer[flam_timers.number_of_flams].display_time = (unsigned)time(NULL) + 1;
                    i = max_index;
                } else if (map[bomb_index + i] != UNDESTRUCTABLE_WALL) {
                    map[bomb_index + i] = 0;
                    flam_timers.number_of_flams = flam_timers.number_of_flams + 1;
                    flam_timers.flam_timer[flam_timers.number_of_flams].flam_index = bomb_index + i;
                    flam_timers.flam_timer[flam_timers.number_of_flams].display_time = (unsigned)time(NULL) + 1;
                } else {
                    break;
                }
                if (i == max_index) {
                    break;
                }
            }
        }
    }
}
