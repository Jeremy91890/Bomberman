CC =			gcc
SRCS =			$(wildcard src/*.c)
OBJS =			$(SRCS:%.c=%.o)
CFLAGS =		-g3 -Wall -Werror -Wno-return-type
SDLFLAGS = 		-lSDL -lSDL_image -lSDL_ttf
OTHERFLAGS = 	-lpthread


ifeq ($(OS),Windows_NT)
	NAME =  	bomberman.exe
	RMOBJS = 	del $(subst /,\,$(OBJS))
	RM =		del
	WINLIBS =  	-lws2_32 -lwsock32
else
	NAME =  	bomberman
	RMOBJS = 	rm -f $(OBJS)
	RM = 		rm
endif

all:		$(NAME)

$(NAME):	$(OBJS)
		$(CC) $(OBJS) $(CFLAGS) $(SDLFLAGS) $(OTHERFLAGS) $(WINLIBS) -o $(NAME)

clean:
	$(RMOBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: fclean all clean