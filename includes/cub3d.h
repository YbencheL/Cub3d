/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:19:03 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/22 11:52:01 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAP_SIZE 8
#define LINE_LENGTH 8

#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_player
{
    double posx;
    double posy;
} t_player;

typedef struct s_data
{
    void *mlx;
    void *win1;
    void *win2;
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
