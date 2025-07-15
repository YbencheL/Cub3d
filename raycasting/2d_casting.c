/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_casting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:04:05 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/15 11:02:05 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	store_hit_info(t_player *player, t_dda *dda)
{
	player->mapx = dda->map_x;
	player->mapy = dda->map_y;

	if (dda->side == 0)
	{
		// ila bghiti thiti wahd lwall w line dyalk is more vertical you need to move horizontaly
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
		// if we travle more towards the vertical lines
		dda_side_n_step(&dda);
		if (dda.map_x < 0 || dda.map_x >= MAP_SIZE
			|| dda.map_y < 0 || dda.map_y >= MAP_SIZE)
			break ;
		if (data->map[dda.map_y][dda.map_x] == '1')
			hit = 1;
	}
	if (hit)
		store_hit_info(player, &dda);
	return (hit);
}

void casting_rays(t_data *data, t_player *player)
{
	int	r;

	r = 0;
	// using arc tan of dirx and y covertes the values into a radiant angle
    player->player_angle = atan2(data->player->diry, data->player->dirx);
    while (r < data->width)
    {
		// from far left to far right
        player->ray_angle = player->player_angle - (player->fov / 2.0)
            + (player->fov * r) / (data->width);
        player->raydirx = cos(player->ray_angle);
        player->raydiry = sin(player->ray_angle);
        player->rayx = data->player->posx;
        player->rayy = data->player->posy;

        if (rendering_lines(data, player))
            casting_walls(data, player, r);
        r++;
    }
}
