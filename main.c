/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 18:05:22 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/11/13 16:00:54 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void key_movements(t_data *data, float delta_distance)
{
    if (mlx_is_key_down(data->mlx, MLX_KEY_ESCAPE))
    {
        mlx_close_window(data->mlx);
        free_game(data);
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
    draw_rays(data);
    draw_map(data);
    draw_player(data);
    draw_rays_color(data);
}


int main()
{
    int fd;
    t_data *data;

    data = (t_data *)malloc(sizeof(t_data));
    if (!data)
        return (1);
    ft_memset(data, 0, sizeof(t_data));
    fd = open("map.cub", O_CREAT | O_RDONLY);
    if (fd == -1)
        exit(1);
    make_map(data, fd);
    data->dda = malloc(sizeof(t_dda));
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