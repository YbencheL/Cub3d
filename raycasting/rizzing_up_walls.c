/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rizzing_up_walls.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybenchel <ybenchel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 10:15:59 by ybenchel          #+#    #+#             */
/*   Updated: 2025/07/02 10:47:47 by ybenchel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int shade_color(int base_color, double distance)
{
    double factor = 1.0 / (1.0 + distance * 0.1);
    int r = ((base_color >> 16) & 0xFF) * factor;
    int g = ((base_color >> 8) & 0xFF) * factor;
    int b = (base_color & 0xFF) * factor;
    return (r << 16) | (g << 8) | b;
}

void textures_logic(t_data *data, t_player *player, int ray_indx)
{
    int tex_width, tex_height;
    char *texture_addr;
    int sizel, bpp;

    // 1. Select correct texture/side based on wall hit orientation and ray direction
    if (player->vertical && player->raydirX < 0) // WEST wall
    {
        texture_addr = data->west.addr;
        tex_width = data->west.width;
        tex_height = data->west.height;
        sizel = data->west.sizel;
        bpp = data->west.bbq;
    }
    else if (player->vertical && player->raydirX >= 0) // EAST wall
    {
        texture_addr = data->east.addr;
        tex_width = data->east.width;
        tex_height = data->east.height;
        sizel = data->east.sizel;
        bpp = data->east.bbq;
    }
    else if (!player->vertical && player->raydirY < 0) // NORTH wall
    {
        texture_addr = data->north.addr;
        tex_width = data->north.width;
        tex_height = data->north.height;
        sizel = data->north.sizel;
        bpp = data->north.bbq;
    }
    else // SOUTH wall
    {
        texture_addr = data->south.addr;
        tex_width = data->south.width;
        tex_height = data->south.height;
        sizel = data->south.sizel;
        bpp = data->south.bbq;
    }

    // 2. Compute wall_x (where along the wall the ray hit, fractional part)
    double wall_x;
    if (player->vertical)
        wall_x = player->hity;
    else
        wall_x = player->hitx;
    wall_x -= floor(wall_x);

    // 3. Texture X coordinate
    int tex_x = (int)(wall_x * (double)tex_width);
    // Optional flip for correct orientation
    if ((player->vertical && player->raydirX > 0) || (!player->vertical && player->raydirY < 0))
        tex_x = tex_width - tex_x - 1;

    // 4. Drawing bounds
    int draw_start = (int)player->draw_start;
    int draw_end = (int)player->draw_end;
    if (draw_start < 0) draw_start = 0;
    if (draw_end >= data->height) draw_end = data->height - 1;
    int wall_height = draw_end - draw_start;

    // 5. Draw vertical wall slice with texture using while loop
    int y = draw_start;
    while (y <= draw_end)
    {
        int d = y * 256 - data->height * 128 + wall_height * 128;
        int tex_y = ((d * tex_height) / wall_height) / 256;
        if (tex_y < 0) tex_y = 0;
        if (tex_y >= tex_height) tex_y = tex_height - 1;

        int color = *(unsigned int *)(texture_addr + tex_y * sizel + tex_x * (bpp / 8));
        my_mlx_pixel_put(data, ray_indx, y, color);
        y++;
    }
}

void casting_walls(t_data *data, t_player *player, int ray_indx)
{
    double dx = player->hitx - player->posx;
    double dy = player->hity - player->posy;
    player->distance = dx * player->dirx + dy * player->diry;
    double projection_plane_d = (data->width / 2.0) / tan(player->fov / 2.0);
    double wall_height = projection_plane_d / player->distance;

    player->draw_start = (data->height / 2.0) - (wall_height / 2.0);
    player->draw_end   = (data->height / 2.0) + (wall_height / 2.0);

    int draw_start = (int)player->draw_start;
    int draw_end = (int)player->draw_end;
    if (draw_start < 0) draw_start = 0;
    if (draw_end >= data->height) draw_end = data->height - 1;

    int y = 0;
    while (y < draw_start)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colors); // ceiling
        y++;
    }
    textures_logic(data, player, ray_indx); // wall texture

    y = draw_end + 1;
    while (y < data->height)
    {
        my_mlx_pixel_put(data, ray_indx, y, data->colorg); // floor
        y++;
    }
}