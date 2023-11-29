/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:40:40 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/11/29 19:51:48 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void calculate_horizontal(t_data *data, float ray_angle)
{
    data->x_ray = data->player->x_map;
    data->y_ray = data->player->y_map;
    if (ray_angle == 0 || ray_angle == 180)
        return;
    if (ray_angle > 0 && ray_angle < 180)
    {
        data->y_ray = (((int)data->player->y_map / TILE_SIZE) + 1) * TILE_SIZE;
		data->y_step = TILE_SIZE;
    }
    else
    {
        data->y_ray = (((int)data->player->y_map / TILE_SIZE)) * TILE_SIZE - 0.002;
		data->y_step = -TILE_SIZE;
    }
    data->x_ray = ((data->y_ray - (data->player->y_map)) / tan(ray_angle * (M_PI / 180))) + data->player->x_map;
    data->x_step = data->y_step / tan(ray_angle * (M_PI / 180));
    check_walls(data, 1);
}

void calculate_vertical(t_data *data, float ray_angle)
{
    data->x_ray = data->player->x_map;
    data->y_ray = data->player->y_map;
    if (ray_angle == 90 || ray_angle == 270)
        return;
    if (ray_angle > 90 && ray_angle < 270)
    {

        data->x_ray = (((int)data->player->x_map / TILE_SIZE) - 0.00001) * TILE_SIZE;
        data->x_step = -TILE_SIZE;
    }
    else
    {
        data->x_ray = (((int)data->player->x_map / TILE_SIZE) + 1) * TILE_SIZE;
        data->x_step = TILE_SIZE;
    }
    data->y_ray = ((data->x_ray - (data->player->x_map)) * tan(ray_angle * (M_PI / 180))) + data->player->y_map;
    data->y_step = data->x_step * tan(ray_angle * (M_PI / 180));
    check_walls(data, 0);
}

void cast_rays(t_data *data, float player_x, float player_y, float ray_angle)
{
    float hori_distance;
    float vert_distance;
    float a;
    float b;

    calculate_horizontal(data, ray_angle);
    a = data->player->x_map - data->x_ray;
    b = data->player->y_map - data->y_ray;
    hori_distance = sqrt(pow(a, 2) + pow(b, 2));
    calculate_vertical(data, ray_angle);
    a = data->player->x_map - data->x_ray;
    b = data->player->y_map - data->y_ray;
    vert_distance = sqrt(pow(a, 2) + pow(b, 2));
    check_closest_distance(data, hori_distance, vert_distance);
}

void draw_rays(t_data *data)
{
    float FOV_ANGLE;
    int NUM_RAYS;
    float ray_angle;
    int i;

    FOV_ANGLE = 60;
    NUM_RAYS = WIDTH;
    ray_angle = data->player->direction - (FOV_ANGLE / 2);
    i = 0;
    while (i < NUM_RAYS)
    {
        ray_angle = normalize_angle(ray_angle);
        cast_rays(data, data->player->x_map, data->player->y_map, ray_angle);
        data->ray_distance = data->ray_distance * cos((ray_angle - data->player->direction) * (M_PI / 180.0));
        draw_walls(data, i);
        ray_angle += FOV_ANGLE / WIDTH;
        i++;
    }
}

void draw_rays_color(t_data *data)
{
    float FOV_ANGLE;
    int NUM_RAYS;
    int i;
    float ray_angle;

    NUM_RAYS = WIDTH;
    FOV_ANGLE = 60;
    ray_angle = data->player->direction - (FOV_ANGLE / 2);
    i = 0;
    while (i < NUM_RAYS)
    {
        ray_angle = normalize_angle(ray_angle);
        cast_rays(data, data->player->x_map, data->player->y_map, ray_angle);
        ray_angle += FOV_ANGLE / WIDTH;
        i++;
    }
}