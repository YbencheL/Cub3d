/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rizzing_up_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/29 10:56:30 by ybenchel         ###   ########.fr       */
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

// void textures_logic(t_data *data, t_player *player)
// {
    
// }

void casting_walls(t_data *data, t_player *player, int ray_indx)
{
    double dx;
    double dy;
    double projection_plane_d;
    double wall_height;
    int y;
    
    dx = player->hitx - player->posx;
    dy = player->hity - player->posy;
    player->distance = dx * player->dirx + dy * player->diry;

    projection_plane_d = (data->width / 2) / tan(player->fov / 2);
    wall_height = (projection_plane_d * 1) / player->distance;
    player->draw_start = (data->height / 2) - (wall_height / 2);
    player->draw_end = (data->height / 2) + (wall_height / 2);
    if (player->draw_start < 0)
        player->draw_start = 0;
    if (player->draw_end >= data->height)
        player->draw_end = data->height - 1;
    y = 0;
    int color = shade_color(0x0000D1, player->distance);
    while (y < player->draw_start)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colors);
        y++;
    }
    while (y < player->draw_end)
    {
        my_mlx_pixel_put(data, ray_indx, y, color);
        y++;
    }
    while (y < data->height)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colorg);
        y++;
    }
}
