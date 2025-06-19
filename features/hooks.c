/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:24:07 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/19 18:36:38 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int close_program(t_data *data)
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
    exit(0);
    return (0);
}

int key_hook(int keycode, t_data *data)
{
    int shift_amount = 2;
    
    if (keycode == 65307)
        close_program(data);
    else if (keycode == 65361)
		data->offset_x -= shift_amount;
	else if (keycode == 65362)
		data->offset_y -= shift_amount;
	else if (keycode == 65363)
		data->offset_x += shift_amount;
	else if (keycode == 65364)
		data->offset_y += shift_amount;
    pixel(data);
    charachter(data);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return 0;
}

void setup_h(t_data *data)
{
    mlx_hook(data->win, 17, 0, &close_program, data);
    mlx_hook(data->win, 2, 1L<<0, &key_hook, data);
}
