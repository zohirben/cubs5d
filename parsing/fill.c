/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 16:42:46 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/04 21:40:01 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_textures_rgb(t_textures *t)
{
	int	i;

	i = 0;
	while (t->c[i])
	{
		if (!ft_isdigit(t->c[i]) && t->c[i] != 'C' && t->c[i] != ' '
			&& t->c[i] != ',' && t->c[i] != '\n')
		{
			printf("error there is an external component\n");
			exit(2);
		}
		i++;
	}
	i = 0;
	while (t->f[i])
	{
		if (!ft_isdigit(t->f[i]) && t->f[i] != 'F' && t->f[i] != ' '
			&& t->f[i] != ',' && t->f[i] != '\n')
		{
			printf("error there is an external component\n");
			exit(2);
		}
		i++;
	}
}

char	*ft_textures(char *str, int i)
{
	char	*returned;
	int		j;

	j = 0;
	i = i + 2;
	while (str[i] && str[i] != '.' && str[i + 1] != '/')
		i++;
	returned = malloc(ft_strlen(str) - i + 1);
	while (str[i] && str[i] != ' ' && str[i] != '\n' && str[i] != '\t')
	{
		returned[j] = str[i];
		i++;
		j++;
	}
	returned[j] = '\0';
	return (returned);
}

int	textures_checker(char **strs, t_var *v, t_textures *t, t_data *data)
{
	v->count = 0;
	while (strs[v->i])
	{
		v->j = 0;
		while (strs[v->i][v->j])
		{
			if (strs[v->i][v->j] == 'N' && strs[v->i][v->j + 1] == 'O')
				v->count += check_no(strs, v, t);
			else if (strs[v->i][v->j] == 'S' && strs[v->i][v->j + 1] == 'O')
				v->count += check_so(strs, v, t);
			else if (strs[v->i][v->j] == 'E' && strs[v->i][v->j + 1] == 'A')
				v->count += check_ea(strs, v, t);
			else if (strs[v->i][v->j] == 'W' && strs[v->i][v->j + 1] == 'E')
				v->count += check_we(strs, v, t);
			else if (strs[v->i][v->j] == 'F')
				v->count += rgb_f(strs, data, t, v);
			else if (strs[v->i][v->j] == 'C')
				v->count += rgb_c(strs, data, t, v);
			v->j++;
		}
		v->i++;
	}
	return (v->count);
}

int	ft_count_map(char *map)
{
	int		fd;
	char	*str;
	int		i;

	i = 0;
	fd = open(map, O_RDWR);
	while (1)
	{
		str = get_next_line(fd);
		free(str);
		if (!str)
			break ;
		i++;
	}
	close(fd);
	return (i);
}

char	**fill_strs(int len, char *str)
{
	int		fd;
	int		i;
	char	**strs;

	i = 0;
	fd = open(str, O_RDWR);
	strs = (char **)ft_calloc(len + 1, sizeof(char *));
	while (1)
	{
		strs[i] = get_next_line(fd);
		if (!strs[i])
			break ;
		i++;
	}
	return (strs);
}
