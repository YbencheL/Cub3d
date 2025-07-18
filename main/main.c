/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:13:35 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/18 10:44:50 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_pos(t_player *player, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < MAP_SIZE)
	{
		x = 0;
		while (x < MAP_SIZE)
		{
			if (map[y][x] == 'P')
			{
				player->posx = (double)x + 0.5;
				player->posy = (double)y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_textures(t_data *data)
{
	data->north.img = mlx_xpm_file_to_image(data->mlx, "textures/west.xpm",
			&data->north.width, &data->north.height);
	data->north.addr = mlx_get_data_addr(data->north.img, &data->north.bbq,
			&data->north.sizel, &data->north.indian);
	data->south.img = mlx_xpm_file_to_image(data->mlx, "textures/west.xpm",
			&data->south.width, &data->south.height);
	data->south.addr = mlx_get_data_addr(data->south.img, &data->south.bbq,
			&data->south.sizel, &data->south.indian);
	data->west.img = mlx_xpm_file_to_image(data->mlx, "textures/north.xpm",
			&data->west.width, &data->west.height);
	data->west.addr = mlx_get_data_addr(data->west.img, &data->west.bbq,
			&data->west.sizel, &data->west.indian);
	data->east.img = mlx_xpm_file_to_image(data->mlx, "textures/north.xpm",
			&data->east.width, &data->east.height);
	data->east.addr = mlx_get_data_addr(data->east.img, &data->east.bbq,
			&data->east.sizel, &data->east.indian);
}

void	init_vars(t_data *data, t_player *player)
{
	data->player = player;
	player->posx = 0.0;
	player->posy = 0.0;
	player->mapx = (int)player->posx;
	player->mapy = (int)player->posy;
	player->fov = M_PI / 3.0;
	player->player_angle = 3.0 * M_PI / 2.0;
	player->dirx = cos(player->player_angle);
	player->diry = sin(player->player_angle);
	data->img = NULL;
	data->addr = NULL;
	data->colors = 0x05cdf8;
	data->colorg = 0x662b04;
	data->height = 600;
	data->width = 850;
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;
	t_data		*data;
	t_player	*player;

	char *map[MAP_SIZE] = {
		"111111111",
		"1000P0001",
		"101011111",
		"100000011",
		"101011011",
		"101000011",
		"101111111",
		"100000001",
		"100111001",
		"111111111"
	};
	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	player = malloc(sizeof(t_player));
	data->tex = malloc(sizeof(t_tex));
	data->map = map;
	init_vars(data, player);
	data->mlx = mlx_init();
	if (!data->mlx)
	return (1);
	init_textures(data);
	data->win = mlx_new_window(data->mlx, data->width, data->height, "cub3d");
	if (!data->win)
		return (1);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bbq, &data->sizel, &data->indian);
	player_pos(player, map);
	casting_rays(data, data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	setup_h(data);
	mlx_loop(data->mlx);
	// t_cub game;
	// check_arg(ac, av);
	// ft_parsing(&game, av[1]);
	// printf("NO        : %s\n", game.no);
	// printf("SO        : %s\n", game.so);
	// printf("WE        : %s\n", game.we);
	// printf("EA        : %s\n", game.ea);
	// printf("F         : %s\n", game.f);
	// printf("C         : %s\n", game.c);
	// printf("COL       : %d\n", game.col);
	// printf("ROW       : %d\n", game.row);
	// printf("F_COLOR   : %d\n", game.f_color);
	// printf("C_COLOR   : %d\n", game.c_color);
	// printf("PLAYER_X  : %d\n", game.player_x);
	// printf("PLAYER_Y  : %d\n", game.player_y);
	// printf("PLAYER    : %c\n", game.d);
	// int i = 0;
	// printf("________________________MAP________________________\n\n\n");
	// while (game.map[i])
	// {
	// 	printf("               %s\n", game.map[i]);
	// 	i++;
	// }
	// ft_free(&game, 0);
	return 0;
}
