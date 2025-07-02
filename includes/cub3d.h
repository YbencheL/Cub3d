/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:19:03 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/02 13:31:02 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef CUB3D_H
# define CUB3D_H

#define MAP_SIZE 8
#define NUM_KEYS 70000 
#define M_PI 3.14159265358979323846


// #include "../minilibx-linux/mlx.h"
#include "mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../get_next_line/get_next_line.h"
#include "../libft/libft.h"

typedef struct s_cub
{
    char **file;
    char **map;
    char **map_plus;
    int row;
    int col;
    char *no;
    char *so;
    char *we;
    char *ea;
    char *f;
    char *c;
    char d;
}t_cub;

typedef enum s_directions
{
    WEST,
    EAST,
    NORTH,
    SOUTH
} t_directions;

typedef struct s_textures
{
    void    *img;
    char    *addr;
    int     height;
    int     width;
    int     bbq;
    int     indian;
    int     sizel;
} t_textures;

typedef struct s_player
{
    double  posx;
    double  posy;
    double  dirx;
    double  diry;
    double  planex;
    double  planey;
    double  player_a;
    int     num_rays;
    double  fov;
    double  ray_angle;
    double  player_angle;
    double  raydirX;
    double  raydirY;
    double  rayX;
    double  rayY;
    double  step_size;
    int     max_steps;
    int     drawX;
    int     drawY;
    int     mapx;
    int     mapy;
    double  hitx;
    double  hity;
    double  draw_start;
    double  draw_end;
    double  distance;
    int     vertical;
} t_player;

typedef struct s_data
{
    void        *mlx;
    void        *win;
    void        *win1;
    void        *img;
    char        *addr;
    int         height;
    int         width;
    int         bbq;
    int         indian;
    int         sizel;
    int         offset_x;
    int         offset_y;
    int         colors;
    int         colora;
    int         colorg;
    int         tile_size;
    char        **map;
    int         key_states[NUM_KEYS];
    t_player    *player;
    t_textures  west;
    t_textures  east;
    t_textures  north;
    t_textures  south;
} t_data;

//------------------features------------------------
void    handle_input(t_data *data);
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

//------------------parsing----------------------
void    ft_parsing(t_cub *game, char *av);
void copy_map(t_cub *game, int i, int l);
void check_arg(int ac, char **av);
void check_map_plus(t_cub *game);
int check_char(t_cub *game, int l);
int conut_split(char **line);
void conut_col(t_cub *game, int i);
void conut_row(t_cub *game, char *av);
int skip_newline(t_cub *game, int l);
void flood_fill(t_cub *game, int x, int y);
void run_flood_fill(t_cub *game);
void read_file(t_cub *game, char *av);
int stor_texture(t_cub *game);
void init_struct(t_cub *file);

#endif