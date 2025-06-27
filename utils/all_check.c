#include "../includes/cub3d.h"


void check_arg(int ac, char **av)
{
    int len;

    if (ac != 2)
    {
        perror("ERROR");
        exit(1);
    }
    len = ft_strlen(av[1]);
    if (len <= 4)
    {
        perror("ERROR");
        exit(1);
    }
    char *argv = av[1];
    if (!ft_strnstr(argv + len - 4, ".cub", 4))
    {
        perror("ERROR");
        exit(1);
    }
    if (ft_strnstr(argv + len - 5, "/", 1))
    {
        perror("ERROR");
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
                perror("ERROR");
                exit(1);
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
                perror("ERROR");
                exit(1);
            }
            i++;
        }
        i = 0;
        while(game->map_plus[game->row - 1][i])
        {
            if (game->map_plus[game->row - 1][i] == 'X')
            {
                perror("ERROR");
                exit(1);
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
            perror("ERROR NEWLINE");
            exit(1);
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
                        perror("ERROR 10NSWE");
                        exit(1);
                    }
                }
                a++;
            }
            i++;
        }
        l++;
    }
    if (dr != 1)
    {
        perror("ERROR NSWE");
        exit(1);
    }
    return l;
}