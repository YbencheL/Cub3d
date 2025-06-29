CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm

SRC =	main/main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/parsing.c \
		utils/all_check.c utils/all_conut.c utils/flood_fill.c utils/read_file.c \
		features/hooks.c 2d_rendering/2d_map_rendering.c 2d_rendering/character.c utils/pixel_puting.c \
		raycasting/2d_casting.c raycasting/rizzing_up_walls.c \

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all: cub3d

cub3d: $(OBJ) $(LIBFT)
	$(CC)  $(OBJ) $(LDFLAGS) $(LIBFT) -o cub3d

$(LIBFT):
	make -C libft

%.o: %.c cub.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f cub3d

re: fclean all