/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:13:35 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/23 13:34:19 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	player_pos(t_data *data, t_cub *game)
{
	data->player->posx = (double)game->player_y + 0.5;
	data->player->posy = (double)game->player_x + 0.5;
	if (game->d == 'N')
	{
		data->player->dirx = 0;
		data->player->diry = -1;
	}
	if (game->d == 'S')
	{
		data->player->dirx = 0;
		data->player->diry = 1;
	}
	if (game->d == 'W')
	{
		data->player->dirx = -1;
		data->player->diry = 0;
	}
	if (game->d == 'E')
	{
		data->player->dirx = 1;
		data->player->diry = 0;
	}
	return ;
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
	player->mapx = (int)player->posx;
	player->mapy = (int)player->posy;
	player->fov = M_PI / 3.0;
	player->player_angle = 3.0 * M_PI / 2.0;
	player->dirx = cos(player->player_angle);
	player->diry = sin(player->player_angle);
	data->img = NULL;
	data->addr = NULL;
	data->height = 600;
	data->width = 800;
}

int	init_data(t_cub *game, t_data *data)
{
	int	i;

	i = 0;
	data->map = malloc(sizeof(char *) * (game->row + 1));
	while (game->map[i])
	{
		data->map[i] = ft_strdup(game->map[i]);
		i++;
	}
	data->map[i] = NULL;
	data->map_h = game->col;
	data->map_w = game->row;
	data->colorg = game->f_color;
	data->colors = game->c_color;
	data->mlx = mlx_init();
	if (!data->mlx)
		return (1);
	data->win = mlx_new_window(data->mlx, data->width, data->height, "cub3d");
	if (!data->win)
		return (1);
	data->img = mlx_new_image(data->mlx, data->width, data->height);
	data->addr = mlx_get_data_addr(data->img, &data->bbq,
			&data->sizel, &data->indian);
	return (0);
}

int	main(int ac, char **av)
{
	t_data		*data;
	t_player	*player;
	t_cub		game;

	check_arg(ac, av);
	ft_parsing(&game, av[1]);
	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	player = malloc(sizeof(t_player));
	data->tex = malloc(sizeof(t_tex));
	init_vars(data, player);
	if (init_data(&game, data))
		return (1);
	init_textures(data, game);
	player_pos(data, &game);
	casting_rays(data, data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	ft_free(&game, 0);
	setup_h(data);
	mlx_loop(data->mlx);
	return (0);
}
