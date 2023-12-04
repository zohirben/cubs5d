/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_walls.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:41:50 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/04 21:39:03 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_player(char **strs)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	j = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == 'N' || strs[i][j] == 'S' || strs[i][j] == 'E'
				|| strs[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		printf("Error check the player\n");
		exit(2);
	}
}

int	check_first_line(char *str)
{
	int	i;

	i = 0;
	if (str)
	{
		while (str[i])
		{
			if (str[i] && !(str[i] == '1' || str[i] == '\n' || str[i] == ' '))
			{
				printf("Error check Wall\n");
				exit(0);
			}
			i++;
		}
	}
	return (1);
}

void	check_right_wall(char	**strs)
{
	int	i;

	i = 1;
	while (strs[i][0] && strs[i][0] != '1' && strs[i][0] != ' ')
	{
		if (strs[i][0] != '\n')
		{
			printf("error : there is something instead of 1 in the wall\n");
			exit(2);
		}
		i++;
	}
}

void	check_new_line(char	**strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (strs[i][0] == '\n')
		{
			printf("Error a new line in the map\n");
			exit(2);
		}
		i++;
	}
}

void	check_map(char **strs)
{
	int	i;
	int	j;

	check_first_line(strs[0]);
	check_player(strs);
	check_right_wall(strs);
	check_new_line(strs);
	i = 0;
	j = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] == '\t')
			{
				printf("Error there is a tab in the map\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}
