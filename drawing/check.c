/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:44:24 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/11/24 17:25:58 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float normalize_angle(float ray_angle)
{
    if (ray_angle <= 0)
        while (ray_angle <= 0)
            ray_angle += 360;
    else if (ray_angle >= 360)
        while (ray_angle >= 360)
            ray_angle -= 360;
    return (ray_angle);
}

void check_closest_distance(t_data *data, float hori_distance, float vert_distance)
{
    if (hori_distance < vert_distance)
    {
        data->x_ray = data->x_hori;
        data->y_ray = data->y_hori;
        data->ray_distance = hori_distance;
        mlx_draw_line(data, data->player->x_map, data->player->y_map, data->x_hori, data->y_hori, get_rgba(150, 244, 255, 255));
    }
    else
    {
        data->x_ray = data->x_vert;
        data->y_ray = data->y_vert;
        data->ray_distance = vert_distance;
        mlx_draw_line(data, data->player->x_map, data->player->y_map, data->x_vert, data->y_vert, get_rgba(150, 244, 255, 255));
    }
}

int inside_map(t_data *data, char direction)
{
    int x;
    int y;
    
    apply_direction(data, direction, &x, &y);
    if (data->map[y][(int)data->player->x_map / TILE_SIZE] == '1'
        && data->map[(int)data->player->y_map / TILE_SIZE][x] == '1')
        return (1);
    if (data->map[y][x] == '1' || x < 0 || x > data->width || y < 0 || y > data->height)
        return (1);
    return (0);
}
void check_walls(t_data *data, int is_horizontal)
{
    int x;
    int y;

    x = data->x_ray / TILE_SIZE;
    y = data->y_ray / TILE_SIZE;
    while (1)
    {
        if (x < 0 || x >= data->width || y < 0 || y >= data->height || data->map[y][x] == '1')
            break;
        data->x_ray += data->x_step;
        data->y_ray += data->y_step;
        x = data->x_ray / TILE_SIZE;
        y = data->y_ray / TILE_SIZE;
    }
    if (is_horizontal)
    {
        data->x_hori = data->x_ray;
        data->y_hori = data->y_ray;
    }
    else
    {
        data->x_vert = data->x_ray;
        data->y_vert = data->y_ray;
    }
}
void apply_direction(t_data *data, char direction, int *x, int *y)
{
    float delta_distance;

    delta_distance = 1.9;
    if (direction == 'W')
    {
        *x = (data->player->x_map + cos(data->player->direction * (M_PI / 180)) * delta_distance) / TILE_SIZE;
        *y = (data->player->y_map + (sin(data->player->direction * (M_PI / 180)) * delta_distance)) / TILE_SIZE;
    }
    else if (direction == 'S')
    {
        *x = (data->player->x_map - cos(data->player->direction * (M_PI / 180)) * delta_distance) / TILE_SIZE;
        *y = (data->player->y_map - sin(data->player->direction * (M_PI / 180)) * delta_distance) / TILE_SIZE;
    }
    else if (direction == 'A')
    {
        *x = (data->player->x_map + sin(data->player->direction * (M_PI / 180)) * delta_distance) / TILE_SIZE;
        *y = (data->player->y_map - cos(data->player->direction * (M_PI / 180)) * delta_distance) / TILE_SIZE;
    }
    else if (direction == 'D')
    {
        *x = (data->player->x_map - sin(data->player->direction * (M_PI / 180)) * delta_distance) / TILE_SIZE;
        *y = (data->player->y_map + cos(data->player->direction * (M_PI / 180)) * delta_distance) / TILE_SIZE;
    }
}
