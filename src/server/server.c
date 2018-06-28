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

    char buffer[1024];
    int sock = init_connection();
    int actual = 0;
    int max = sock;
    
    t_game game;
    
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
            struct sockaddr_in csin;
            socklen_t sinsize = sizeof(csin);
    
            int csock = accept(sock, (SOCKADDR *) &csin, &sinsize);
            if (csock == -1)
            {
                perror("accept()");
                continue;
            }
    
            if(read_client(csock, buffer) == -1)
            {
                /* disconnected */
                continue;
            }

            printf("%s", buffer);
            printf("socket received");
            max = csock > max ? csock : max;
            FD_SET(csock, &rdfs);
            //t_player_infos pi = add_new_player(actual);
           // pi.socket = csock;
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

int read_client(SOCKET sock, char *buffer)
{
   int n = 0;

   if((n = recv(sock, buffer, strlen(buffer) - 1, 0)) < 0)
   {
      perror("recv()");
      /* if recv error we disonnect the client */
      n = 0;
   }

   buffer[n] = 0;

   return n;
}

// static void write_client(SOCKET sock, const char *buffer)
// {
//    if(send(sock, buffer, strlen(buffer), 0) < 0)
//    {
//       perror("send()");
//       exit(errno);
//    }
// }
