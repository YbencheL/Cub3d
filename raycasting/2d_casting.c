/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_casting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:04:05 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/18 14:11:39 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	hit_info(t_player *player, t_dda *dda)
{
	player->mapx = dda->map_x;
	player->mapy = dda->map_y;
	if (dda->side == 0)
	{
		player->hitx = player->posx + (dda->side_x - dda->delta_x)
			* player->raydirx;
		player->hity = player->posy + (dda->side_x - dda->delta_x)
			* player->raydiry;
		player->vertical = 1;
	}
	else
	{
		player->hitx = player->posx + (dda->side_y - dda->delta_y)
			* player->raydirx;
		player->hity = player->posy + (dda->side_y - dda->delta_y)
			* player->raydiry;
		player->vertical = 0;
	}
}

void	dda_side_n_step(t_dda *dda)
{
	if (dda->side_x < dda->side_y)
	{
		dda->side_x += dda->delta_x;
		dda->map_x += dda->step_x;
		dda->side = 0;
	}
	else
	{
		dda->side_y += dda->delta_y;
		dda->map_y += dda->step_y;
		dda->side = 1;
	}
}

int	rendering_lines(t_data *data, t_player *player)
{
	t_dda	dda;
	int		hit;

	hit = 0;
	init_dda_vars(player, &dda);
	while (!hit)
	{
		dda_side_n_step(&dda);
		if (dda.map_x < 0 || dda.map_x >= data->map_w || dda.map_y < 0
			|| dda.map_y >= data->map_w)
			break ;
		if (data->map[dda.map_y][dda.map_x] == '1')
			hit = 1;
	}
	if (hit)
		hit_info(player, &dda);
	return (hit);
}

void	casting_rays(t_data *data, t_player *player)
{
	int	r;

	r = 0;
	player->player_angle = atan2(data->player->diry, data->player->dirx);
	while (r < data->width)
	{
		player->ray_angle = player->player_angle - (player->fov / 2.0)
			+ (player->fov * r) / (data->width);
		player->raydirx = cos(player->ray_angle);
		player->raydiry = sin(player->ray_angle);
		if (rendering_lines(data, player))
			casting_walls(data, player, r);
		r++;
	}
}
