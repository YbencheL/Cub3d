/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/16 18:02:46 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/21 14:28:15 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	handle_input(t_data *data)
{
	double	speed;

	speed = 0.02;
	if (data->key_states[65307])
		close_program(data);
	if (data->key_states[65361])
		rotate_player(data, -0.015, data->map);
	if (data->key_states[119])
		move_player(data, data->player->dirx * speed, data->player->diry
			* speed, data->map);
	if (data->key_states[65363])
		rotate_player(data, 0.015, data->map);
	if (data->key_states[115])
		move_player(data, -data->player->dirx * speed,
			-data->player->diry * speed, data->map);
	if (data->key_states[100])
		move_player(data, -data->player->diry * speed,
			data->player->dirx * speed, data->map);
	if (data->key_states[97])
		move_player(data, data->player->diry * speed,
			-data->player->dirx * speed, data->map);
}

void	setup_h(t_data *data)
{
	mlx_hook(data->win, 17, 0, &close_program, data);
	mlx_hook(data->win, 2, 1L << 0, &key_press, data);
	mlx_hook(data->win, 3, 1L << 1, &key_release, data);
	mlx_loop_hook(data->mlx, redraw, data);
}
