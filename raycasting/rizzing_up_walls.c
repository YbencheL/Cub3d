/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rizzing_up_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/26 16:19:41 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void casting_walls(t_data *data, t_player *player, int ray_indx)
{
    double dx;
    double dy;
    double distance;
    double projection_plane_d;
    double wall_height;
    double draw_start;
    double draw_end;
    int y;
    
    dx = player->hitx - player->posx;
    dy = player->hity - player->posy;
    distance = dx * player->dirx + dy * player->diry;

    projection_plane_d = (data->width / 2) / tan(player->fov / 2);
    wall_height = (projection_plane_d * 1) / distance;
    draw_start = (data->height / 2) - (wall_height / 2);
    draw_end = (data->height / 2) + (wall_height / 2);
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= data->height)
        draw_end = data->height - 1;
    y = 0;
    while (y < draw_start)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colors);
        y++;
    }
    while (y < draw_end)
    {
        my_mlx_pixel_put(data, ray_indx, y, 0x00C000);
        y++;
    }
    while (y < data->height)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colorg);
        y++;
    }
}
