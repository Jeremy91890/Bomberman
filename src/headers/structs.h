#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#define MAX_PLAYERS 4
#define MAP_SIZE 195

typedef enum direction
{
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    TOP = 4
} direction;

typedef enum bloc_type
{
    GROUND = 0b00000111,
    DESTRUCTABLE_WALL = 0b01100111,
    UNDESTRUCTABLE_WALL = 0b01000111
} bloc_type;

typedef struct s_bomb_timer
{
    int bomb_index;
    int explosion_time;
} t_bomb_timer;

typedef struct s_bomb_timers
{
    t_bomb_timer bomb_timer[195];
    int number_of_bombs;
} t_bomb_timers;

typedef struct s_flam_timer
{
    int flam_index;
    int display_time;
} t_flam_timer;

typedef struct s_flam_timers
{
    t_flam_timer flam_timer[195];
    int number_of_flams;
} t_flam_timers;

typedef struct s_client_request
{
    unsigned int magic;
    int x_pos;
    int y_pos;
    int dir;
    int command;
    int speed;
    int checksum;
} t_client_request;

typedef struct s_player_infos
{
    int socket;
    char connected;
    char alive;
    int x_pos;
    int y_pos;
    int current_dir;
    int current_speed;
    int max_speed;
    int bombs_left;
    int bombs_capacity;
    int frags;
} t_player_infos;

typedef char t_map[MAP_SIZE];

typedef struct s_game
{
    t_player_infos player_infos[MAX_PLAYERS];
    t_map map;
    int game_state;
    int time;
} t_game;

typedef struct s_thread_params
{
    int sock;
    t_game *game;
    int game_size;
    t_player_infos *player;
    int actual_index;
} t_thread_params;

#endif
