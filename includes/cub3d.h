/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:19:03 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/26 16:18:08 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAP_SIZE 8
#define LINE_LENGTH 8
#define M_PI 3.14159265358979323846


#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

typedef struct s_player
{
    double posx;
    double posy;
    double dirx;
    double diry;
    double planex;
    double planey;
    double player_a;
    int num_rays;
    double fov;
    double ray_angle;
    double player_angle;
    double raydirX;
    double raydirY;
    double rayX;
    double rayY;
    double step_size;
    int max_steps;
    int drawX;
    int drawY;
    int mapx;
    int mapy;
    double hitx;
    double hity;
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

//------------------features------------------------
int     key_hook(int keycode, t_data *data);
void    setup_h(t_data *data);
int     close_program(t_data *data);
void    move_player(t_player *player, double dx, double dy, char **map);
void    rotate_player(t_data *data, double angle, char **map);

//------------------main----------------------------
void    pixel(t_data *data, char **map);
void    charachter(t_data *data);

//------------------utils---------------------------
int     redraw(t_data *data);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);

//------------------raycasting----------------------
void    casting_rays(t_data *data, t_player *player);
void    casting_walls(t_data *data, t_player *player, int ray_indx);