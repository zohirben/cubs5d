/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:48:07 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/12/04 19:47:04 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

t_player	*assign_player(int x, int y, int color)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		exit(1);
	player->x = x;
	player->y = y;
	return (player);
}

void	find_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] && data->map[i][j] != '\n')
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'E'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'S')
			{
				data->player = assign_player(j, i, get_rgba(20, 100, 93, 255));
				break ;
			}
			j++;
		}
		i++;
	}
}

void	key_movements2(t_data *data, float delta_distance)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_W) && inside_map(data,
			'W') != 1)
	{
		data->player->x_map += cos(data->player->direction * (M_PI / 180))
			* delta_distance;
		data->player->y_map += sin(data->player->direction * (M_PI / 180))
			* delta_distance;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S) && inside_map(data,
			'S') != 1)
	{
		data->player->x_map -= cos(data->player->direction * (M_PI / 180))
			* delta_distance;
		data->player->y_map -= sin(data->player->direction * (M_PI / 180))
			* delta_distance;
	}
}
void	key_movements(t_data *data, float delta_distance)
{
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->mlx);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A) && inside_map(data,
			'A') != 1)
	{
		data->player->x_map += sin(data->player->direction * (M_PI / 180))
			* delta_distance;
		data->player->y_map -= cos(data->player->direction * (M_PI / 180))
			* delta_distance;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) && inside_map(data,
			'D') != 1)
	{
		data->player->x_map -= sin(data->player->direction * (M_PI / 180))
			* delta_distance;
		data->player->y_map += cos(data->player->direction * (M_PI / 180))
			* delta_distance;
	}
	key_movements2(data, delta_distance);
}
