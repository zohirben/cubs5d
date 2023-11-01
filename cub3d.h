#ifndef CUB3D_H
# define CUB3D_H

# include "libft.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <math.h>

#define WIDTH 1472
#define HEIGHT 1472
#define TILE_SIZE 64

typedef struct s_player
{
    float x;
    float y;
    float direction;
    float speed;
    float x_map;
    float y_map;

} t_player;

typedef struct s_data
{
    char **map;
    int height;

    t_player *player;

    mlx_t* mlx;
    mlx_image_t* img;
} t_data;

void draw_map(t_data *data);
void draw_player(t_data *data);
#endif
