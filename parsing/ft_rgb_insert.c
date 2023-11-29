/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 23:48:41 by sbellafr          #+#    #+#             */
/*   Updated: 2023/11/28 17:37:55 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_rgb_one(char *str, int i, t_color *color)
{
	char	*buffer;
	int		j;

	buffer = malloc(4);
	j = 0;
	while (!ft_isalnum(str[i]))
		i++;
	if (ft_isalnum(str[i]))
		while (str[i] && ft_isalnum(str[i]))
			buffer[j++] = str[i++];
	buffer[j] = '\0';
	if (buffer[0] == '\0')
	{
		printf("please check the rgb\n");
		exit(2);
	}
	color->r = ft_atoi(buffer);
	free(buffer);
	if (color->r > 255 || color->r < 0)
	{
		printf("error check the number in the rgb\n");
		exit(2);
	}
	return (i);
}

int	ft_rgb_two(char *str, int i, t_color *color)
{
	char	*buffer;
	int		j;

	buffer = malloc(4);
	j = 0;
	while (!ft_isalnum(str[i]))
		i++;
	if (ft_isalnum(str[i]))
		while (str[i] && ft_isalnum(str[i]))
			buffer[j++] = str[i++];
	buffer[j] = '\0';
	if (buffer[0] == '\0')
	{
		printf("please check the rgb\n");
		exit(2);
	}
	color->g = ft_atoi(buffer);
	free(buffer);
	if (color->g > 255 || color->g < 0)
	{
		printf("error check the number in the rgb\n");
		exit(2);
	}
	return (i);
}

int	ft_rgb_three(char *str, int i, t_color *color)
{
	char	*buffer;
	int		j;

	buffer = malloc(4);
	j = 0;
	while (!ft_isalnum(str[i]))
		i++;
	if (ft_isalnum(str[i]))
		while (str[i] && ft_isalnum(str[i]))
			buffer[j++] = str[i++];
	buffer[j] = '\0';
	if (buffer[0] == '\0')
	{
		printf("please check the rgb\n");
		exit(2);
	}
	color->b = ft_atoi(buffer);
	free(buffer);
	if (color->b > 255 || color->b < 0)
	{
		printf("error check the number in the rgb\n");
		exit(2);
	}
	return (i);
}

void	ft_rgb(char *str, t_color *color)
{
	int		i;
	int		j;
	char	*buffer;

	i = -1;
	while (str[++i])
	{
		if (ft_isalpha(str[i]))
		{
			i++;
			i = ft_rgb_one(str, i, color);
			i = ft_rgb_two(str, i, color);
			i = ft_rgb_three(str, i, color);
		}
	}
	i = -1;
	j = 0;
	while (str[++i])
		if (str[i] == ',')
			j++;
	if (j > 2)
	{
		printf("Error: check the rgb\n");
		exit(2);
	}
}
