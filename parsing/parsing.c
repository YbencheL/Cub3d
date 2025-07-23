/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 23:03:27 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/23 20:29:34 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	ft_parsing(t_cub *game, char *av)
{
	int	i;
	int	l;

	i = 0;
	init_struct(game);
	conut_row(game, av);
	read_file(game, av);
	i = stor_texture(game);
	if_check(game);
	i++;
	i = skip_newline(game, i);
	l = i;
	i = check_char(game, i);
	game->row = i - l;
	game->map = malloc(sizeof(char *) * (game->row + 1));
	game->map_plus = malloc(sizeof(char *) * (game->row + 1));
	if (!game->map || !game->map_plus)
		return ;
	conut_col(game, l);
	copy_map(game, l, 0);
	run_flood_fill(game);
	map_space(game);
}

void	map_space(t_cub *game)
{
	int	i;
	int	l;

	i = 0;
	while (game->map[i])
	{
		l = 0;
		while (game->map[i][l])
		{
			if (game->map && game->map[i][l] == game->d)
			{
				game->player_x = i;
				game->player_y = l;
			}
			if (game->map[i][l] == 32)
				game->map[i][l] = '1';
			l++;
		}
		i++;
	}
}

void	copy_map(t_cub *game, int i, int l)
{
	int	s;

	while (game->file[i] != NULL)
	{
		game->map[l] = malloc(sizeof(char) * (game->col));
		game->map_plus[l] = malloc(sizeof(char) * (game->col));
		s = 0;
		while (game->file[i][s] != '\0' && game->file[i][s] != '\n')
		{
			game->map[l][s] = game->file[i][s];
			game->map_plus[l][s] = game->file[i][s];
			s++;
		}
		game->map[l][s] = '\0';
		while (s < game->col - 1)
		{
			game->map_plus[l][s] = ' ';
			s++;
		}
		game->map_plus[l][s] = '\0';
		i++;
		l++;
	}
	game->map[l] = NULL;
	game->map_plus[l] = NULL;
}
