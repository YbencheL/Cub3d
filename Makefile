CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm

SRC =	main/main.c features/hooks.c
OBJ = $(SRC:.c=.o)

all: cub3d

cub3d: $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o cub3d

%.o: %.c cub.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f cub3d

re: fclean all