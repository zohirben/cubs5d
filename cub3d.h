#ifndef CUB3D_H
#define CUB3D_H

#include "libft.h"
#include "MLX42/MLX42.h"
#include <math.h>

#define WIDTH 1000
#define HEIGHT 750
#define TILE_SIZE 20
# define PI 3.141592653589793
# define RAD 0.0174533 
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

typedef struct s_color
{
	int	r;
	int	b;
	int	g;
}t_color;
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
    mlx_image_t	*imgmap;
	mlx_texture_t *txt;
	mlx_texture_t *txt1;
	mlx_texture_t *txt2;
	mlx_texture_t *txt3;
	mlx_texture_t *txt4;

    mlx_t *mlx;
    mlx_image_t *img;
    t_dda *dda;
	t_color floor;
	t_color ceiling;
} t_data;
typedef struct s_textures
{
	char *no;
	char *so;
	char *we;
	char *ea;
	char *f;
	char *c;

}t_textures;



typedef struct s_map
{
	int		lenght;
	int		wide;
	int		width;
	char	**mapc;
	char	**mapo;
}t_map;

typedef struct s_window
{
	void		*win_ptr;
	t_player	player;
	mlx_image_t	*img;
	mlx_t		*mlx_ptr;
	t_map		map;
}t_window;

typedef struct s_point
{
	double	x;
	double	y;
}t_point;

typedef struct s_playerme
{
	t_point	p;
	double	angle;
}t_playerme;

typedef struct s_var
{
	int	i;
	int	j;
	int count;
	int	last_line;

}t_var;

typedef struct s_floats
{
	float	y_img;
	float	x_txt;
	float	y_txt;
	float	y_increment;

}t_floats;

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
// void check_closest_distance(t_data *data, float hori_distance, float vert_distance);
float normalize_angle(float ray_angle);
void apply_direction(t_data *data, char direction, int *x, int *y);
void check_walls(t_data *data, int is_horizontal);
int inside_map(t_data *data, char direction);
// dda
char **lst_to_2darr(t_list *lst);
void make_map(t_data *data, int fd);
void mlx_draw_line(mlx_image_t *img, int x1, int y1, int x2, int y2, uint32_t color);
int get_rgba(int r, int g, int b, int a);
t_player *assign_player(int x, int y, int color);
void find_player(t_data *data);
void    free_game(t_data *data);
//parsing
void draw_map(t_data *data);
void draw_player(t_data *data);
void check_map(char **strs);
void check_zero_surrond(char **strs);
void check_tab(char **strs);
int out_of_elements(char c);
int check_no(char **strs, t_var *vars, t_textures *t);
int check_so(char **strs, t_var *vars, t_textures *t);
int check_ea(char **strs, t_var *vars, t_textures *t);
int check_we(char **strs, t_var *vars, t_textures *t);
void ft_rgb(char *str, t_color *color);
void ft_rgb_c(char *str, t_color *color);
int	rgb_f(char **strs, t_color *floor, t_textures *t, t_var *vars);
int	rgb_c(char **strs, t_color *floor, t_textures *t, t_var *vars);
void ft_rgb(char *str, t_color *color);
void ft_rgb_c(char *str, t_color *color);
char *ft_textures(char *str, int i);
void ft_draw_textures(t_data *data, float x_img, float y_start, float y_end);
void	check_map(char **strs);
void	check_elements(char **strs);
void	ft_draw_textures(t_data *data, float x_img, float y_start, float y_end);
void	ver_or_hor(float *x_txt, t_data *data);
void ft_start(int i, char **strs, t_window *win);

#endif
