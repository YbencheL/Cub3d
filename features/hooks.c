/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:24:07 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/21 11:35:43 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

static void redraw(t_data *data)
{
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->addr = mlx_get_data_addr(data->img, &data->bbq, &data->sizel, &data->indian);
    
    pixel(data, data->map);
    charachter(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
}

int close_program(t_data *data, t_player *player)
{
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    if (data->win)
        mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    free(data);
    free(player);
    exit(0);
    return (0);
}

void move_player(t_player *player, double dx, double dy, char **map)
{
    double new_x = player->posx + dx;
    double new_y = player->posy + dy;
    
    int map_x = (int)new_x;
    int map_y = (int)new_y;
    
    if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE && 
        map[map_y][map_x] != '1') {
        player->posx = new_x;
        player->posy = new_y;
    }
}

int key_hook(int keycode, t_data *data)
{
    double move_amount = 0.1;
    
    if (keycode == 65307)
        close_program(data, data->player);
    else if (keycode == 65361)
        move_player(data->player, -move_amount, 0, data->map);
    else if (keycode == 65362)
        move_player(data->player, 0, -move_amount, data->map);
    else if (keycode == 65363)
        move_player(data->player, move_amount, 0, data->map);
    else if (keycode == 65364)
        move_player(data->player, 0, move_amount, data->map);
    
    redraw(data);
        
    return 0;
}

void setup_h(t_data *data)
{
    mlx_hook(data->win, 17, 0, &close_program, data);
    mlx_hook(data->win, 2, 1L<<0, &key_hook, data);
}
