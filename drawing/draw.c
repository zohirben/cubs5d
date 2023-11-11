/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:36:42 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/11/11 21:28:59 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void draw_map2(t_data *data, int x, int y)
{
    int i;
    int j;
    uint32_t color;

    i = y * TILE_SIZE;
    while (i < ((y * TILE_SIZE) + TILE_SIZE))
    {
        j = x * TILE_SIZE;
        while (j < ((x * TILE_SIZE) + TILE_SIZE))
        {
            if (data->map[y][x] == '1')
                color = get_rgba(20, 50, 70, 255);
            else if (data->map[y][x] == '0' || data->map[y][x] == 'P')
                color = get_rgba(200, 100, 70, 255);
            else
                color = get_rgba(20, 50, 70, 255);
            mlx_put_pixel(data->img, j, i, color);
            j++;
        }
        i++;
    }
}

void draw_map(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (data->map[y])
    {
        x = 0;
        while (data->map[y][x] && data->map[y][x] != '\n')
        {
            draw_map2(data, x, y);
            x++;
        }
        y++;
    }
}

void draw_player(t_data *data)
{
    mlx_put_pixel(data->img, data->player->x_map, data->player->y_map, get_rgba(187, 230, 228, 255));
}

void blacked(t_data *data)
{
    int x = 0;
    int y = 0;
    int dividingLine = HEIGHT / 2;
    uint32_t color;

    while (y < HEIGHT)
    {
        x = 0;
        while (x < WIDTH)
        {
            if (y < dividingLine)
                color = get_rgba(135, 206, 235, 255);
            else
                color = get_rgba(20, 50, 70, 255);
            mlx_put_pixel(data->img, x, y, color);
            x++;
        }

        y++;
    }
}

void draw_walls(t_data *data, int index)
{
    float wh;
    float x_start;
    float y_start;
    float x_end;
    float y_end;

    x_start = (float)index;
    x_end = (float)index;
    wh = (HEIGHT / data->ray_distance) * TILE_SIZE;
    y_start = (HEIGHT / 2) - (wh / 2);
    y_end = y_start + wh;
    mlx_draw_line(data, x_start, y_start, x_end, y_end, get_rgba(86, 240, 189, 255));
}