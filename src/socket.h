#ifndef     _SOCKET_H_
#define     _SOCKET_H_


# ifdef __WIN32__

# undef _WIN32_WINNT
# define _WIN32_WINNT _WIN32_WINNT_WIN8
# else
# include <sys/socket.h>
# include <sys/types.h>
# define closesocket(s) close(s)

# define INVALID_SOCKET -1
# define SOCKET_ERROR -1

typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;
# endif



#endif