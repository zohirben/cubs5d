/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_insert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 23:48:41 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/01 01:01:14 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_rgb_one(char *str, int i, t_data *data)
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
	data->floor.r = ft_atoi(buffer);
	free(buffer);
	if (data->floor.r > 255 || data->floor.r < 0)
	{
		printf("error check the number in the rgb\n");
		exit(2);
	}
	return (i);
}

int	ft_rgb_two(char *str, int i, t_data *data)
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
	data->floor.g = ft_atoi(buffer);
	free(buffer);
	if (data->floor.g > 255 || data->floor.g < 0)
	{
		printf("error check the number in the rgb\n");
		exit(2);
	}
	return (i);
}

int	ft_rgb_three(char *str, int i, t_data *data)
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
	data->floor.b = ft_atoi(buffer);
	free(buffer);
	if (data->floor.b > 255 || data->floor.b < 0)
	{
		printf("error check the number in the rgb\n");
		exit(2);
	}
	return (i);
}

void	ft_rgb(char *str, t_data *data)
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
			i = ft_rgb_one(str, i, data);
			i = ft_rgb_two(str, i, data);
			i = ft_rgb_three(str, i, data);
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
