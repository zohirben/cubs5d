/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   begin_text.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:00:31 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/04 19:01:06 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_textures(char **strs, t_textures *t, t_data *data)
{
	t_var	vars;
	int		count;
	int		signal;

	vars.i = 0;
	vars.j = 0;
	vars.last_line = 0;
	signal = 0;
	count = 0;
	count = textures_checker(strs, &vars, t, data);
	if (count != 6)
	{
		printf("error check the textures or the rgb\n");
		exit(2);
	}
	check_textures_rgb(t);
	return (vars.last_line);
}

void	textures_manage3(t_data *data, t_textures *t)
{
	data->txt2 = mlx_load_png(t->ea);
	if (!data->txt2)
	{
		printf("check textures files\n");
		exit(2);
	}
	if (ft_strncmp(&t->ea[ft_strlen(t->ea) - 4], ".png", 4))
	{
		printf("check textures files\n");
		exit(2);
	}
	free(t->ea);
}

void	textures_manage2(t_data *data, t_textures *t)
{
	data->txt4 = mlx_load_png(t->so);
	if (!data->txt4)
	{
		printf("check textures files\n");
		exit(2);
	}
	if (ft_strncmp(&t->so[ft_strlen(t->so) - 4], ".png", 4))
	{
		printf("check textures files\n");
		exit(2);
	}
	free(t->so);
	data->txt3 = mlx_load_png(t->no);
	if (!data->txt3)
	{
		printf("check textures files\n");
		exit(2);
	}
	if (ft_strncmp(&t->no[ft_strlen(t->no) - 4], ".png", 4))
	{
		printf("check textures files\n");
		exit(2);
	}
	free(t->no);
	textures_manage3(data, t);
}

void	textures_manage(t_data *data, t_textures *t)
{
	data->txt = NULL;
	data->txt1 = mlx_load_png(t->we);
	if (!data->txt1)
	{
		printf("check textures files\n");
		exit(2);
	}
	if (ft_strncmp(&t->we[ft_strlen(t->we) - 4], ".png", 4))
	{
		printf("check textures files\n");
		exit(2);
	}
	free(t->we);
	textures_manage2(data, t);
}

void	ft_mlx_begin(t_textures *t, t_data *data,
		t_window *win)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "UwU", false);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->imgmap = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->player = malloc(sizeof(t_player));
	data->playerme = malloc(sizeof(t_playerme));
	get_player_location(data->playerme, win->map.mapo);
	data->map = win->map.mapo;
	data->height = win->map.wide;
	data->width = win->map.lenght;
	data->player->x = data->playerme->p.x;
	data->player->y = data->playerme->p.y;
	data->player->direction = data->playerme->angle;
	data->player->speed = 2.2;
	data->player->x_map = (data->player->x * TILE_SIZE) + (TILE_SIZE / 2);
	data->player->y_map = (data->player->y * TILE_SIZE) + (TILE_SIZE / 2);
	textures_manage(data, t);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_image_to_window(data->mlx, data->imgmap, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
