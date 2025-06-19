/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:19:03 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/19 18:27:54 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define MAP_SIZE 10

#include "../minilibx-linux/mlx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
} t_data;

//------------------features----------------------
int close_program(t_data *data);
int key_hook(int keycode, t_data *data);
void setup_h(t_data *data);
//------------------main----------------------
void pixel(t_data *data);
void charachter(t_data *data);
