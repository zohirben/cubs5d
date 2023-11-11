/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:05:22 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/11/11 19:25:22 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void printo(void *line)
{
    printf("%s", line);
}
char **lst_to_2darr(t_list *lst)
{
    char **map;
    int len;
    int i;

    i = 0;
    len = ft_lstsize(lst);
    map = malloc((len + 1) * sizeof(char *));
    if (!map)
        return (0);
    while (lst)
    {
        map[i] = ft_strdup(lst->content);
        i++;
        lst = lst->next;
    }
    map[i] = NULL;
    return (map);
}
void read_2d(char **array)
{
    while (*array != NULL)
    {
        printf("%s\n", *array);
        array++;
    }
}

void make_map(t_data *data, int fd)
{
    char *line;
    t_list *map_read;

    map_read = NULL;
    line = get_next_line(fd);
    data->width = ft_strlen(line) - 1;
    while (line)
    {
        ft_lstadd_back(&map_read, ft_lstnew(line));
        line = get_next_line(fd);
    }
    data->map = lst_to_2darr(map_read);
    data->height = ft_lstsize(map_read);
}
void mlx_draw_line(t_data *data, int x1, int y1, int x2, int y2, uint32_t color)
{
    data->dda->dx = abs(x2 - x1);
    data->dda->dy = -abs(y2 - y1);
    data->dda->sx = x1 < x2 ? 1 : -1;
    data->dda->sy = y1 < y2 ? 1 : -1;
    data->dda->err = data->dda->dx + data->dda->dy;
    while (1)
    {
        if (x1 < WIDTH && y1 < HEIGHT && x1 > 0 && y1 > 0)
            mlx_put_pixel(data->img, x1, y1, color);
        if (x1 == x2 && y1 == y2)
            break;
        data->dda->e2 = 2 * data->dda->err;
        if (data->dda->e2 >= data->dda->dy)
        {
            data->dda->err += data->dda->dy;
            x1 += data->dda->sx;
        }
        if (data->dda->e2 <= data->dda->dx)
        {
            data->dda->err += data->dda->dx;
            y1 += data->dda->sy;
        }
    }
}

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void apply_direction(t_data *data, char direction, int *x, int *y)
{
    if (direction == 'W')
    {
        *x = (data->player->x_map + cos(data->player->direction * (M_PI / 180)) * 0.9) / TILE_SIZE;
        *y = (data->player->y_map + (sin(data->player->direction * (M_PI / 180)) * 0.9)) / TILE_SIZE;
    }
    else if (direction == 'S')
    {
        *x = (data->player->x_map - cos(data->player->direction * (M_PI / 180)) * 0.9) / TILE_SIZE;
        *y = (data->player->y_map - sin(data->player->direction * (M_PI / 180)) * 0.9) / TILE_SIZE;
    }
    else if (direction == 'A')
    {
        *x = (data->player->x_map + sin(data->player->direction * (M_PI / 180)) * 0.9) / TILE_SIZE;
        *y = (data->player->y_map - cos(data->player->direction * (M_PI / 180)) * 0.9) / TILE_SIZE;
    }
    else if (direction == 'D')
    {
        *x = (data->player->x_map - sin(data->player->direction * (M_PI / 180)) * 0.9) / TILE_SIZE;
        *y = (data->player->y_map + cos(data->player->direction * (M_PI / 180)) * 0.9) / TILE_SIZE;
    }
}

int inside_map(t_data *data, char direction)
{
    int x;
    int y;

    apply_direction(data, direction, &x, &y);
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

void calculate_horizontal(t_data *data, float ray_angle)
{
    if (ray_angle == 0 || ray_angle == 180)
        return;
    if (ray_angle > 0 && ray_angle < 180)
    {
        data->y_ray = (((int)data->player->y_map / TILE_SIZE) + 1) * TILE_SIZE;
        data->y_step = TILE_SIZE;
    }
    else
    {
        data->y_ray = (((int)data->player->y_map / TILE_SIZE) - 0.00001) * TILE_SIZE;
        data->y_step = -TILE_SIZE;
    }
    data->x_ray = ((data->y_ray - (data->player->y_map)) / tan(ray_angle * (M_PI / 180))) + data->player->x_map;
    data->x_step = data->y_step / tan(ray_angle * (M_PI / 180));
    check_walls(data, 1);
}

void calculate_vertical(t_data *data, float ray_angle)
{
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
    mlx_draw_line(data, x_start, y_start, x_end, y_end, get_rgba(86, 240, 189, 255));
}

void draw_rays(t_data *data)
{
    float FOV_ANGLE = 60;
    int NUM_RAYS = WIDTH;
    float ray_angle = data->player->direction - (FOV_ANGLE / 2);

    int i = 0;
    while (i < NUM_RAYS)
    {
        ray_angle = normalize_angle(ray_angle);
        cast_rays(data, data->player->x_map, data->player->y_map, ray_angle);
        draw_walls(data, i);
        ray_angle += FOV_ANGLE / WIDTH;
        i++;
    }
}

void draw_rays_color(t_data *data)
{
    float FOV_ANGLE = 60;
    int NUM_RAYS = WIDTH;
    float ray_angle = data->player->direction - (FOV_ANGLE / 2);

    int i = 0;
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

void key_movements(t_data *data, float delta_distance)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
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
    data->dda = malloc(sizeof(t_dda));
    blacked(data);
    draw_rays(data);
    draw_map(data);
    draw_player(data);
    draw_rays_color(data);
    free(data->dda);
}

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

t_player *assign_player(int x, int y, int color)
{
    t_player *player;

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
            if (data->map[i][j] == 'P')
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
    mlx_put_pixel(data->img, data->player->x_map, data->player->y_map, get_rgba(187, 230, 228, 255));
}

int main()
{
    int fd;
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    ft_memset(data, 0, sizeof(t_data));
    fd = open("map.cub", O_CREAT | O_RDONLY);
    if (fd == -1)
        exit(1);
    make_map(data, fd);
    data->mlx = mlx_init(WIDTH, HEIGHT, "UwU", true);
    data->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);

    find_player(data);
    data->player->direction = 180;
    data->player->speed = 2.2;
    data->player->x_map = (data->player->x * TILE_SIZE) + (TILE_SIZE / 2);
    data->player->y_map = (data->player->y * TILE_SIZE) + (TILE_SIZE / 2);

    mlx_image_to_window(data->mlx, data->img, 0, 0);

    mlx_loop_hook(data->mlx, ft_hook, data);
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
}