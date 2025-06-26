/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   charachter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:05:58 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/26 10:07:53 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void charachter(t_data *data)
{
    int rad = 10;
    int center_x = (int)(data->player->posx * data->tile_size);
    int center_y = (int)(data->player->posy * data->tile_size);
    int x;
    int y;
    int j;
    int i = -rad;

    while(i < rad)
    {
        j = -rad;
        while(j < rad)
        {
            x = center_x + i;
            y = center_y + j;
            if (i*i + j*j <= rad*rad)
            {
                if (x >= 0 && x < data->width && 
                    y >= 0 && y < data->height)
                {
                    my_mlx_pixel_put(data, x, y, 0x00C000);
                }
            }
            j++;
        }
        i++;
    }
    // double step = 0.0;
    // while (step < 5.0)
    // {
    //     int line_x = (int)((data->player->posx + data->player->dirx * step * 0.2) * data->tile_size);
    //     int line_y = (int)((data->player->posy + data->player->diry * step * 0.2) * data->tile_size);
    //     my_mlx_pixel_put(data, line_x, line_y, 0x00C000);
    //     step += 0.05;
    // }
    casting_rays(data, data->player);
    // raycasting_loop(data, data->player);
}