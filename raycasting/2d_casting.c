/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_casting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:04:05 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/26 16:18:19 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int rendering_lines(t_data *data, t_player *player)
{
    int i = 0;
    int hit = 0;
    player->max_steps = (int)(20.0 / player->step_size);
    while (i < player->max_steps && !hit)
    {
        player->drawX = (int)(player->rayX * data->tile_size);
        player->drawY = (int)(player->rayY * data->tile_size);
        player->mapx = (int)player->rayX;
        player->mapy = (int)player->rayY;
        if (player->mapx < 0 || player->mapx >= MAP_SIZE || player->mapy < 0 || player->mapy >= MAP_SIZE)
            break;
        if (data->map[player->mapy][player->mapx] == '1')
        {
            player->hitx = player->rayX;
            player->hity = player->rayY;
            hit = 1;
            break;
        }
        // if (player->drawX >= 0 && player->drawX < data->width && player->drawY >= 0 && player->drawY < data->height)
        //     my_mlx_pixel_put(data, player->drawX, player->drawY, 0x87CEEB);
        player->rayX += player->raydirX * player->step_size;
        player->rayY += player->raydirY * player->step_size;
        i++;
    }
    return hit;
}

void casting_rays(t_data *data, t_player *player)
{
    int r = 0;
    
    player->player_angle = atan2(data->player->diry, data->player->dirx);
    player->num_rays = data->width;
    while (r < player->num_rays)
    {
        player->ray_angle = player->player_angle - (player->fov / 2.0)
            + (player->fov * r) / (player->num_rays - 1);

        player->raydirX = cos(player->ray_angle);
        player->raydirY = sin(player->ray_angle);

        player->rayX = data->player->posx;
        player->rayY = data->player->posy;

        player->step_size = 0.01;
        if (rendering_lines(data, player))
            casting_walls(data, player, r);
        r++;
    }
}
