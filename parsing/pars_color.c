/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 23:03:06 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/17 23:38:38 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    ft_free(t_cub *game, int n_exit)
{
    free_split(game->file);
    free_split(game->map_plus);
    free_split(game->map);
    if (game->ea)
        free(game->ea);
    if (game->we)
        free(game->we);
    if (game->so)
        free(game->so);
    if (game->no)
        free(game->no);
    if (game->f)
        free(game->f);
    if (game->c)
        free(game->c);
    exit(n_exit);
}
void    free_split(char **arr)
{
    int i;

    i = 0;
    while(arr && arr[i])
    {
        free(arr[i]);
        i++;
    }
    if(arr)
        free(arr);
}

int is_number(char *str)
{
	int i;

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


int parse_rgb(char *str)
{
	char	**split;
	int		r, g, b;
    
	split = ft_split_plus(str, ',');
	if (conut_split(split) > 2)
		return (-1);

	if (!is_number(split[0]) || !is_number(split[1]) || !is_number(split[2]))
		return (-1);

	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (-1);
    free_split(split);
	return ((r << 16) | (g << 8) | b);
}

void    if_check(t_cub *game)
{
    if (!game->c || !game->f || !game->no || !game->so || !game->we || !game->ea)
    {
        ft_putendl_fd("ERROR", 2);
        ft_free(game, 1);
    }
    if((game->f_color = parse_rgb(game->f)) == -1)
    {
        ft_putendl_fd("ERROR", 2);
        ft_free(game, 1);
    }
    if((game->c_color = parse_rgb(game->c)) == -1)
    {
        ft_putendl_fd("ERROR", 2);
        ft_free(game, 1);
    }
}
