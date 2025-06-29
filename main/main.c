/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:13:35 by ybenchel          #+#    #+#             */
/*   Updated: 2025/06/29 15:44:45 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"
#include <string.h>

void player_pos(t_player *player, char **map)
{
    int y = 0,x;
    while(y < MAP_SIZE)
    {
        x = 0;
        while(x < MAP_SIZE)
        {
            if (map[y][x] == 'P')
            {
                player->posx = (double)x + 0.5;
                player->posy = (double)y + 0.5;
                return;
            }
            x++;
        }
        y++;
    }
}

void    init_textures(t_data *data)
{
    data->north.img = mlx_xpm_file_to_image(data->mlx, "textures/lol1.xpm", &data->north.width, &data->north.height);
    data->north.addr = mlx_get_data_addr(data->north.img, &data->north.bbq, &data->north.sizel, &data->north.indian);
    
    data->south.img = mlx_xpm_file_to_image(data->mlx, "textures/lol2.xpm", &data->south.width, &data->south.height);
    data->south.addr = mlx_get_data_addr(data->south.img, &data->south.bbq, &data->south.sizel, &data->south.indian);
    
    data->west.img = mlx_xpm_file_to_image(data->mlx, "textures/lol1.xpm", &data->west.width, &data->west.height);
    data->west.addr = mlx_get_data_addr(data->west.img, &data->west.bbq, &data->west.sizel, &data->west.indian);
    
    data->east.img = mlx_xpm_file_to_image(data->mlx, "textures/lol2.xpm", &data->east.width, &data->east.height);
    data->east.addr = mlx_get_data_addr(data->east.img, &data->east.bbq, &data->east.sizel, &data->east.indian);
}

void init_vars(t_data *data, t_player *player)
{
    data->player = player;
    player->posx = 0.0;
    player->posy = 0.0;
    player->mapx = (int)player->posx;
    player->mapy = (int)player->posy;
    player->num_rays = 60;
    player->fov = M_PI / 3.0;
    player->player_a = 3 * M_PI / 2;
    player->dirx = cos(player->player_a);
    player->diry = sin(player->player_a);
    player->planex = -player->diry * 0.33;
    player->planey = player->diry * 0.33;
    data->img = NULL;
    data->addr = NULL;
    data->colors = 0xF0EAD6;
    data->colora = 0x000000;
    data->colorg = 0x808080;
    data->tile_size = 100;
    data->height = 800;
    data->width = 800;
    data->offset_x = 0;
    data->offset_y = 0;
}

int main(int ac, char **av)
{
    (void)ac;
    (void)av;
    t_data *data;
    t_player *player;
    
    char *map[MAP_SIZE] = {
        "11111111",
        "10100001",
        "10111101",
        "10000101",
        "10P00001",
        "10001111",
        "11000001",
        "11111111",
    };
    
    data = malloc(sizeof(t_data));
    ft_memset(data, 0, sizeof(t_data));
    player = malloc(sizeof(t_player));
    data->map = map;
    init_vars(data, player);
    data->mlx = mlx_init();
    if (!data->mlx)
        return (1);
    init_textures(data);
    data->win = mlx_new_window(data->mlx, data->width, data->height, "cub3d");
    if (!data->win)
        return (1);
    data->img = mlx_new_image(data->mlx, data->width, data->height);
    data->addr = mlx_get_data_addr(data->img, &data->bbq, &data->sizel, &data->indian);
    player_pos(player, map);
    // pixel(data, data->map);
    // charachter(data);
    casting_rays(data, data->player);
    mlx_put_image_to_window(data->mlx, data->win, data->img, 0, 0);
    setup_h(data);
    mlx_loop(data->mlx);
    // t_cub game;
    // int i;
    // check_arg(ac, av);
    // ft_parsing(&game, av[1]);
    // if (game.c && game.f && game.no && game.so && game.we && game.ea)
    // {
    //     // printf("%s\n", file.no);
    //     // printf("%s\n", file.so);
    //     // printf("%s\n", file.we);
    //     // printf("%s\n", file.ea);
    //     // printf("%s\n", file.f);
    //     // printf("%s\n", file.c);
    //     // printf("-------%c\n", file.d);
    //     // printf("-------row : %d\n", file.row);
    //     printf("-------col : %d\n", game.col);
    //     i = 0;
    //     if (game.map_plus)
    //     {
    //         printf("----------map----------\n");
    //         while(game.map_plus[i])
    //         {
    //             int s = 0;
    //             while(game.map_plus[i][s])
    //                 printf("[%c]", game.map_plus[i][s++]);
    //             printf("\n");
    //             i++;
    //         }
    //     }
    // }
    // else
    //     perror("ERROR");
    return 0;
}
