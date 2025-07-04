/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rizzing_up_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/05 13:48:35 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int shade_color(int base_color, double distance)
{
    double factor = 1.0 / (1.0 + distance * 0.1);
    int r = ((base_color >> 16) & 0xFF) * factor;
    int g = ((base_color >> 8) & 0xFF) * factor;
    int b = (base_color & 0xFF) * factor;
    return (r << 16) | (g << 8) | b;
}

// void textures_logic(t_data *data, t_player *player, int ray_indx)
// {
    
// }

void selecting_texture_we(t_data *data, t_player *player, t_tex *tex)
{
    if (player->vertical && player->raydirX < 0) // WEST wall
    {
        tex->texture_addr = data->west.addr;
        tex->tex_width = data->west.width;
        tex->tex_height = data->west.height;
        tex->sizel = data->west.sizel;
        tex->bpp = data->west.bbq;
    }
    else if (player->vertical && player->raydirX >= 0) // EAST wall
    {
        tex->texture_addr = data->east.addr;
        tex->tex_width = data->east.width;
        tex->tex_height = data->east.height;
        tex->sizel = data->east.sizel;
        tex->bpp = data->east.bbq;
    }
}

void selecting_texture_ns(t_data *data, t_player *player, t_tex *tex)
{
    if (!player->vertical && player->raydirY < 0) // NORTH wall
    {
        tex->texture_addr = data->north.addr;
        tex->tex_width = data->north.width;
        tex->tex_height = data->north.height;
        tex->sizel = data->north.sizel;
        tex->bpp = data->north.bbq;
    }
    else // SOUTH wall
    {
        tex->texture_addr = data->south.addr;
        tex->tex_width = data->south.width;
        tex->tex_height = data->south.height;
        tex->sizel = data->south.sizel;
        tex->bpp = data->south.bbq;
    }
}

void textures_logic(t_data *data, t_player *player, int ray_indx, double wall_x)
{
    int tex_x;
    double draw_start;
    double draw_end;
    double wall_height;
    double step;
    double tex_pos;
    double y;
    int tex_y;
    int color;
    
	if (player->vertical)
		selecting_texture_we(data, player, data->tex);
	else
		selecting_texture_ns(data, player, data->tex);
    tex_x = (int)(wall_x * data->tex->tex_width);
    draw_start = player->draw_start;
    draw_end = player->draw_end;
    if (draw_start < 0) draw_start = 0;
    if (draw_end >= data->height) draw_end = data->height - 1;
    wall_height = draw_end - draw_start;
    step = data->tex->tex_height / wall_height;
    tex_pos = (draw_start - data->height / 2 + wall_height / 2) * step;

    y = draw_start;
    while (y <= draw_end)
    {
        tex_y = (int)tex_pos;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= data->tex->tex_height) tex_y = data->tex->tex_height - 1;

        color = *(unsigned int *)(data->tex->texture_addr +
                    tex_y * data->tex->sizel +
                    tex_x * (data->tex->bpp / 8));
        my_mlx_pixel_put(data, ray_indx, y, color);
        tex_pos += step;
        y++;
    }
}

void casting_walls(t_data *data, t_player *player, int ray_indx)
{
    double dx;
    double dy;
    double projection_plane_d;
    double wall_height;
    int y;
    double wall_x;

    dx = player->hitx - player->posx;
    dy = player->hity - player->posy;
    player->distance = sqrt(dx * dx + dy * dy) * cos(player->ray_angle - player->player_angle);
    projection_plane_d = (data->width / 2.0) / tan(player->fov / 2.0);
    wall_height = (projection_plane_d) / player->distance;
    player->draw_start = (data->height / 2.0) - (wall_height / 2.0);
    player->draw_end = (data->height / 2.0) + (wall_height / 2.0);
    if (player->draw_start < 0)
        player->draw_start = 0;
    if (player->draw_end >= data->height)
        player->draw_end = data->height - 1;
    if (player->vertical)
        wall_x = player->hity;
    else
        wall_x = player->hitx;
    wall_x -= floor(wall_x);
    y = 0;
    int color = shade_color(0x0000D1, player->distance);
    while (y < player->draw_start)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colors);
        y++;
    }
    // textures_logic(data, player, ray_indx, wall_x);
    while (y < player->draw_end)
    {
        my_mlx_pixel_put(data, ray_indx, y, color);
        y++;
    }
    y = (int)player->draw_end;
    while (y < data->height)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colorg);
        y++;
    }
}
