/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_logic.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 11:22:07 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/23 13:41:06 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	selecting_texture_we(t_data *data, t_player *player, t_tex *tex)
{
	if (player->vertical && player->raydirx < 0)
	{
		tex->texture_addr = data->west.addr;
		tex->tex_width = data->west.width;
		tex->tex_height = data->west.height;
		tex->sizel = data->west.sizel;
		tex->bpp = data->west.bbq;
	}
	else if (player->vertical && player->raydirx >= 0)
	{
		tex->texture_addr = data->east.addr;
		tex->tex_width = data->east.width;
		tex->tex_height = data->east.height;
		tex->sizel = data->east.sizel;
		tex->bpp = data->east.bbq;
	}
}

void	selecting_texture_ns(t_data *data, t_player *player, t_tex *tex)
{
	if (!player->vertical && player->raydiry < 0)
	{
		tex->texture_addr = data->north.addr;
		tex->tex_width = data->north.width;
		tex->tex_height = data->north.height;
		tex->sizel = data->north.sizel;
		tex->bpp = data->north.bbq;
	}
	else if (!player->vertical && player->raydiry >= 0)
	{
		tex->texture_addr = data->south.addr;
		tex->tex_width = data->south.width;
		tex->tex_height = data->south.height;
		tex->sizel = data->south.sizel;
		tex->bpp = data->south.bbq;
	}
}

void	tex_loop(t_player *player, t_texinfo *info, t_data *data, int ray_indx)
{
	double	y;
	int		tex_y;
	int		color;

	y = player->draw_start;
	while (y <= player->draw_end)
	{
		tex_y = (int)info->tex_pos;
		if (tex_y < 0)
			tex_y = 0;
		else
		{
			color = *(unsigned int *)(data->tex->texture_addr + tex_y
					* data->tex->sizel + info->tex_x * (data->tex->bpp / 8));
		}
		my_mlx_pixel_put(data, ray_indx, y, color);
		info->tex_pos += info->step;
		y++;
	}
}

void	textures_logic(t_data *data, t_player *player, int ray_indx,
		double wall_x)
{
	t_texinfo	info;

	if (player->vertical)
		selecting_texture_we(data, player, data->tex);
	else
		selecting_texture_ns(data, player, data->tex);
	info.tex_x = (int)(wall_x * data->tex->tex_width);
	info.step = (double)data->tex->tex_height / player->wall_height;
	info.tex_pos = (player->draw_start - data->height / 2 + player->wall_height
			/ 2) * info.step;
	tex_loop(player, &info, data, ray_indx);
}
