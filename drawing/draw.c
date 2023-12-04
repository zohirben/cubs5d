/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:36:42 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/12/04 19:07:54 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_map2(t_data *data, int x, int y)
{
	int			i;
	int			j;
	uint32_t	color;

	i = y * TILE_SIZE;
	while (i < ((y * TILE_SIZE) + TILE_SIZE))
	{
		j = x * TILE_SIZE;
		while (j < ((x * TILE_SIZE) + TILE_SIZE))
		{
			color = 0;
			if (data->map[y][x] == '1')
				color = get_rgba(20, 50, 70, 255);
			else if (data->map[y][x] == '0' || data->map[y][x] == 'N'
					|| data->map[y][x] == 'E' || data->map[y][x] == 'W'
					|| data->map[y][x] == 'S')
				color = get_rgba(200, 100, 70, 255);
			if (j > WIDTH || i > HEIGHT)
				exit(1);
			mlx_put_pixel(data->imgmap, j, i, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_data *data)
{
	int	x;
	int	y;

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

void	check_walls(t_data *data, int is_horizontal)
{
	int	x;
	int	y;

	x = data->x_ray / TILE_SIZE;
	y = data->y_ray / TILE_SIZE;
	while (1)
	{
		if (x < 0 || x >= data->width || y < 0 || y >= data->height
			|| data->map[y][x] == '1')
			break ;
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

void	blacked(t_data *data)
{
	int			x;
	int			y;
	int			line;
	uint32_t	color;

	x = 0;
	y = 0;
	line = HEIGHT / 2;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			if (y < line)
				color = get_rgba(data->ceiling.r, data->ceiling.g,
						data->ceiling.b, 255);
			else
				color = get_rgba(data->floor.r, data->floor.g, data->floor.b,
						255);
			mlx_put_pixel(data->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_walls(t_data *data, int index)
{
	float	wh;
	float	x_start;
	float	y_start;
	float	x_end;
	float	y_end;

	x_start = (float)index;
	x_end = (float)index;
	wh = (HEIGHT / data->ray_distance) * TILE_SIZE;
	y_start = (HEIGHT / 2) - (wh / 2); 
	y_end = y_start + wh;
	ft_draw_textures(data, x_start, y_start, y_end);
}
