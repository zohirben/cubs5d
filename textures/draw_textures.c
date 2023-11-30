/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 15:49:59 by sbellafr          #+#    #+#             */
/*   Updated: 2023/11/30 23:59:31 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	vertical_data(float *x_txt, t_data *data)
{
	float	ratio;

	if (fmod(data->x_ray, 16) == 0)
	{
		data->txt = data->txt1;
		ratio = data->txt->height / 16;
		*(x_txt) = fmod(data->y_ray, 16) * ratio;
	}
	else
	{
		data->txt = data->txt2;
		ratio = data->txt->height / 16;
		*(x_txt) = fmod(data->y_ray, 16) * ratio;

	}
}

void	hor_data(float *x_txt, t_data *data)
{
	float	ratio;

	if (fmod(data->y_ray, 16) == 0)
	{
		data->txt = data->txt3;
		ratio = data->txt->height / 16;
		*(x_txt) = fmod(data->x_ray, 16) * ratio;
	}
	else
	{
		data->txt = data->txt4;
		ratio = data->txt->height / 16;
		*(x_txt) = fmod(data->x_ray, 16) * ratio;
	}
}

void	ver_or_hor(float *x_txt, t_data *data)
{


	if (!data->is_hor)
	{
		vertical_data(x_txt, data);
	}
	else
	{
		hor_data(x_txt, data);

	}
}
