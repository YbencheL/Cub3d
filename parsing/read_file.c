/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 23:03:36 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/23 20:25:38 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	read_file(t_cub *game, char *av)
{
	char	*line;
	int		fd;
	int		i;

	fd = open(av, O_RDONLY);
	if (fd < 0)
	{
		perror("ERROR");
		exit(1);
	}
	game->file = malloc(sizeof(char *) * (game->row + 1));
	if (!game->file)
		return ;
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		game->file[i] = ft_strdup(line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	game->file[i] = NULL;
}

static void	handle_error(t_cub *game, char **line)
{
	ft_putendl_fd("ERROR: INVALID TEXTURES", 2);
	free_split(line);
	ft_free(game, 1);
}

static void	assign_texture(t_cub *game, char **line)
{
	if (!game->no && ft_strncmp(line[0], "NO", 2) == 0)
		game->no = ft_strdup(line[1]);
	else if (!game->so && ft_strncmp(line[0], "SO", 2) == 0)
		game->so = ft_strdup(line[1]);
	else if (!game->we && ft_strncmp(line[0], "WE", 2) == 0)
		game->we = ft_strdup(line[1]);
	else if (!game->ea && ft_strncmp(line[0], "EA", 2) == 0)
		game->ea = ft_strdup(line[1]);
	else if (!game->f && ft_strncmp(line[0], "F", 1) == 0
		&& ft_strlen(line[0]) == 1)
		game->f = ft_strdup(line[1]);
	else if (!game->c && ft_strncmp(line[0], "C", 1) == 0
		&& ft_strlen(line[0]) == 1)
		game->c = ft_strdup(line[1]);
	else
		handle_error(game, line);
}

int	stor_texture(t_cub *game)
{
	char	**line;
	int		l;

	l = 0;
	while (game->file[l])
	{
		line = ft_split(game->file[l]);
		if (conut_split(line) == 0)
		{
			free_split(line);
			l++;
			continue ;
		}
		if (conut_split(line) != 2 || ft_strlen(line[0]) > 2)
			handle_error(game, line);
		assign_texture(game, line);
		free_split(line);
		if (game->c && game->f && game->no && game->so && game->we && game->ea)
			break ;
		l++;
	}
	return (l);
}

void	init_struct(t_cub *file)
{
	file->c = NULL;
	file->ea = NULL;
	file->f = NULL;
	file->map = NULL;
	file->map_plus = NULL;
	file->file = NULL;
	file->no = NULL;
	file->so = NULL;
	file->we = NULL;
	file->d = 0;
	file->row = 0;
	file->col = 0;
	file->player_x = 0;
	file->player_y = 0;
}
