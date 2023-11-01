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
    while (line)
    {
        ft_lstadd_back(&map_read, ft_lstnew(line));
        line = get_next_line(fd);
    }
    data->map = lst_to_2darr(map_read);
    // read_2d(data->map);
    data->height = ft_lstsize(map_read);
}
void mlx_draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, uint32_t color)
{
    int dx = abs(x2 - x1);
    int dy = -abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2;

    while (1)
    {
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
        x = (data->player->x_map + cos(data->player->direction) * 2.2) / TILE_SIZE;
        y = (data->player->y_map + (sin(data->player->direction) * 2.2)) / TILE_SIZE;
    }
    else if (direction == 'S')
    {
        x = (data->player->x_map - cos(data->player->direction) * 2.2) / TILE_SIZE;
        y = (data->player->y_map - sin(data->player->direction) * 2.2) / TILE_SIZE;
    }
    else if (direction == 'A')
    {
        x = (data->player->x_map + sin(data->player->direction) * 2.2) / TILE_SIZE;
        y = (data->player->y_map - cos(data->player->direction) * 2.2) / TILE_SIZE;
    }
    else if (direction == 'D')
    {
        x = (data->player->x_map - sin(data->player->direction) * 2.2) / TILE_SIZE;
        y = (data->player->y_map + cos(data->player->direction) * 2.2) / TILE_SIZE;
    }
    if (data->map[y][x] == '1' || x < 0 || x > WIDTH || y < 0 || y > HEIGHT)
        return (1);
    return (0);
}

void cast_rays(t_data *data, float player_x, float player_y, float ray_angle)
{
    float x = player_x;
    float y = player_y;
    float RAY_LENGTH = 10;
    
    float endX; 
    float endY;
    endX= data->player->x_map + cos(ray_angle) * RAY_LENGTH;
    endY = data->player->y_map + sin(ray_angle) * RAY_LENGTH;
    while (1)
    {
        if (data->map[(int)(endY / TILE_SIZE)][(int)(endX / TILE_SIZE)] != '1')
        {
            endX = data->player->x_map + cos(ray_angle) * RAY_LENGTH;
            endY = data->player->y_map + sin(ray_angle) * RAY_LENGTH;
            RAY_LENGTH++;
        }
        else
            break;
    }
    // Draw the line from player to endpoint
    mlx_draw_line(data->img, data->player->x_map, data->player->y_map, endX, endY, get_rgba(150, 244, 255, 255));
}

void draw_rays(t_data *data)
{
    float FOV_ANGLE = 60 * (M_PI / 180);
    int NUM_RAYS = WIDTH;
    int columid = 0;
    float ray_angle = data->player->direction - (FOV_ANGLE / 2);


    int i = 0;
    while (i < NUM_RAYS)
    {
        cast_rays(data, data->player->x_map, data->player->y_map, ray_angle);
        ray_angle += FOV_ANGLE / WIDTH;
        i++;
    }
}

void ft_hook(void *param)
{
    t_data *data;

    float deltaDistance = 2.2;
    data = param;
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
        mlx_close_window(data->mlx);
    else if (mlx_is_key_down(data->mlx, MLX_KEY_A) && inside_map(data, 'A') != 1)
    {
        data->player->x_map += sin(data->player->direction) * deltaDistance;
        data->player->y_map -= cos(data->player->direction) * deltaDistance;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_D) && inside_map(data, 'D') != 1)
    {
        data->player->x_map -= sin(data->player->direction) * deltaDistance;
        data->player->y_map += cos(data->player->direction) * deltaDistance;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_W) && inside_map(data, 'W') != 1)
    {
        data->player->x_map += cos(data->player->direction) * deltaDistance;
        data->player->y_map += sin(data->player->direction) * deltaDistance;
    }
    else if (mlx_is_key_down(data->mlx, MLX_KEY_S) && inside_map(data, 'S') != 1)
    {
        data->player->x_map -= cos(data->player->direction) * deltaDistance;
        data->player->y_map -= sin(data->player->direction) * deltaDistance;
    }
    if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
        data->player->direction -= M_PI / 180;
    else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
        data->player->direction += M_PI / 180;
    draw_map(data);
    draw_player(data);
    draw_rays(data);
    
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
                    else if (data->map[y][x] == '0' || data->map[y][x] == 'P')
                        color = get_rgba(200, 100, 70, 255);
                    else
                        color = get_rgba(20, 50, 70, 255);
                    mlx_put_pixel(data->img, j, i, color);
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
    // Calculate the endpoint of the line for POV
    float endX = data->player->x_map + cos(data->player->direction) * 80;
    float endY = data->player->y_map + sin(data->player->direction) * 80;
    // printf("endX = %f\nendY = %f\n", endX, endY);

    // Draw the line from player to endpoint
    // mlx_draw_line(data->img, data->player->x_map, data->player->y_map, endX, endY, get_rgba(150, 244, 255, 255));
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
    int windowWidth = (ft_strlen(data->map[0]) - 1) * TILE_SIZE;
    int windowHeight = data->height * TILE_SIZE;
    data->mlx = mlx_init(windowWidth, windowHeight, "UwU", true);
    data->img = mlx_new_image(data->mlx, windowWidth, windowHeight);

    find_player(data);
    data->player->direction = M_PI / 180;
    data->player->speed = 2.2;
    data->player->x_map = (data->player->x * TILE_SIZE) + (TILE_SIZE / 2);
    data->player->y_map = (data->player->y * TILE_SIZE) + (TILE_SIZE / 2);

    mlx_image_to_window(data->mlx, data->img, 0, 0);

    mlx_loop_hook(data->mlx, ft_hook, data);
    mlx_loop(data->mlx);
    mlx_terminate(data->mlx);
}