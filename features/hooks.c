/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:24:07 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/29 15:22:26 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include "mlx.h"

int close_program(t_data *data)
{
    if (data->north.img)
        mlx_destroy_image(data->mlx, data->north.img);
    if (data->south.img)
        mlx_destroy_image(data->mlx, data->south.img);
    if (data->west.img)
        mlx_destroy_image(data->mlx, data->west.img);
    if (data->east.img)
        mlx_destroy_image(data->mlx, data->east.img);
    if (data->img)
    mlx_destroy_image(data->mlx, data->img);
    if (data->win)
    mlx_destroy_window(data->mlx, data->win);
    if (data->mlx)
    {
        mlx_destroy_display(data->mlx);
        free(data->mlx);
    }
    free(data->player);
    free(data);
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

void rotate_player(t_data *data, double angle, char **map)
{
    int map_x = (int)data->player->posx;
    int map_y = (int)data->player->posy;
    
    if (map_x >= 0 && map_x < MAP_SIZE && map_y >= 0 && map_y < MAP_SIZE && 
        map[map_y][map_x] != '1')
    {
        data->player->player_a += angle;
        if (data->player->player_a < 0)
            data->player->player_a += 2 * M_PI;
        else if (data->player->player_a > 2 * M_PI)
            data->player->player_a -= 2 * M_PI;
        data->player->dirx = cos(data->player->player_a);
        data->player->diry = sin(data->player->player_a);
    }
}

int key_press(int keycode, t_data *data)
{
    if (keycode >= 0 && keycode < NUM_KEYS)
        data->key_states[keycode] = 1;
    return 0;
}

int key_release(int keycode, t_data *data)
{
    if (keycode >= 0 && keycode < NUM_KEYS)
        data->key_states[keycode] = 0;
    return 0;
}

void handle_input(t_data *data)
{
    double speed = 0.02;
    if (data->key_states[65307])
        close_program(data);
    if (data->key_states[65361])
        rotate_player(data, -0.04, data->map);
    if (data->key_states[119])
        move_player(data->player, data->player->dirx * speed, data->player->diry * speed, data->map);
    if (data->key_states[65363])
        rotate_player(data, 0.04, data->map);
    if (data->key_states[115])
        move_player(data->player, -data->player->dirx * speed, -data->player->diry * speed, data->map);
    if (data->key_states[100])
        move_player(data->player, -data->player->diry * speed, data->player->dirx * speed, data->map);
    if (data->key_states[97])
        move_player(data->player, data->player->diry * speed, -data->player->dirx * speed, data->map);
}

void setup_h(t_data *data)
{
    mlx_hook(data->win, 17, 0, &close_program, data);
    mlx_hook(data->win, 2, 1L<<0, &key_press, data);
    mlx_hook(data->win, 3, 1L<<1, &key_release, data);
    mlx_loop_hook(data->mlx, redraw, data);
}

