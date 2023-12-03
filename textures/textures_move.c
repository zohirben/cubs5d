/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_move.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:13:32 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/03 18:27:18 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	condition_setter(t_data *data, t_floats f, float x_img)
{
	if (((((int)f.y_txt * data->txt->width) + (int)f.x_txt) < data->txt->width
			* data->txt->height) && (((int)f.y_img * data->img->width)
			+ (int)x_img) < data->img->width * data->img->height)
		return (1);
	return (0);
}

unsigned char	*copy_pixels_text(t_data *data, t_floats f, float x_img)
{
	return (&data->txt->pixels[(((int)f.y_txt * data->txt->width)
				+ (int)f.x_txt) * data->txt->bytes_per_pixel]);
}

unsigned char	*copy_pixels_image(t_data *data, t_floats f, float x_img)
{
	return (&data->img->pixels[(((int)f.y_img * data->img->width) 
				+ (int)x_img) * data->txt->bytes_per_pixel]);
}

void	ft_draw_textures(t_data *data, float x_img, float y_start, float y_end)
{
	unsigned char	*text;
	unsigned char	*image;
	t_floats		f;
	float			wall_height;

	wall_height = y_end - y_start;
	f.y_img = y_start;
	ver_or_hor(&f.x_txt, data);
		
	f.y_txt = 0;
	f.y_increment = data->txt->height / wall_height;
	while (f.y_txt <= data->txt->height && f.y_img <= y_end)
	{
		if (condition_setter(data, f, x_img))
		{
			text = copy_pixels_text(data, f, x_img);
			image = copy_pixels_image(data, f, x_img);
			ft_memmove(image, text, data->txt->bytes_per_pixel);
		}
		f.y_img++;
		f.y_txt += f.y_increment;
	}
}
