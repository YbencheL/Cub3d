/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 23:03:06 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/23 20:34:16 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	parse_rgb(char *str, int r, int g, int b)
{
	char	**split;

	split = ft_split_plus(str, ',');
	if (conut_split(split) != 3)
	{
		free_split(split);
		return (-1);
	}
	if (!is_number(split[0]) || !is_number(split[1]) || !is_number(split[2]))
	{
		free_split(split);
		return (-1);
	}
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
	{
		free_split(split);
		return (-1);
	}
	free_split(split);
	return ((r << 16) | (g << 8) | b);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] == ' ')
		i++;
	if (str[i] == '\0')
		return (0);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

void	if_check(t_cub *game)
{
	if (!game->c || !game->f || !game->no || !game->so || !game->we
		|| !game->ea)
	{
		ft_putendl_fd("ERROR: INVALID TEXTURES", 2);
		ft_free(game, 1);
	}
	game->f_color = parse_rgb(game->f, 0, 0, 0);
	if (game->f_color == -1)
	{
		ft_putendl_fd("ERROR: INVALID COLOR", 2);
		ft_free(game, 1);
	}
	game->c_color = parse_rgb(game->c, 0, 0, 0);
	if (game->c_color == -1)
	{
		ft_putendl_fd("ERROR: INVALID COLOR", 2);
		ft_free(game, 1);
	}
}
