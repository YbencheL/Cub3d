/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_puting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:06:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/01 17:08:06 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char	*dst;

    dst = data->addr + (y * data->sizel + x * (data->bbq / 8));
    *(unsigned int*)dst = color;
}

int redraw(t_data *data)
{
    handle_input(data);
    if (data->img) 
        mlx_destroy_image(data->mlx, data->img);
    
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->addr = mlx_get_data_addr(data->img, &data->bbq, &data->sizel, &data->indian);
    
    // pixel(data, data->map);
    // charachter(data);
    casting_rays(data, data->player);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    return 0;
}
