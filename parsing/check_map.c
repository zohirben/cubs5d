/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/14 23:31:08 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/04 19:25:59 by sbellafr         ###   ########.fr       */
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

void	check_zero_surrond(char **s)
{
	int		k;
	t_var	v;

	v.j = 0;
	v.i = 0;
	k = 0;
	while (s[k])
		k++;
	while (v.i < k - 1)
	{
		v.j = -1;
		while (s[v.i][++v.j])
		{
			if (s[v.i][v.j] && checker_0_p(s[v.i][v.j]))
			{
				if (s[v.i][v.j] && zero_one(s, v.i, v.j))
				{
					printf("Error check the zero or the player place\n");
					exit(2);
				}
			}
		}
		v.i++;
	}
	check_last_zero(s, v.i);
}
