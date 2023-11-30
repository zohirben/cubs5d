/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:31:08 by sbellafr          #+#    #+#             */
/*   Updated: 2023/11/28 21:25:18 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	zero_or_one(char c)
{
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

void	check_tab(char **strs)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (strs[i][j] && strs[i][j] == '\t')
			{
				printf("Error there is a tab in the map\n");
				exit(0);
			}
			j++;
		}
		i++;
	}
}

int	zero_one(char **strs, int i, int j)
{
	if (zero_or_one(strs[i][j + 1]) || zero_or_one(strs[i][j - 1])
		|| zero_or_one(strs[i + 1][j]) || zero_or_one(strs[i - 1][j]))
		return (1);
	return (0);
}

void	check_last_zero(char **strs, int i)
{
	int	j;

	j = 0;
	while (strs[i][j])
	{
		if (strs[i][j] == '0')
		{
			printf("Error check the zero\n");
			exit(2);
		}
		j++;
	}
	check_tab(strs);
}

void	check_zero_surrond(char **strs)
{
	int		k;
	t_var	vars;

	vars.j = 0;
	vars.i = 0;
	k = 0;
	while (strs[k])
		k++;
	while (vars.i < k - 1)
	{
		vars.j = -1;
		while (strs[vars.i][++vars.j])
		{
			if (strs[vars.i][vars.j] && strs[vars.i][vars.j] == '0')
			{
				if (strs[vars.i][vars.j] && zero_one(strs, vars.i, vars.j))
				{
					printf("Error check the zero\n");
					exit(2);
				}
			}
		}
		vars.i++;
	}
	check_last_zero(strs, vars.i);
}
