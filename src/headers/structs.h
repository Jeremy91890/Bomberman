#ifndef     _STRUCTS_H_
#define     _STRUCTS_H_

#define MAX_PLAYERS     4
#define MAP_SIZE        195

typedef enum        direction
{
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    TOP = 4
}                   direction;

typedef enum        bloc_type
{
    GROUND = 0b00000111,
    DESTRUCTABLE_WALL = 0b01100111,
    UNDESTRUCTABLE_WALL = 0b01000111
}                   bloc_type;

typedef struct      s_client_request
{
    unsigned int    magic;
    int             x_pos;
    int             y_pos;
    int             dir;
    int             command;
    int             speed;
    int             checksum;
}                   t_client_request;

typedef struct      s_player_infos
{
    int             socket;
    char            connected;
    char            alive;
    int             x_pos;
    int             y_pos;
    int             current_dir;
    int             current_speed;
    int             max_speed;
    int             bombs_left;
    int             bombs_capacity;
    int             frags;
}                   t_player_infos;

typedef char        t_map[MAP_SIZE];

typedef struct      s_game
{
    t_player_infos  player_infos[MAX_PLAYERS];
    t_map           map;
    //t_other         infos;
}                   t_game;

#endif
