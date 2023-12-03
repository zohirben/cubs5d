/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 19:48:07 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/12/03 23:26:50 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	get_rgba(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
t_player	*assign_player(int x, int y, int color)
{
	t_player	*player;

	player = malloc(sizeof(t_player));
	if (!player)
		exit(1);
	player->x = x;
	player->y = y;
	return (player);
}
void	find_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j] && data->map[i][j] != '\n')
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'E'
				|| data->map[i][j] == 'W' || data->map[i][j] == 'S')
			{
				data->player = assign_player(j, i, get_rgba(20, 100, 93, 255));
				break ;
			}
			j++;
		}
		i++;
	}
}
// void	free_game(t_data *data)
// {
// 	int	i;

// 	free(data->dda);
// 	i = 0;
// 	while (data->map[i] != NULL)
// 	{
// 		free(data->map[i]);
// 		i++;
// 	}
// 	free(data->map);
// }
