/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:33:46 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/18 10:14:32 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void check_arg(int ac, char **av)
{
    char *argv;
    int len;

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

void check_map_plus(t_cub *game)
    {
        int i;
        int l;
    
        i = 0;
        while(game->map_plus[0][i])
        {
            if (game->map_plus[0][i] == 'X')
            {
                ft_putendl_fd("ERROR: INVALID MAP", 2);
                ft_free(game, 1);
            }
            i++;
        }
        i = 1;
        while(game->map_plus[i])
        {
            l = 0;
            while (game->map_plus[i][l])
                l++;
            if (game->map_plus[i][0] == 'X' || game->map_plus[i][l -1] == 'X')
            {
                ft_putendl_fd("ERROR: INVALID MAP", 2);
                ft_free(game, 1);
            }
            i++;
        }
        i = 0;
        while(game->map_plus[game->row - 1][i])
        {
            if (game->map_plus[game->row - 1][i] == 'X')
            {
                ft_putendl_fd("ERROR: INVALID MAP", 2);
                ft_free(game, 1);
            }
            i++;
        }
    }
    
int check_char(t_cub *game, int l)
{
    char **map;
    int i;
    int dr = 0;

    while (game->file[l] != NULL)
    {
        map = ft_split(game->file[l]);
        if (conut_split(map) == 0)
        {
            ft_putendl_fd("ERROR: NEWLINE", 2);
            free_split(map);
            ft_free(game, 1);
        }
        i = 0;
        while (map[i])
        {
            int a = 0;
            while(map[i][a])
            {
                if (!ft_strchr("10", map[i][a]))
                {
                    if (ft_strchr("NSWE", map[i][a]))
                    {
                        game->d = map[i][a];
                        dr++;
                    }
                    else
                    {
                        ft_putendl_fd("ERROR: INVALID CHAR", 2);
                        free_split(map);
                        ft_free(game, 1);
                    }
                }
                a++;
            }
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
    return l;
}