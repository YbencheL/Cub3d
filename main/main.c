/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:13:35 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/24 15:36:36 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->sizel + x * (data->bbq / 8));
    *(unsigned int*)dst = color;
}

// void raycasting_loop(t_data *data, t_player *player)
// {

// }

void casting_rays(t_data *data, int startX, int startY)
{
    int i = 0;
    double x = startX;
    double y = startY;
    double diroffY = data->player->diry * data->height;
    double diroffX = data->player->dirx * data->width;
    double endX = x + diroffX;
    double endY = y + diroffY;
    double dX = endX - x;
    double dY = endY - y;
    int mapX;
    int mapY;
    int steps = fmax(fabs(dX), fabs(dY));
    double increment_x = dX / steps;
    double increment_y = dY / steps;

    while (i < steps)
    {
        mapX = (int)(x / data->tile_size);
        mapY = (int)(y / data->tile_size);

        if (mapX < 0 || mapX >= data->width || mapY < 0 || mapY >= data->height)
            break;
        if (data->map[mapY][mapX] == '1')
            break;
        my_mlx_pixel_put(data, x, y, 0x00C000);
        x += increment_x;
        y += increment_y;
        i++;
    }
}

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
    casting_rays(data, center_x, center_y);
    // raycasting_loop(data, data->player);
}

void player_pos(t_player *player, char **map)
{
    int y = 0,x;
    while(y < MAP_SIZE)
    {
        x = 0;
        while(x < MAP_SIZE)
        {
            if (map[y][x] == 'P')
            {
                player->posx = (double)x + 0.5;
                player->posy = (double)y + 0.5;
                return;
            }
            x++;
        }
        y++;
    }
}

void pixel(t_data *data, char **map)
{
    int i = 0, j = 0;
    int x, y;
    int start_x;
    int start_y;
    int color;
    int original_color;

    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
        
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->addr = mlx_get_data_addr(data->img, &data->bbq, &data->sizel, &data->indian);
    y = 0;
    while(y < MAP_SIZE)
    {
        x = 0;
        while(x < MAP_SIZE)
        {
            if (map[y][x] == '1')
                original_color = data->colorg;
            else
                original_color = data->colors;
            i = 0;
            while(i < data->tile_size)
            {
                j = 0;
                while(j < data->tile_size)
                {
                    color = original_color;
                    if ((i == 1 || i == 0) || (i == data->tile_size - 2 || i == data->tile_size - 1)
                        || (j == 1 || j == 0) || (j == data->tile_size - 2 || j ==  data->tile_size - 1))
                        color = data->colora;
                    start_x = x * data->tile_size + j;
                    start_y = y * data->tile_size + i;
                    if (start_x < data->width && start_y < data->height)
                        my_mlx_pixel_put(data, start_x, start_y, color);
                    j++;
                }
                i++;
            }
            x++;
        }
        y++;
    }
}

int main()
{
    t_data *data;
    t_player *player;
    
    char *map[MAP_SIZE] = {
    "11111111",
    "10100001",
    "10000101",
    "10000101",
    "10000001",
    "10001111",
    "110P0001",
    "11111111",
    };

    data = malloc(sizeof(t_data));
    player = malloc(sizeof(t_player));
    player->posx = 0.0;
    player->posy = 0.0;
    player->player_a = -M_PI / 2;
    player->dirx = cos(player->player_a);
    player->diry = sin(player->player_a);
    player->planex = 0.0;
    player->planey = 0.66;
    data->map = map;
    data->player = player;
    data->img = NULL;
    data->addr = NULL;
    data->colors = 0xF0EAD6;
    data->colora = 0x000000;
    data->colorg = 0x808080;
    data->tile_size = 100;
    data->height = 800;
    data->width = 800;
    data->offset_x = 0;
    data->offset_y = 0;
    
    data->mlx = mlx_init();
    
    // data->win2 = mlx_new_window(data->mlx, data->height, data->width, "qub3d");
    data->win1 = mlx_new_window(data->mlx, data->height, data->width, "qub3d mini map");
    player_pos(player, map);
    pixel(data, data->map);
    charachter(data);
    mlx_put_image_to_window(data->mlx, data->win1, data->img, 0, 0);
    setup_h(data);
    mlx_loop(data->mlx);
    
    return 0;
}
