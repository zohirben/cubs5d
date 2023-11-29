#ifndef CUB3D_H
#define CUB3D_H

#include "libft.h"
#include "MLX42/include/MLX42/MLX42.h"
#include <math.h>

#define WIDTH 1000
#define HEIGHT 750
#define TILE_SIZE 20

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
    int is_hor;

    mlx_t *mlx;
    mlx_image_t *img;
    t_dda *dda;
} t_data;
// draw
void draw_map2(t_data *data, int x, int y);
void draw_walls(t_data *data, int index);
void draw_player(t_data *data);
void draw_map(t_data *data);
void blacked(t_data *data);
// render
void cast_rays(t_data *data, float player_x, float player_y, float ray_angle);
void calculate_horizontal(t_data *data, float ray_angle);
void calculate_vertical(t_data *data, float ray_angle);
void draw_rays_color(t_data *data);
void draw_rays(t_data *data);
// check
void check_closest_distance(t_data *data, float hori_distance, float vert_distance);
float normalize_angle(float ray_angle);
void apply_direction(t_data *data, char direction, int *x, int *y);
void check_walls(t_data *data, int is_horizontal);
int inside_map(t_data *data, char direction);
// dda
char **lst_to_2darr(t_list *lst);
void make_map(t_data *data, int fd);
void mlx_draw_line(t_data *data, int x1, int y1, int x2, int y2, uint32_t color);
void mlx_draw_line(t_data *data, int x1, int y1, int x2, int y2, uint32_t color);
int get_rgba(int r, int g, int b, int a);
t_player *assign_player(int x, int y, int color);
void find_player(t_data *data);
void    free_game(t_data *data);

#endif
