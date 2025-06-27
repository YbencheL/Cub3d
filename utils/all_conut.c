#include "../includes/cub3d.h"

int conut_split(char **line)
{
    int i = 0;

    while (line[i])
        i++;
    return i;
}
void conut_col(t_cub *game, int i)
{
    int col;

    while (game->file[i] != NULL)
    {
        col = 0;
        while (game->file[i][col])
            col++;
        if (col > game->col)
            game->col = col;
        i++;
    }
}
void conut_row(t_cub *game, char *av)
{
    char *line;
    int fd;

    fd = open(av, O_RDONLY);
    if (fd < 0)
    {
        perror("ERROR");
        exit(1);
    }
    line = get_next_line(fd);
    while (line)
    {
        game->row++;
        free(line);
        line = get_next_line(fd);
    }
    close(fd);
    if (game->row == 0)
    {
        perror("ERROR MAP IS EMPTY");
        exit(1);
    }
}