/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:44:24 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/12/04 21:41:10 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	normalize_angle(float ray_angle)
{
	if (ray_angle <= 0)
		while (ray_angle <= 0)
			ray_angle += 360;
	else if (ray_angle >= 360)
		while (ray_angle >= 360)
			ray_angle -= 360;
	return (ray_angle);
}

void	check_closest_distance(t_data *data, float hori_distance,
		float vert_distance)
{
	data->is_hor = 0;
	if (hori_distance < vert_distance)
	{
		data->is_hor = 1;
		data->x_ray = data->x_hori;
		data->y_ray = data->y_hori;
		data->ray_distance = hori_distance;
	}
	else
	{
		data->x_ray = data->x_vert;
		data->y_ray = data->y_vert;
		data->ray_distance = vert_distance;
	}
}

int	inside_map(t_data *data, char direction)
{
	int	x;
	int	y;

	apply_direction(data, direction, &x, &y);
	if (data->map[y][(int)data->player->x_map / TILE_SIZE] == '1'
		&& data->map[(int)data->player->y_map / TILE_SIZE][x] == '1')
		return (1);
	if (data->map[y][x] == '1' || x < 0 || x > data->width || y < 0
		|| y > data->height)
		return (1);
	return (0);
}

void	apply_direction2(t_data *data, char direction, int *x, int *y)
{
	float	delta_distance;

	delta_distance = 1.9;
	if (direction == 'S')
	{
		*x = (data->player->x_map - cos(data->player->direction * (M_PI / 180))
				* delta_distance) / TILE_SIZE;
		*y = (data->player->y_map - sin(data->player->direction * (M_PI / 180))
				* delta_distance) / TILE_SIZE;
	}
	else if (direction == 'D')
	{
		*x = (data->player->x_map - sin(data->player->direction * (M_PI / 180))
				* delta_distance) / TILE_SIZE;
		*y = (data->player->y_map + cos(data->player->direction * (M_PI / 180))
				* delta_distance) / TILE_SIZE;
	}
}

void	apply_direction(t_data *data, char direction, int *x, int *y)
{
	float	delta_distance;

	delta_distance = 3;
	if (direction == 'W')
	{
		*x = (data->player->x_map + cos(data->player->direction * (M_PI / 180))
				* delta_distance) / TILE_SIZE;
		*y = (data->player->y_map + (sin(data->player->direction * (M_PI / 180))
					* delta_distance)) / TILE_SIZE;
	}
	else if (direction == 'A')
	{
		*x = (data->player->x_map + sin(data->player->direction * (M_PI / 180))
				* delta_distance) / TILE_SIZE;
		*y = (data->player->y_map - cos(data->player->direction * (M_PI / 180))
				* delta_distance) / TILE_SIZE;
	}
	apply_direction2(data, direction, x, y);
}
