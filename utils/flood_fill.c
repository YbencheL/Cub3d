#include "../includes/cub3d.h"
    

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
                break;
            }
    }
    return l;
}

void flood_fill(t_cub *game, int x, int y)
{
    // if (x < 0 || x >= game->row || y < 0 || y >= game->col)
    //     return;
    // if (game->map_plus[x][y] == '1' || game->map_plus[x][y] == 'X')
    //     return;

    game->map_plus[x][y] = 'X';

    while (1)
    {
        if (x != 0 && ft_strchr(" 0",game->map_plus[x - 1][y]))
            x--;
        else if (y + 1 < game->col && ft_strchr(" 0",game->map_plus[x][y + 1]))
            y++;
        else if (x + 1 < game->row && ft_strchr(" 0",game->map_plus[x + 1][y]))
            x++;
        else if (y != 0 && ft_strchr(" 0",game->map_plus[x][y - 1]))
            y--;
        else
            break;
        game->map_plus[x][y] = 'X';
    }
}


void run_flood_fill(t_cub *game)
{
    int i;
    int l;

    i = 0;
    while(game->map_plus[i])
    {
        l = 0;
        while(game->map_plus[i][l])
        {
            if (game->map_plus[i][l] == '0' || game->map_plus[i][l] == game->d)
                flood_fill(game, i , l);
            else
                l++;
        }
        i++;
    }
    check_map_plus(game);
}