/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_check_v0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:33:46 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/08/06 15:28:41 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_arg(int ac, char **av)
{
	char	*argv;
	int		len;

	if (ac != 2)
	{
		ft_putendl_fd("ERROR: INPUT PROBLEM", 2);
		exit(1);
	}
	len = ft_strlen(av[1]);
	if (len <= 4)
	{
		ft_putendl_fd("ERROR: INPUT PROBLEM", 2);
		exit(1);
	}
	argv = av[1];
	if (!ft_strnstr(argv + len - 4, ".cub", 4))
	{
		ft_putendl_fd("ERROR: INPUT PROBLEM", 2);
		exit(1);
	}
	if (ft_strnstr(argv + len - 5, "/", 1))
	{
		ft_putendl_fd("ERROR: INPUT PROBLEM", 2);
		exit(1);
	}
}

void	check_map_plus(t_cub *game)
{
	check_top(game);
	check_middle(game);
	check_bottom(game);
}

int	check_char(t_cub *game, int l)
{
	char	**map;
	int		i;
	int		dr;

	dr = 0;
	while (game->file[l])
	{
		map = ft_split(game->file[l]);
		check_newline(game, map);
		i = 0;
		while (map[i])
		{
			check_char_in_line(game, map, map[i], &dr);
			i++;
		}
		free_split(map);
		l++;
	}
	if (dr != 1)
	{
		ft_putendl_fd("ERROR: INVALID PLAYER", 2);
		ft_free(game, 1);
	}
	return (l);
}
