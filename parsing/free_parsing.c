/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parsing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohel-kh <mohel-kh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/18 10:35:12 by mohel-kh          #+#    #+#             */
/*   Updated: 2025/07/18 10:35:14 by mohel-kh         ###   ########.fr       */
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