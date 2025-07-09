/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_casting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:04:05 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/09 18:08:33 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void	set_dda_delta(t_player *player, t_dda *dda)
{
    // delta hiya distance li khas lplayer ytravl bash ycrossi 1 vertical or horizontal line
	if (player->raydirx == 0)
		dda->delta_x = 1e30; // to not make it 0 cause 0 will cause to stay allways in one line
	else
		dda->delta_x = fabs(1.0 / player->raydirx);
	if (player->raydiry == 0)
		dda->delta_y = 1e30;
	else
		dda->delta_y = fabs(1.0 / player->raydiry);
}

static void	set_dda_stepx_sx(t_player *player, t_dda *dda)
{
    // step x hiya shm itijah l coordinants dyal lmap ghaymsho fih bash ydkhlo fnshi grid
    // side hiya distance li ghaymshi fiha lplayer bash ydkhl f next gridline x wla y
	if (player->raydirx < 0)
	{
		dda->step_x = -1;
		dda->side_x = (player->posx - dda->map_x) * dda->delta_x;
	}
	else
	{
		dda->step_x = 1;
		dda->side_x = (dda->map_x + 1.0 - player->posx) * dda->delta_x;
	}
}

static void	set_dda_stepy_sy(t_player *player, t_dda *dda)
{
	if (player->raydiry < 0)
	{
		dda->step_y = -1;
		dda->side_y = (player->posy - dda->map_y) * dda->delta_y;
	}
	else
	{
		dda->step_y = 1;
		dda->side_y = (dda->map_y + 1.0 - player->posy) * dda->delta_y;
	}
}

static void	init_dda_vars(t_player *player, t_dda *dda)
{
	dda->map_x = (int)player->posx;
	dda->map_y = (int)player->posy;
	set_dda_delta(player, dda);
	set_dda_stepx_sx(player, dda);
	set_dda_stepy_sy(player, dda);
}

static void	store_hit_info(t_player *player, t_dda *dda)
{
	player->mapx = dda->map_x;
	player->mapy = dda->map_y;

	if (dda->side == 0)
	{
		// shrh f tldraw but ila bghiti t+is wahd lwall w line dyal is more vertical you need to move horizontaly
		player->hitx = player->posx + (dda->side_x - dda->delta_x) * player->raydirx;
		player->hity = player->posy + (dda->side_x - dda->delta_x) * player->raydiry;
		player->vertical = 1;
	}
	else
	{
		player->hitx = player->posx + (dda->side_y - dda->delta_y) * player->raydirx;
		player->hity = player->posy + (dda->side_y - dda->delta_y) * player->raydiry;
		player->vertical = 0;
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
		if (dda.side_x < dda.side_y)
		{
			dda.side_x += dda.delta_x;
			dda.map_x += dda.step_x;
			dda.side = 0;
		}
		else
		{
			dda.side_y += dda.delta_y;
			dda.map_y += dda.step_y;
			dda.side = 1;
		}
		if (dda.map_x < 0 || dda.map_x >= MAP_SIZE
			|| dda.map_y < 0 || dda.map_y >= MAP_SIZE)
			break;
		if (data->map[dda.map_y][dda.map_x] == '1')
			hit = 1;
	}
	if (hit)
		store_hit_info(player, &dda);
	return (hit);
}

void casting_rays(t_data *data, t_player *player)
{
    int r = 0;
    
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
