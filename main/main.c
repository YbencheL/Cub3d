/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:13:35 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/18 14:25:59 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_pos(t_data *data, char **map)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map_h)
	{
		x = 0;
		while (x < data->map_w)
		{
			if (map[y][x] == 'N')
			{
				data->player->posx = (double)x + 0.5;
				data->player->posy = (double)y + 0.5;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_textures(t_data *data, t_cub game)
{
	data->north.img = mlx_xpm_file_to_image(data->mlx, game.no,
			&data->north.width, &data->north.height);
	data->north.addr = mlx_get_data_addr(data->north.img, &data->north.bbq,
			&data->north.sizel, &data->north.indian);
	data->south.img = mlx_xpm_file_to_image(data->mlx, game.we,
			&data->south.width, &data->south.height);
	data->south.addr = mlx_get_data_addr(data->south.img, &data->south.bbq,
			&data->south.sizel, &data->south.indian);
	data->west.img = mlx_xpm_file_to_image(data->mlx, game.so,
			&data->west.width, &data->west.height);
	data->west.addr = mlx_get_data_addr(data->west.img, &data->west.bbq,
			&data->west.sizel, &data->west.indian);
	data->east.img = mlx_xpm_file_to_image(data->mlx, game.ea,
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

	t_cub game;
	check_arg(ac, av);
	ft_parsing(&game, av[1]);
	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	player = malloc(sizeof(t_player));
	data->tex = malloc(sizeof(t_tex));
	data->map = game.map;
	data->map_h = game.col;
	data->map_w = game.row;
	init_vars(data, player);
	data->mlx = mlx_init();
	if (!data->mlx)
	return (1);
	init_textures(data, game);
	data->win = mlx_new_window(data->mlx, data->width, data->height, "cub3d");
	if (!data->win)
		return (1);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bbq, &data->sizel, &data->indian);
	player_pos(data, data->map);
	casting_rays(data, data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	setup_h(data);
	mlx_loop(data->mlx);
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
