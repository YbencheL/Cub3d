/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_puting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:06:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/24 09:41:19 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (data == NULL)
		return ;
	if (data->height <= y || data->width <= x)
		return ;
	if (y < 0 || x < 0)
		return ;
	dst = data->addr + (y * data->sizel + x * (data->bbq / 8));
	*(unsigned int *)dst = color;
}

int	redraw(t_data *data)
{
	handle_input(data);
	casting_rays(data, data->player);
	mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
	return (0);
}
