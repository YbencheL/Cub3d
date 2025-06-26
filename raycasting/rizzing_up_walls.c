/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rizzing_up_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/26 13:28:40 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void casting_walls(t_data *data, t_player *player, int ray_indx)
{
    double dx = player->hitx - player->posx;
    double dy = player->hity - player->posy;
    double distance = dx * player->dirx + dy * player->diry;

    double projection_plane_d = (data->width / 2) / tan(player->fov / 2);
    double wall_height = (projection_plane_d * data->tile_size) / distance;

    double draw_start = (data->height / 2) - (wall_height / 2);
    double draw_end = (data->height / 2) + (wall_height / 2);

    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= data->height)
        draw_end = data->height - 1;
    int x = ray_indx;
    int y = draw_start;
    while (y <= draw_end)
    {
        my_mlx_pixel_put(data, x, y, 0x00C000);
        y++;
    }
}
