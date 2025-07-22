/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:24:07 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/22 14:51:29 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	close_program(t_data *data)
{
	if (data->north.img)
		mlx_destroy_image(data->mlx, data->north.img);
	if (data->south.img)
		mlx_destroy_image(data->mlx, data->south.img);
	if (data->west.img)
		mlx_destroy_image(data->mlx, data->west.img);
	if (data->east.img)
		mlx_destroy_image(data->mlx, data->east.img);
	if (data->img)
		mlx_destroy_image(data->mlx, data->img);
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	free_split(data->map);
	free(data->tex);
	free(data->player);
	free(data);
	exit(0);
	return (0);
}

void	move_player(t_data *data, double dx, double dy, char **map)
{
	int	map_x;
	int	map_y;

	map_x = (int)(data->player->posx + dx);
	map_y = (int)(data->player->posy + dy);
	if (map_x >= 0 && map_x < (int)ft_strlen(map[map_y])
		&& map_y >= 0 && map_y < data->map_h 
		&& map[map_y][map_x] != '1')
	{
		data->player->posx += dx;
		data->player->posy += dy;
	}
}

void	rotate_player(t_data *data, double angle)
{
	int	map_x;
	int	map_y;

	map_x = (int)data->player->posx;
	map_y = (int)data->player->posy;
	data->player->player_angle += angle;
	if (data->player->player_angle < 0)
		data->player->player_angle += 2 * M_PI;
	else if (data->player->player_angle > 2 * M_PI)
		data->player->player_angle -= 2 * M_PI;
	data->player->dirx = cos(data->player->player_angle);
	data->player->diry = sin(data->player->player_angle);
}

int	key_press(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < NUM_KEYS)
		data->key_states[keycode] = 1;
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode >= 0 && keycode < NUM_KEYS)
		data->key_states[keycode] = 0;
	return (0);
}
