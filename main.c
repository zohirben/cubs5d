/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 09:00:30 by sbellafr          #+#    #+#             */
/*   Updated: 2023/11/29 19:07:40 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void printo(void *line)
{
	printf("%s", line);
}
// char **lst_to_2darr(t_list *lst)
// {
//     char **map;
//     int len;
//     int i;

//     i = 0;
//     len = ft_lstsize(lst);
//     map = malloc((len + 1) * sizeof(char *));
//     if (!map)
//         return (0);
//     while (lst)
//     {
//         map[i] = ft_strdup(lst->content);
//         i++;
//         lst = lst->next;
//     }
//     map[i] = NULL;
//     return (map);
// }
void read_2d(char **array)
{
	while (*array != NULL)
	{
		printf("%s\n", *array);
		array++;
	}
}

void mlx_draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2,
				   uint32_t color)
{
	int dx;
	int dy;
	int sx;
	int sy;
	int err;
	int e2;

	dx = abs(x2 - x1);
	dy = -abs(y2 - y1);
	sx = x1 < x2 ? 1 : -1;
	sy = y1 < y2 ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		if (x1 < WIDTH && y1 < HEIGHT && x1 > 0 && y1 > 0)
			mlx_put_pixel(img, x1, y1, color);
		if (x1 == x2 && y1 == y2)
			break;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x1 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y1 += sy;
		}
	}
}

int get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int inside_map(t_data *data, char direction)
{
	int x;
	int y;

	if (direction == 'W')
	{
		x = (data->player->x_map + cos(data->player->direction * (M_PI / 180)) * 1) / TILE_SIZE;
		y = (data->player->y_map + (sin(data->player->direction * (M_PI / 180)) * 1)) / TILE_SIZE;
	}
	else if (direction == 'S')
	{
		x = (data->player->x_map - cos(data->player->direction * (M_PI / 180)) * 1) / TILE_SIZE;
		y = (data->player->y_map - sin(data->player->direction * (M_PI / 180)) * 1) / TILE_SIZE;
	}
	else if (direction == 'A')
	{
		x = (data->player->x_map + sin(data->player->direction * (M_PI / 180)) * 1) / TILE_SIZE;
		y = (data->player->y_map - cos(data->player->direction * (M_PI / 180)) * 1) / TILE_SIZE;
	}
	else if (direction == 'D')
	{
		x = (data->player->x_map - sin(data->player->direction * (M_PI / 180)) * 1) / TILE_SIZE;
		y = (data->player->y_map + cos(data->player->direction * (M_PI / 180)) * 1) / TILE_SIZE;
	}
	if (data->map[y][x] == '1' || x < 0 || x > data->width || y < 0 || y > data->height)
		return (1);
	return (0);
}

void calculate_horizontal(t_data *data, float ray_angle)
{
	int x;
	int y;

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
	x = data->x_ray / TILE_SIZE;
	y = data->y_ray / TILE_SIZE;
	while (1)
	{
		if (x < 0 || x >= data->width || y < 0 || y >= data->height || data->map[y][x] == '1')
			break;
		data->x_ray += data->x_step;
		data->y_ray += data->y_step;
		// printf("x = %i\n")
		x = data->x_ray / TILE_SIZE;
		y = data->y_ray / TILE_SIZE;
	}
	data->x_hori = data->x_ray;
	data->y_hori = data->y_ray;
	// mlx_draw_line(data->img, data->player->x_map, data->player->y_map,
	// data->x_ray, data->y_ray, get_rgba(150, 244, 255, 255));
}

void calculate_vertical(t_data *data, float ray_angle)
{
	int x;
	int y;

	if (ray_angle == 90 || ray_angle == 270)
		return;
	if (ray_angle > 90 && ray_angle < 270)
	{
		data->x_ray = (((int)data->player->x_map / TILE_SIZE)) * TILE_SIZE - 0.002;
		data->x_step = -TILE_SIZE;
	}
	else
	{
		data->x_ray = (((int)data->player->x_map / TILE_SIZE) + 1) * TILE_SIZE;
		data->x_step = TILE_SIZE;
	}
	data->y_ray = ((data->x_ray - (data->player->x_map)) * tan(ray_angle * (M_PI / 180))) + data->player->y_map;
	data->y_step = data->x_step * tan(ray_angle * (M_PI / 180));
	x = data->x_ray / TILE_SIZE;
	y = data->y_ray / TILE_SIZE;
	while (1)
	{
		if (x < 0 || x >= data->width || y < 0 || y >= data->height || data->map[y][x] == '1')
			break;
		data->x_ray += data->x_step;
		data->y_ray += data->y_step;
		// printf("x = %i\n")
		x = data->x_ray / TILE_SIZE;
		y = data->y_ray / TILE_SIZE;
	}
	data->x_vert = data->x_ray;
	data->y_vert = data->y_ray;
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
	data->is_hor = 0;
	if (hori_distance < vert_distance)
	{
		data->is_hor = 1;
		data->x_ray = data->x_hori;
		data->y_ray = data->y_hori;
		data->ray_distance = hori_distance;
		mlx_draw_line(data->imgmap, data->player->x_map, data->player->y_map,
					  data->x_hori, data->y_hori, get_rgba(150, 244, 255, 255));
	}
	else
	{
		data->x_ray = data->x_vert;
		data->y_ray = data->y_vert;
		data->ray_distance = vert_distance;
		mlx_draw_line(data->imgmap, data->player->x_map, data->player->y_map,
					  data->x_vert, data->y_vert, get_rgba(150, 244, 255, 255));
	}

	// Draw the line from player to endpoint
	// mlx_draw_line(data->imgmap, data->player->x_map, data->player->y_map,
	// endX, endY, get_rgba(150, 244, 255, 255));
}
float normalize_angle(float ray_angle)
{
	if (ray_angle < 0)
		return (ray_angle + 360);
	if (ray_angle > 360)
		return (ray_angle - 360);
	return (ray_angle);
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
	// mlx_draw_line(data->img, x_start, y_start, x_end, y_end, get_rgba(86, 240, 189, 255));
	ft_draw_textures(data, x_start, y_start, y_end);
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
		ray_angle += FOV_ANGLE / WIDTH;
		i++;
	}
}

void blacked(t_data *data)
{
	int x;
	int y;
	int dividingLine;
	uint32_t color;

	x = 0;
	y = 0;
	dividingLine = HEIGHT / 2;
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

void ft_hook(void *param)
{
	t_data *data;
	float deltaDistance;

	deltaDistance = 1;
	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
		exit(0);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A) && inside_map(data,
																 'A') != 1)
	{
		data->player->x_map += sin(data->player->direction * (M_PI / 180)) * deltaDistance;
		data->player->y_map -= cos(data->player->direction * (M_PI / 180)) * deltaDistance;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D) && inside_map(data,
																 'D') != 1)
	{
		data->player->x_map -= sin(data->player->direction * (M_PI / 180)) * deltaDistance;
		data->player->y_map += cos(data->player->direction * (M_PI / 180)) * deltaDistance;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_W) && inside_map(data,
																 'W') != 1)
	{
		data->player->x_map += cos(data->player->direction * (M_PI / 180)) * deltaDistance;
		data->player->y_map += sin(data->player->direction * (M_PI / 180)) * deltaDistance;
	}
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S) && inside_map(data,
																 'S') != 1)
	{
		data->player->x_map -= cos(data->player->direction * (M_PI / 180)) * deltaDistance;
		data->player->y_map -= sin(data->player->direction * (M_PI / 180)) * deltaDistance;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		data->player->direction -= 1;
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		data->player->direction += 1;
	blacked(data);
	draw_map(data);
	draw_rays(data);
	draw_player(data);
	// draw_rays_color(data);
}

void draw_map(t_data *data)
{
	int x;
	int y;
	int i;
	int j;
	uint32_t color;
	char tile;

	y = 0;
	while (data->map[y])
	{
		x = 0;
		while (data->map[y][x] && data->map[y][x] != '\n')
		{
			i = y * TILE_SIZE;
			while (i < ((y * TILE_SIZE) + TILE_SIZE))
			{
				j = x * TILE_SIZE;
				while (j < ((x * TILE_SIZE) + TILE_SIZE))
				{
					if (data->map[y][x] == '1')
						color = get_rgba(20, 50, 70, 255);
					else if (data->map[y][x] == '0' || data->map[y][x] == 'N')
						color = get_rgba(200, 100, 70, 255);
					else
						color = get_rgba(20, 50, 70, 255);
					mlx_put_pixel(data->imgmap, j, i, color);
					j++;
				}
				i++;
			}
			x++;
		}
		y++;
	}
}

t_player *assign_player(int x, int y, int color)
{
	t_player *player;

	player = malloc(sizeof(t_player));
	player->x = x;
	player->y = y;
	return (player);
}

void find_player(t_data *data)
{
	int i;
	int j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] && data->map[i][j] != '\n')
		{
			if (data->map[i][j] == 'N')
			{
				data->player = assign_player(j, i, get_rgba(20, 100, 93, 255));
				break;
			}
			j++;
		}
		i++;
	}
}

void draw_player(t_data *data)
{
	mlx_put_pixel(data->imgmap, data->player->x_map, data->player->y_map,
				  get_rgba(187, 230, 228, 255));
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
int check_textures(char **strs, t_textures *t, t_color *floor, t_color *ceiling)
{
	t_var vars;
	vars.i = 0;
	vars.j = 0;
	vars.last_line = 0;

	int count;
	int signal = 0;
	count = 0;

	count = textures_checker(strs, floor, ceiling, &vars, t);
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
	t_color floor;
	t_color ceiling;
	t_data data;
	t_window win;
	t_playerme playerme;

	i = 0;
	if (ac == 2)
	{
		i = ft_count_map(av[1]);
		strs = fill_strs(i, av[1]);
		i = check_textures(strs, &t, &floor, &ceiling);
		ft_start(i, strs, &win);
		ft_mlx_begin(&playerme, &t, &data, &win);
	}
	else
		return (1);
}
