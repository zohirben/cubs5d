/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 19:54:39 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/04 21:40:36 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	out_of_elements(char c)
{
	if (c != '1' && c != '0' && c != 'W' && c != ' ' && c != '\n' && c != 'N'
		&& c != 'S' && c != 'E')
		return (1);
	return (0);
}

void	check_elements(char **strs)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j])
		{
			if (out_of_elements(strs[i][j]))
				count++;
			j++;
		}
		i++;
	}
	if (count > 0)
	{
		printf("Error check map elements\n");
		exit(0);
	}
}
