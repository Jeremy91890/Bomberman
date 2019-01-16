ifdef OS
	CC := gcc
	RM := del -f
	LN_F = ln -f

	CFLAGS := -c -Wall -g3 -Werror -lSDL -lSDL_image -lSDL_ttf

	EXE_NAME := BombermanExe
	SRCDIRS := src src\client src\server
	OBJDIR := build\obj
	BINDIR := build\bin

	TARGET := $(BINDIR)\$(EXE_NAME)

	SRC_FILES :=
	SRCS := $(foreach dir,$(SRCDIRS), $(wildcard $(dir)\*.c)) $(SRC_FILES)
	OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

	create_out_directory := $(shell mkdir -p build)
	create_out_directory := $(shell mkdir -p $(BINDIR))
    create_out_directory := $(shell mkdir -p $(OBJDIR))
    create_out_directory := $(foreach dir,  $(SRCDIRS),   $(shell mkdir -p $(OBJDIR)\$(dir)))
else
   ifeq ($(shell uname), Linux)
    CC := gcc
	RM := rm -f
	LN_F = ln -f

	CFLAGS := -Wall -g3 -Werror -lpthread -lSDL -lSDL_image -lSDL_ttf

	EXE_NAME := BombermanExe
	SRCDIRS := src src/client src/server
	OBJDIR := build/obj
	BINDIR := build/bin

	TARGET := $(BINDIR)/$(EXE_NAME)

	SRC_FILES :=
	SRCS := $(foreach dir,$(SRCDIRS), $(wildcard $(dir)/*.c)) $(SRC_FILES)
	OBJS := $(SRCS:%.c=$(OBJDIR)/%.o)

	create_out_directory := $(shell mkdir -p build)
	create_out_directory := $(shell mkdir -p $(BINDIR))
	create_out_directory := $(shell mkdir -p $(OBJDIR))
	create_out_directory := $(foreach dir,  $(SRCDIRS),   $(shell mkdir -p $(OBJDIR)/$(dir)))
   endif
endif


all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(CFLAGS) -o "$(TARGET)"
	$(LN_F) $(TARGET) $(EXE_NAME)

$(OBJDIR)/%.o: %.c
	$(CC) -c $(CFLAGS) "$<" -o "$@"

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(EXE_NAME) $(TARGET) $(OBJS)

re: fclean all

.PHONY: all%