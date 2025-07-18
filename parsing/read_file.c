/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 23:03:36 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/18 10:17:44 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void read_file(t_cub *game, char *av)
{
    char *line;
    int fd;
    int i;

    fd = open(av, O_RDONLY);
    if (fd < 0)
    {
        perror("ERROR");
        exit(1);
    }
    game->file = malloc(sizeof(char *) * (game->row + 1));
    if (!game->file )
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
int stor_texture(t_cub *game)
{
    char **new_line;
    int l;

    l = 0;
    while (game->file[l])
    {
        new_line = ft_split(game->file[l]);
        if (conut_split(new_line) == 0)
        {
            l++;
            l--;
        }
        else if (conut_split(new_line) != 2)
        {
            ft_putendl_fd("ERROR: INVALID TEXTURES", 2);
            free_split(new_line);
            ft_free(game, 1);
        }
        else if (!game->no && ft_strncmp(new_line[0], "NO", 2) == 0)
            game->no = ft_strdup(new_line[1]);
        else if (!game->so && ft_strncmp(new_line[0], "SO", 2) == 0)
            game->so = ft_strdup(new_line[1]);
        else if (!game->we && ft_strncmp(new_line[0], "WE", 2) == 0)
            game->we = ft_strdup(new_line[1]);
        else if (!game->ea && ft_strncmp(new_line[0], "EA", 2) == 0)
            game->ea = ft_strdup(new_line[1]);
        else if (!game->f && ft_strncmp(new_line[0], "F", 2) == 0)
            game->f = ft_strdup(new_line[1]);
        else if (!game->c && ft_strncmp(new_line[0], "C", 2) == 0)
            game->c = ft_strdup(new_line[1]);
        else
        {
            ft_putendl_fd("ERROR: INVALID TEXTURES", 2);
            free_split(new_line);
            ft_free(game, 1);
        }
        free_split(new_line);
        if (game->c && game->f && game->no && game->so && game->we && game->ea)
            break;
        l++;
    }
    return l;
}
void init_struct(t_cub *file)
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