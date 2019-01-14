#ifndef     _SOCKET_H_
#define     _SOCKET_H_

#ifdef __WIN32__
# include <winsock2.h>
#else
# include <sys/socket.h>
# define INVALID_SOCKET -1
# define SOCKET_ERROR -1
typedef int SOCKET;
#endif

#include <sys/types.h>
#define closesocket(s) close(s)




typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#endif