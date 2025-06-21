/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:19:03 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/21 11:35:25 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAP_SIZE 8

#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_player
{
    double posx;
    double posy;
    double dirx;
    double diry;
    double planx;
    double plany;
} t_player;

typedef struct s_data
{
    void *mlx;
    void *win;
    void *img;
    char *addr;
    int height;
    int width;
    int bbq;
    int indian;
    int sizel;
    int offset_x;
    int offset_y;
    int colors;
    int colora;
    int colorg;
    int tile_size;
    char **map;
    t_player *player;
} t_data;


//------------------features----------------------
int key_hook(int keycode, t_data *data);
void setup_h(t_data *data);
int close_program(t_data *data, t_player *player);
//------------------main----------------------
void pixel(t_data *data, char **map);
void charachter(t_data *data);
void move_player(t_player *player, double dx, double dy, char **map);
