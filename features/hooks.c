/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:24:07 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/24 16:06:18 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int redraw(t_data *data)
{
    if (data->img)
        mlx_destroy_image(data->mlx, data->img);
    
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->addr = mlx_get_data_addr(data->img, &data->bbq, &data->sizel, &data->indian);
    
    pixel(data, data->map);
    charachter(data);
    mlx_put_image_to_window(data->mlx, data->win1, data->img, 0, 0);
    return 0;
}

int close_program(t_data *data)
{
    if (data->img)
    mlx_destroy_image(data->mlx, data->img);
    if (data->win1)
    mlx_destroy_window(data->mlx, data->win1);
    // if (data->win2)
    //     mlx_destroy_window(data->mlx, data->win2);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    free(data);
    free(data->player);
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
        player->posx += dx;
        player->posy += dy;
    }
}

// void move_player(t_data *data, double dx, double dy)
// {
//     data->player->posx += dx;
//     data->player->posy += dy;
// }

void rotate_player(t_data *data, double angle)
{
    data->player->player_a += angle;
    if (data->player->player_a < 0)
        data->player->player_a += 2 * M_PI;
    else if (data->player->player_a > 2 * M_PI)
        data->player->player_a -= 2 * M_PI;

    data->player->dirx = cos(data->player->player_a);
    data->player->diry = sin(data->player->player_a);
}

int key_hook(int keycode, t_data *data)
{
    double speed = 0.1;

    if (keycode == 65307)
        close_program(data);
    else if (keycode == 65361)
        rotate_player(data, -0.1);
    else if (keycode == 65362)
        move_player(data->player, data->player->dirx * speed, data->player->diry * speed, data->map);
    else if (keycode == 65363)
        rotate_player(data, 0.1);
    else if (keycode == 65364)
        move_player(data->player, -data->player->dirx * speed, -data->player->diry * speed, data->map);

    redraw(data);
    return 0;
}


void setup_h(t_data *data)
{
    mlx_hook(data->win1, 17, 0, &close_program, data);
    // mlx_hook(data->win2, 17, 0, &close_program, data);
    mlx_hook(data->win1, 2, 1L<<0, &key_hook, data);
    // mlx_hook(data->win2, 2, 1L<<0, &key_hook, data);
    mlx_loop_hook(data->mlx, redraw, data);
}
