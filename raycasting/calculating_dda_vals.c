/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculating_dda_vals.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/10 11:29:46 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/16 18:00:32 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	set_dda_delta(t_player *player, t_dda *dda)
{
	if (player->raydirx == 0)
		dda->delta_x = 1e30;
	else
		dda->delta_x = fabs(1.0 / player->raydirx);
	if (player->raydiry == 0)
		dda->delta_y = 1e30;
	else
		dda->delta_y = fabs(1.0 / player->raydiry);
}

void	set_dda_stepx_sidex(t_player *player, t_dda *dda)
{
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

void	set_dda_stepy_sidey(t_player *player, t_dda *dda)
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
	set_dda_stepx_sidex(player, dda);
	set_dda_stepy_sidey(player, dda);
}
