#include "./headers/server.h"

void *main_server()
{
    int i = 0;
    while(i < 10){
        printf("I'm the server in a thread !\n");
        sleep(1);
        i = i + 1;
    }

    // int sock = init_connection();
    // int actual = 0;
    // int max = sock;
    //
    // t_game game;
    //
    // fd_set rdfs;
    //
    // while(1)
    // {
    //     int i = 0;
    //     FD_ZERO(&rdfs);
    //     FD_SET(sock, &rdfs);
    //
    //     for (i = 0 ; i < actual ; i++)
    //         FD_SET(game.player_infos[i].socket, &rdfs);
    //
    //     if (select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
    //     {
    //         perror("select()");
    //         exit(errno);
    //     }
    //
    //     if (FD_ISSET(sock, &rdfs))
    //     {
    //         struct sockaddr_in csin;
    //         size_t sinsize = sizeof(csin);
    //
    //         int csock = accept(sock, (SOCKADDR *) &csin, &sinsize);
    //         if (csock == -1)
    //         {
    //             perror("accept()");
    //             continue;
    //         }
    //
    //         max = csock > max ? csock : max;
    //         FD_SET(csock, &rdfs);
    //         t_player_infos pi = add_new_player(actual);
    //         pi.socket = csock;
    //     }
    // }

    //destroy the warning
    pthread_exit(NULL);
}

int init_connection()
{
    int                 s;
    struct protoent     *pe;
    struct sockaddr_in  sin;

    pe = getprotobyname("tcp");
    s = socket(PF_INET, SOCK_STREAM, pe->p_proto);
    if (s == -1)
    {
        perror("socket()");
        exit(errno);
    }

    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);
    sin.sin_addr.s_addr = INADDR_ANY;

    if (bind(s, (struct sockaddr*) &sin, sizeof(sin)) == -1 )
    {
        perror("bind()");
        exit(errno);
    }

    if (listen(s, MAX_PLAYERS) == -1)
    {
        perror("listen()");
        exit(errno);
    }

    return s;
}
