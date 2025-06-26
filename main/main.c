/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:13:35 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/26 16:03:33 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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

void init_vars(t_data *data, t_player *player)
{
    player->posx = 0.0;
    player->posy = 0.0;
    player->num_rays = 60;
    player->fov = M_PI / 3.0;
    player->player_a = 3 * M_PI / 2;
    player->dirx = cos(player->player_a);
    player->diry = sin(player->player_a);
    player->planex = -player->diry * 0.33;
    player->planey = player->diry * 0.33;
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
    "10P00001",
    "10001111",
    "11000001",
    "11111111",
    };

    data = malloc(sizeof(t_data));
    player = malloc(sizeof(t_player));
    data->map = map;
    init_vars(data, player);
    data->mlx = mlx_init();
    
    data->win = mlx_new_window(data->mlx, data->height, data->width, "qub3d mini map");
    player_pos(player, map);
    pixel(data, data->map);
    charachter(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    setup_h(data);
    mlx_loop(data->mlx);
    
    return 0;
}
