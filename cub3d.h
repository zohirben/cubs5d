#ifndef CUB3D_H
#define CUB3D_H

#include "libft.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <math.h>

#define WIDTH 1000
#define HEIGHT 750
#define TILE_SIZE 32

typedef struct s_player
{
    float x;
    float y;
    float direction;
    float speed;
    float x_map;
    float y_map;

} t_player;

typedef struct s_dda
{
    int dx;
    int dy;
    int sx;
    int sy;
    int err;
    int e2;

} t_dda;
typedef struct s_data
{
    char **map;
    int height;
    int width;

    t_player *player;
    float x_step;
    float y_step;
    float x_ray;
    float y_ray;

    float x_hori;
    float y_hori;
    float x_vert;
    float y_vert;
    float ray_distance;

    mlx_t *mlx;
    mlx_image_t *img;
    t_dda *dda;
} t_data;

void draw_map(t_data *data);
void draw_player(t_data *data);
#endif
