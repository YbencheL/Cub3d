/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rizzing_up_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/10 11:54:59 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void selecting_texture_we(t_data *data, t_player *player, t_tex *tex)
{
    if (player->vertical && player->raydirx < 0) // WEST wall
    {
        tex->texture_addr = data->west.addr;
        tex->tex_width = data->west.width;
        tex->tex_height = data->west.height;
        tex->sizel = data->west.sizel;
        tex->bpp = data->west.bbq;
    }
    else if (player->vertical && player->raydirx >= 0) // EAST wall
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
    if (!player->vertical && player->raydiry < 0) // NORTH wall
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
    step = (double)data->tex->tex_height / player->wall_height;
    tex_pos = (player->draw_start - data->height / 2 + player->wall_height / 2) * step;
    y = player->draw_start;
    while (y <= player->draw_end)
    {
        tex_y = (int)tex_pos;
        //previntiw segfault
        if (tex_y < 0)
            tex_y = 0;
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
    double y;
    double wall_x;

    dx = player->hitx - player->posx;
    dy = player->hity - player->posy;
    player->distance = sqrt(dx * dx + dy * dy) * cos(player->ray_angle - player->player_angle);
    projection_plane_d = (data->width / 2.0) / tan(player->fov / 2.0);
    player->wall_height = (int)(projection_plane_d / player->distance);
    player->draw_start = (data->height / 2.0) - (player->wall_height / 2.0);
    player->draw_end = (data->height / 2.0) + (player->wall_height / 2.0);
    //drawi gha flhodo dyal screen
    if (player->draw_start < 0)
        player->draw_start = 0;
    if (player->draw_end >= data->height)
        player->draw_end = data->height - 1;
    if (player->vertical)
        wall_x = player->hity;
    else
        wall_x = player->hitx;
    wall_x -= floor(wall_x);
    y = 0.0;
    // int color = shade_color(0x0000D1, player->distance);
    while (y < player->draw_start)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colors);
        y++;
    }
    textures_logic(data, player, ray_indx, wall_x);
    // while (y < player->draw_end)
    // {
    //     my_mlx_pixel_put(data, ray_indx, y, color);
    //     y++;
    // }
    y = player->draw_end;
    while (y < data->height)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colorg);
        y++;
    }
}
