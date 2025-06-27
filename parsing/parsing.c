#include "../includes/cub3d.h"

void    ft_parsing(t_cub *game, char *av)
{
    int i;

    i = 0;
    init_struct(game);
    conut_row(game, av);
    read_file(game, av);
    i = stor_texture(game);
    i++;
    i = skip_newline(game, i);
    int l = i;
    i = check_char(game, i);
    game->row = i - l;
    game->map = malloc(sizeof(char *) * (game->row + 1));
    game->map_plus = malloc(sizeof(char *) * (game->row + 1));
    if (!game->map || !game->map_plus)
        return ;
    conut_col(game, l);
    copy_map(game, l, 0);
    run_flood_fill(game);
}
void copy_map(t_cub *game, int i, int l)
{
    int s;

    while(game->file[i] != NULL)
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