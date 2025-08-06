/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_check_v1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 20:15:42 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/08/06 15:29:16 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_top(t_cub *game)
{
	int	i;

	i = 0;
	while (game->map_plus[0][i])
	{
		if (game->map_plus[0][i] == 'X')
		{
			ft_putendl_fd("ERROR: INVALID MAP", 2);
			ft_free(game, 1);
		}
		i++;
	}
}

void	check_middle(t_cub *game)
{
	int	i;
	int	l;

	i = 1;
	while (game->map_plus[i])
	{
		l = 0;
		while (game->map_plus[i][l])
			l++;
		if (game->map_plus[i][0] == 'X' || game->map_plus[i][l - 1] == 'X')
		{
			ft_putendl_fd("ERROR: INVALID MAP", 2);
			ft_free(game, 1);
		}
		i++;
	}
}

void	check_bottom(t_cub *game)
{
	int	i;

	i = 0;
	while (game->map_plus[game->row - 1][i])
	{
		if (game->map_plus[game->row - 1][i] == 'X')
		{
			ft_putendl_fd("ERROR: INVALID MAP", 2);
			ft_free(game, 1);
		}
		i++;
	}
}

void	check_newline(t_cub *game, char **map)
{
	if (conut_split(map) == 0)
	{
		ft_putendl_fd("ERROR: NEWLINE", 2);
		free_split(map);
		ft_free(game, 1);
	}
}

void	check_char_in_line(t_cub *game, char **map, char *line, int *dr)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (!ft_strchr("10", line[i]))
		{
			if (ft_strchr("NSWE", line[i]))
			{
				game->d = line[i];
				(*dr)++;
			}
			else
			{
				ft_putendl_fd("ERROR: INVALID CHAR", 2);
				free_split(map);
				ft_free(game, 1);
			}
		}
		i++;
	}
}
