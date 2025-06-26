CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm

SRC =	main/main.c features/hooks.c 2d_rendering/2d_map_rendering.c 2d_rendering/character.c utils/pixel_puting.c \
		raycasting/2d_casting.c raycasting/rizzing_up_walls.c
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