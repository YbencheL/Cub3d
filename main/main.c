/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:13:35 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/25 18:53:16 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->sizel + x * (data->bbq / 8));
    *(unsigned int*)dst = color;
}

void casting_rays(t_data *data)
{
    int num_rays = 120;
    double fov = M_PI / 3.0;
    double ray_angle;
    double player_angle;
    double raydirX;
    double raydirY;
    double rayX;
    double rayY;
    double step_size;
    int hit;
    int max_steps;
    int drawX;
    int drawY;
    int mapx;
    int mapy;
    int r = 0;
    int i;
    
    player_angle = atan2(data->player->diry, data->player->dirx);
    while (r < num_rays)
    {
        ray_angle = player_angle - (fov / 2.0) + (fov * r) / (num_rays - 1);

        raydirX = cos(ray_angle);
        raydirY = sin(ray_angle);

        rayX = data->player->posx;
        rayY = data->player->posy;

        step_size = 0.01;
        hit = 0;
        max_steps = (int)(20.0 / step_size);
        i = 0;
        while (i < max_steps && !hit)
        {
            drawX = (int)(rayX * data->tile_size);
            drawY = (int)(rayY * data->tile_size);
            mapx = (int)rayX;
            mapy = (int)rayY;
            if (mapx < 0 || mapx >= MAP_SIZE || mapy < 0 || mapy >= MAP_SIZE)
                break;
            if (data->map[mapy][mapx] == '1')
                hit = 1;
            if (drawX >= 0 && drawX < data->width && drawY >= 0 && drawY < data->height)
                my_mlx_pixel_put(data, drawX, drawY, 0x00C000);
            rayX += raydirX * step_size;
            rayY += raydirY * step_size;
            i++;
        }
        r++;
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
    // double step = 0.0;
    // while (step < 5.0)
    // {
    //     int line_x = (int)((data->player->posx + data->player->dirx * step * 0.2) * data->tile_size);
    //     int line_y = (int)((data->player->posy + data->player->diry * step * 0.2) * data->tile_size);
    //     my_mlx_pixel_put(data, line_x, line_y, 0x00C000);
    //     step += 0.05;
    // }
    casting_rays(data);
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
    player->player_a = 3 * M_PI / 2;
    player->dirx = cos(player->player_a);
    player->diry = sin(player->player_a);
    player->planex = -player->diry * 0.33;
    player->planey = player->diry * 0.33;
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
