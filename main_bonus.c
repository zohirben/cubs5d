/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 21:18:37 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/04 22:01:43 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_hook(void *param)
{
	t_data	*data;
	float	delta_distance;

	data = param;
	delta_distance = 0.8;
	key_movements(data, delta_distance);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->direction -= 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->direction += 1;
	data->bonus = 1;
	blacked(data);
	draw_map(data);
	draw_player(data);
	draw_rays(data);
}

void	draw_player(t_data *data)
{
	float	radian;
	int		radius;
	int		i;
	int		j;
	int		angle;

	radius = 2;
	angle = 0;
	while (angle <= 360)
	{
		radian = angle * (M_PI / 180.0);
		i = data->player->x_map + radius * cos(radian);
		j = data->player->y_map + radius * sin(radian);
		mlx_put_pixel(data->imgmap, i, j, get_rgba(187, 230, 228, 255));
		angle += 10;
	}
}

void	get_angle(char c, t_playerme *player)
{
	if (c == 'E')
		player->angle = 0;
	else if (c == 'N')
		player->angle = 270;
	else if (c == 'W')
		player->angle = 180;
	else if (c == 'S')
		player->angle = 90;
}

void	get_player_location(t_playerme *player, char **mapo)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (mapo[i])
	{
		j = 0;
		while (mapo[i][j])
		{
			if (mapo[i][j] == 'N' || mapo[i][j] == 'E' || mapo[i][j] == 'W'
				|| mapo[i][j] == 'S')
			{
				get_angle(mapo[i][j], player);
				player->p.y = i;
				player->p.x = j;
			}
			j++;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	char		**strs;
	int			i;
	t_textures	t;
	t_data		data;
	t_window	win;

	i = 0;
	if (ac == 2)
	{
		i = ft_count_map(av[1]);
		strs = fill_strs(i, av[1]);
		i = check_textures(strs, &t, &data);
		ft_start(i, strs, &win);
		ft_mlx_begin(&t, &data, &win);
	}
	else
	{
		printf("check arguments\n");
		return (1);
	}
}
