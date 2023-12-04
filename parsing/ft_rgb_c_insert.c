/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_c_insert.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 23:50:05 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/04 21:38:55 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_rgb_c_one(char *str, int i, t_data *data)
{
	char	*buffer;
	int		j;

	buffer = malloc(4);
	j = 0;
	while (str[i] && !ft_isalnum(str[i]))
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
	data->ceiling.r = ft_atoi(buffer);
	free(buffer);
	if (data->ceiling.r > 255 || data->ceiling.r < 0)
	{
		printf("error check the number in the rgb\n");
		exit(2);
	}
	return (i);
}

int	ft_rgb_c_two(char *str, int i, t_data *data)
{
	char	*buffer;
	int		j;

	buffer = malloc(4);
	j = 0;
	while (str[i] && !ft_isalnum(str[i]))
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
	data->ceiling.g = ft_atoi(buffer);
	free(buffer);
	if (data->ceiling.g > 255 || data->ceiling.g < 0)
	{
		printf("error check the number in the rgb\n");
		exit(2);
	}
	return (i);
}

int	ft_rgb_c_three(char *str, int i, t_data *data)
{
	char	*buffer;
	int		j;

	buffer = malloc(4);
	j = 0;
	while (str[i] &&!ft_isalnum(str[i]))
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
	data->ceiling.b = ft_atoi(buffer);
	free(buffer);
	if (data->ceiling.b > 255 || data->ceiling.b < 0)
	{
		printf("error check the number in the rgb\n");
		exit(2);
	}
	return (i);
}

void	ft_rgb_c(char *str, t_data *data)
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
			i = ft_rgb_c_one(str, i, data);
			i = ft_rgb_c_two(str, i, data);
			i = ft_rgb_c_three(str, i, data);
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
