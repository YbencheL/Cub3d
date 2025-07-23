/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rizzing_up_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/23 13:23:48 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

double	border_patrol(t_player *player, t_data *data)
{
	double	wall_x;

	if (player->draw_start < 0)
		player->draw_start = 0;
	if (player->draw_end < 0)
		player->draw_end = 0;
	if (player->draw_end >= data->height)
		player->draw_end = data->height - 1;
	if (player->draw_start >= data->height)
		player->draw_start = data->height - 1;
	if (player->vertical)
		wall_x = player->hity;
	else
		wall_x = player->hitx;
	wall_x -= floor(wall_x);
	return (wall_x);
}

void	casting_walls(t_data *data, t_player *player, int ray_indx)
{
	double	dx;
	double	dy;
	double	projection_plane_d;
	double	y;
	double	wall_x;

	dx = player->hitx - player->posx;
	dy = player->hity - player->posy;
	player->distance = sqrt(dx * dx + dy * dy) * cos(player->ray_angle
			- player->player_angle);
	projection_plane_d = (data->width / 2.0) / tan(player->fov / 2.0);
	player->wall_height = (int)(projection_plane_d / player->distance);
	player->draw_start = (data->height / 2.0) - (player->wall_height / 2.0);
	player->draw_end = (data->height / 2.0) + (player->wall_height / 2.0);
	wall_x = border_patrol(player, data);
	y = -1.0;
	while (++y < player->draw_start)
		my_mlx_pixel_put(data, ray_indx, y, data->colors);
	textures_logic(data, player, ray_indx, wall_x);
	y = player->draw_end;
	while (++y < data->height)
		my_mlx_pixel_put(data, ray_indx, y, data->colorg);
}
