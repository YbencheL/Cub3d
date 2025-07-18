/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 21:34:04 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/18 09:43:58 by mohel-kh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void flood_fill(t_cub *map, int x, int y)
{
    if (x < 0 || y < 0 || x >= map->row || y >= map->col
        || ft_strchr("1X", map->map_plus[x][y]))
            return ;
    map->map_plus[x][y] = 'X';
    flood_fill(map, x, y + 1);
    flood_fill(map, x, y - 1);
    flood_fill(map, x + 1, y);
    flood_fill(map, x - 1, y);
}
void run_flood_fill(t_cub *game)
{
            int x;
            int y;
        
            x = 0;
            while(game->map_plus[x])
            {
                y = 0;
                while(game->map_plus[x][y])
                {
                    if (game->map_plus[x][y] == '0' || game->map_plus[x][y] == game->d)
                        flood_fill(game, x , y);
                    else
                        y++;
                }
                x++;
            }
            check_map_plus(game);
        }

int skip_newline(t_cub *game, int l)
{    
    char **map;

    while(game->file[l] != NULL)
    {
        map = ft_split(game->file[l]);
        if (conut_split(map) == 0)
            l++;
        else
        {
            free_split(map);
            break;
        }
        free_split(map);
    }
    return l;
}
