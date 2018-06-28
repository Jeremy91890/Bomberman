#include "./headers/server.h"
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "../socket.h"

void *main_server()
{
    /*int i = 0;
    while(i < 10){
        printf("I'm the server in a thread !\n");
        sleep(1);
        i = i + 1;
    }*/

    //char buffer[1024];
    int sock = init_connection();
    int actual = 0;
    int max = sock;
    
    t_game game;
   // init_map(game.map);

    fd_set rdfs;
    
    while(1)
    {
        printf("while");
        int i = 0;
        FD_ZERO(&rdfs);
        FD_SET(sock, &rdfs);

        for (i = 0 ; i < actual ; i++)
            FD_SET(game.player_infos[i].socket, &rdfs);
    
        if (select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            printf("select error");
            perror("select()");
            exit(errno);
        }

        if (FD_ISSET(sock, &rdfs))
        {
            printf("isset");

            struct sockaddr_in csin;
            socklen_t sinsize = sizeof(csin);
    
            int csock = accept(sock, (SOCKADDR *) &csin, &sinsize);
            if (csock == -1)
            {
                perror("accept()");
                continue;
            }
    
            if(read_player(csock, game) == -1)
            {
                printf("read player -1");

                /* disconnected */
                continue;
            }

            printf("socket received");

            max = csock > max ? csock : max;
            FD_SET(csock, &rdfs);
            t_player_infos pi = add_new_player(actual);
            pi.socket = csock;
            printf("%d", pi.bombs_left);

            game.player_infos[i] = pi;
            actual++;
            //send_game_to_all_players(actual, game);
        }
        else {
            printf("not setted");
            int i = 0;
            for(i = 0; i < actual; i++)
            {
                /* a client is talking */
                if(FD_ISSET(game.player_infos[i].socket, &rdfs))
                {
                    int c = read_player(game.player_infos[i].socket, game);
                    /* client disconnected */
                    if(c == 0)
                    {
                        closesocket(game.player_infos[i].socket);
                        //remove_client(clients, i, &actual);
                        // strncpy(buffer, client.name, BUF_SIZE - 1);
                        // strncat(buffer, " disconnected !", BUF_SIZE - strlen(buffer) - 1);
                        send_game_to_all_players(actual, game);
                    }
                    else
                    {
                        send_game_to_all_players(actual, game);
                    }
                break;
                }
            }
        }

    }

    printf("quit");
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

int read_player(SOCKET sock, t_game game)
{
   int n = 0;

   if((n = recv(sock, (void*)&game, sizeof(game) - 1, 0)) < 0)
   {
      perror("recv()");
      /* if recv error we disonnect the client */
      n = 0;
   }

   //game[n] = 0;

   return n;
}

void send_game_to_all_players(int actual, t_game game)
{
   printf("send game for all");

   int i = 0;

   for(i = 0; i < actual; i++)
   {
        write_player(game.player_infos[i].socket, game);
   }
}

void write_player(SOCKET sock, t_game game)
{
   printf("write player");
   if(send(sock, (void*)&game, sizeof(game), 0) < 0)
   {
      perror("send()");
      exit(errno);
   }
}
