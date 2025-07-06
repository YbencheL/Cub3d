/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2d_map_rendering.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:05:19 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/06 10:11:19 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void pix_by_pix_rendiring(t_data *data, int x, int y, int original_color)
{
    int i = 0;
    int j;
    int start_x;
    int start_y;
    int color;
    
    while(i < data->tile_size)
    {
        j = 0;
        while(j < data->tile_size)
        {
            color = original_color;
            if ((i == 1 || i == 0) || (i == data->tile_size - 2 || i == data->tile_size - 1)
                || (j == 1 || j == 0) || (j == data->tile_size - 2 || j ==  data->tile_size - 1))
                color = data->colora;
            start_x = x * data->tile_size - data->offset_x;
            start_y = y * data->tile_size - data->offset_y;
            // start_x = x * data->tile_size + i;
            // start_y = y * data->tile_size + j;
            if (start_x + data->tile_size >= 0 && start_x < data->width &&
                start_y + data->tile_size >= 0 && start_y < data->height)
                my_mlx_pixel_put(data, start_x, start_y, color);
            j++;
        }
        i++;
    }
}

void pixel(t_data *data, char **map)
{
    int x, y;
    int original_color;

    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
        
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->addr = mlx_get_data_addr(data->img, &data->bbq, &data->sizel, &data->indian);
    y = 0;
    data->offset_x = data->player->posx * data->tile_size - data->width / 2;
    data->offset_y = data->player->posy * data->tile_size - data->height / 2;
    while(y < MAP_SIZE)
    {
        x = 0;
        while(x < MAP_SIZE)
        {
            if (map[y][x] == '1')
                original_color = data->colorg;
            else
                original_color = data->colors;
            pix_by_pix_rendiring(data, x, y, original_color);
            x++;
        }
        y++;
    }
}
