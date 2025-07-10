/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculating_dda_vals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:29:46 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/10 11:40:27 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_dda_delta(t_player *player, t_dda *dda)
{
    // delta hiya distance li khas lplayer ytravl bash ycrossi 1 vertical or horizontal line
	if (player->raydirx == 0)
		dda->delta_x = 0; // to not make it 0 cause 0 will cause the ray to stay allways in one line
	else
		dda->delta_x = fabs(1.0 / player->raydirx);
	if (player->raydiry == 0)
		dda->delta_y = 0;
	else
		dda->delta_y = fabs(1.0 / player->raydiry);
}

void	set_dda_stepx_sx(t_player *player, t_dda *dda)
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

void	set_dda_stepy_sy(t_player *player, t_dda *dda)
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

void	init_dda_vars(t_player *player, t_dda *dda)
{
	dda->map_x = (int)player->posx;
	dda->map_y = (int)player->posy;
	set_dda_delta(player, dda);
	set_dda_stepx_sx(player, dda);
	set_dda_stepy_sy(player, dda);
}
