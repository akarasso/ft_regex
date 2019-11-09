REGEX_INCLUDE ?= -I./includes

CC ?= gcc
NAME = regex
CFLAGS := ${CFLAGS}
CFLAGS += -g3 #-ansi -std=99
CFLAGS += $(REGEX_INCLUDE)
LIBS :=

PREFIX ?= /usr/local
BINDIR ?= ${PREFIX}/bin
MANDIR ?= ${PREFIX}/share/man
LDFLAGS=

SOURCES = $(wildcard *.c) $(wildcard ./*/*.c) $(wildcard ./*/*/*.c)
OBJ	= $(SOURCES:.c=.o)

all	: $(NAME)

%.o : %.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(NAME)	: $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

clean :
	rm -f $(OBJ)


fclean : clean
	rm -f $(NAME)

re : fclean all