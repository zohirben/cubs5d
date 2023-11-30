/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:05:22 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/11/30 23:49:26 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void key_movements(t_data *data, float delta_distance)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
    {
        free_game(data);
        mlx_close_window(data->mlx);
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_A) && inside_map(data, 'A') != 1)
    {
        data->player->x_map += sin(data->player->direction * (M_PI / 180)) * delta_distance;
        data->player->y_map -= cos(data->player->direction * (M_PI / 180)) * delta_distance;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_D) && inside_map(data, 'D') != 1)
    {
        data->player->x_map -= sin(data->player->direction * (M_PI / 180)) * delta_distance;
        data->player->y_map += cos(data->player->direction * (M_PI / 180)) * delta_distance;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_W) && inside_map(data, 'W') != 1)
    {
        data->player->x_map += cos(data->player->direction * (M_PI / 180)) * delta_distance;
        data->player->y_map += sin(data->player->direction * (M_PI / 180)) * delta_distance;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_S) && inside_map(data, 'S') != 1)
    {
        data->player->x_map -= cos(data->player->direction * (M_PI / 180)) * delta_distance;
        data->player->y_map -= sin(data->player->direction * (M_PI / 180)) * delta_distance;
    }
}

void ft_hook(void *param)
{
    t_data *data;
    float delta_distance;
    data = param;
    delta_distance = 0.8;
    key_movements(data, delta_distance);
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        data->player->direction -= 1;
    else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        data->player->direction += 1;
    blacked(data);
    draw_map(data);
    draw_player(data);
    draw_rays(data);
}


void error(void)
{
	puts(mlx_strerror(mlx_errno));
	exit(EXIT_FAILURE);
}


void get_angle(char c, t_playerme *player)
{
	if (c == 'E')
		player->angle = 0;
	else if (c == 'N')
		player->angle = PI / 2;
	else if (c == 'W')
		player->angle = PI;
	else if (c == 'S')
		player->angle = PI * 3 / 2;
}
void get_player_location(t_playerme *player, char **mapo)
{
	int i;
	int j;

	i = 0;
	j = 0;

	while (mapo[i])
	{
		j = 0;
		while (mapo[i][j])
		{
			if (mapo[i][j] == 'N' || mapo[i][j] == 'E' || mapo[i][j] == 'W' || mapo[i][j] == 'S')
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

void check_textures_rgb(t_textures *t)
{
	int i;

	i = 0;
	while (t->c[i])
	{
		if (!ft_isdigit(t->c[i]) && t->c[i] != 'C' && t->c[i] != ' ' && t->c[i] != ',' && t->c[i] != '\n')
		{
			printf("error there is an external component\n");
			exit(2);
		}
		i++;
	}
	i = 0;
	while (t->f[i])
	{
		if (!ft_isdigit(t->f[i]) && t->f[i] != 'F' && t->f[i] != ' ' && t->f[i] != ',' && t->f[i] != '\n')
		{
			printf("error there is an external component\n");
			exit(2);
		}
		i++;
	}
}
char *ft_textures(char *str, int i)
{
	char *returned;
	int j;

	j = 0;
	i = i + 2;
	while (str[i] && str[i] != '.' && str[i + 1] != '/')
		i++;
	returned = malloc(ft_strlen(str) - i + 1);
	while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
	{
		returned[j] = str[i];
		i++;
		j++;
	}
	returned[j] = '\0';
	return (returned);
}
int textures_checker(char **strs, t_color *floor, t_color *ceiling, t_var *vars, t_textures *t)
{
	vars->count = 0;
	while (strs[vars->i])
	{
		vars->j = 0;
		while (strs[vars->i][vars->j])
		{
			if (strs[vars->i][vars->j] == 'N' && strs[vars->i][vars->j + 1] == 'O')
				vars->count += check_no(strs, vars, t);
			else if (strs[vars->i][vars->j] == 'S' && strs[vars->i][vars->j + 1] == 'O')
				vars->count += check_so(strs, vars, t);
			else if (strs[vars->i][vars->j] == 'E' && strs[vars->i][vars->j + 1] == 'A')
				vars->count += check_ea(strs, vars, t);
			else if (strs[vars->i][vars->j] == 'W' && strs[vars->i][vars->j + 1] == 'E')
				vars->count += check_we(strs, vars, t);
			else if (strs[vars->i][vars->j] == 'F')
				vars->count += rgb_f(strs, floor, t, vars);
			else if (strs[vars->i][vars->j] == 'C')
				vars->count += rgb_c(strs, ceiling, t, vars);
			vars->j++;
		}
		vars->i++;
	}
	return vars->count;
}
int check_textures(char **strs, t_textures *t, t_data *data)
{
	t_var vars;
	vars.i = 0;
	vars.j = 0;
	vars.last_line = 0;

	int count;
	int signal = 0;
	count = 0;

	count = textures_checker(strs, &data->floor, &data->ceiling, &vars, t);
	if (count != 6)
	{
		printf("error check the textures or the rgb\n");
		exit(2);
	}
	check_textures_rgb(t);
	return (vars.last_line);
}

void ft_mlx_begin(t_playerme *playerme, t_textures *t, t_data *data, t_window *win)
{
	data->mlx = mlx_init(WIDTH, HEIGHT, "UwU", false);
	data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->imgmap = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	data->player = malloc(sizeof(t_player));

	get_player_location(playerme, win->map.mapo);
	
	data->map = win->map.mapo;
	data->height = win->map.wide;
	data->width = win->map.lenght;
	data->player->x = playerme->p.x;
	data->player->y = playerme->p.y;
	data->player->direction = 180;
	data->player->speed = 2.2;
	data->player->x_map = (data->player->x * TILE_SIZE) + (TILE_SIZE / 2);
	data->player->y_map = (data->player->y * TILE_SIZE) + (TILE_SIZE / 2);
	data->txt = mlx_load_png(t->so);
	data->txt1 = mlx_load_png(t->we);
	data->txt2 = mlx_load_png(t->so);
	data->txt3 = mlx_load_png(t->no);
	data->txt4 = mlx_load_png(t->ea);
	mlx_image_to_window(data->mlx, data->img, 0, 0);
	mlx_image_to_window(data->mlx, data->imgmap, 0, 0);
	mlx_loop_hook(data->mlx, ft_hook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
}
int ft_count_map(char *map)
{
	int fd;
	char *str;
	int i;

	i = 0;
	fd = open(map, O_RDWR);
	while (1)
	{
		str = get_next_line(fd);
		free(str);
		if (!str)
			break;
		i++;
	}
	close(fd);
	return i;
}
char **fill_strs(int len, char *str)
{
	int fd;
	int i;

	i = 0;
	fd = open(str, O_RDWR);

	char **strs = (char **)ft_calloc(len + 1, sizeof(char *));
	while (1)
	{
		strs[i] = get_next_line(fd);
		if (!strs[i])
			break;
		i++;
	}
	return strs;
}
int main(int ac, char **av)
{
	char **strs;
	int i;
	t_textures t;
	
	t_data data;
	t_window win;
	t_playerme playerme;

	i = 0;
	if (ac == 2)
	{
		i = ft_count_map(av[1]);
		strs = fill_strs(i, av[1]);
		i = check_textures(strs, &t, &data);
		ft_start(i, strs, &win);
		ft_mlx_begin(&playerme, &t, &data, &win);
	}
	else
		return (1);
}
