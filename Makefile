CC = cc
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm

SRC =	main/main.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c parsing/parsing.c \
		utils/all_check.c utils/all_conut.c utils/flood_fill.c utils/read_file.c \
		features/hooks.c features/key_hooks.c utils/pixel_puting.c \
		raycasting/2d_casting.c raycasting/rizzing_up_walls.c raycasting/calculating_dda_vals.c raycasting/texture_logic.c \

OBJ = $(SRC:.c=.o)

LIBFT = libft/libft.a

all: cub3D

cub3D: $(OBJ) $(LIBFT)
	$(CC)  $(OBJ) $(LDFLAGS) $(LIBFT) -o cub3D

$(LIBFT):
	make -C libft

%.o: %.c cub3D.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f cub3D

re: fclean all