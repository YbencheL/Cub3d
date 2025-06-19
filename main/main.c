/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:13:35 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/19 18:31:07 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->sizel + x * (data->bbq / 8));
    *(unsigned int*)dst = color;
}

void charachter(t_data *data)
{
    int rad = 30;
    int center_x = 450 + data->offset_x;
    int center_y = 450 + data->offset_y;
    int x;
    int y;
    int j = -rad;
    int i = -rad;

    while(i < rad)
    {
        j = -rad;
        while(j < rad)
        {
            if (i*i + j*j <= rad*rad)
            {
                x = center_x + i;
                y = center_y + j;
                if (x >= 0 && x < data->width && 
                    y >= 0 && y < data->height)
                    my_mlx_pixel_put(data, x, y, 0x00C000);
            }
            j++;
        }
        i++;
    }
}

void pixel(t_data *data)
{
    int i = 0, j = 0;
    int x, y;
    int tile_size = 100;
    int start_x;
    int start_y;
    int color;
    int original_color;
    int colors = 0xF0EAD6;
    int colora = 0x000000;
    int colorg = 0x808080;
    char *map[MAP_SIZE] = {
    "1111111111",
    "1000000001",
    "1011111101",
    "1000000001",
    "1111011111",
    "1000000001",
    "1000001001",
    "1010001001",
    "1100001001",
    "1111111111"
    };


    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->addr = mlx_get_data_addr(data->img, &data->bbq, &data->sizel, &data->indian);
    x = 0;
    while(x < MAP_SIZE)
    {
        y = 0;
        while(y < MAP_SIZE)
        {
            if (map[y][x] == '1')
                original_color = colorg;
            else
                original_color = colors;
            i = 0;
            while(i < tile_size)
            {
                j = 0;
                while(j < tile_size)
                {
                    color = original_color;
                    if ((i == 1 || i == 0) || (i == tile_size - 2 || i == tile_size - 1)
                        || (j == 1 || j == 0) || (j == tile_size - 2 || j ==  tile_size - 1))
                        color = colora;
                    start_x = x * tile_size + j;
                    start_y = y * tile_size + i;
                    if (start_x < data->width && start_y < data->height)
                        my_mlx_pixel_put(data, start_x, start_y, color);
                    j++;
                }
                i++;
            }
            y++;
        }
        x++;
    }
}

int main()
{
    t_data *data;
    
    data = malloc(sizeof(t_data));
    
    data->img = NULL;
    data->addr = NULL;
    data->height = 1000;
    data->width = 1000;
    data->offset_x = 0;
    data->offset_y = 0;
    
    data->mlx = mlx_init();
    
    data->win = mlx_new_window(data->mlx, data->height, data->width, "qub3d");

    pixel(data);
    charachter(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    setup_h(data);
    mlx_loop(data->mlx);
    
    return 0;
}