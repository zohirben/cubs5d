/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_separate_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 01:50:11 by sbellafr          #+#    #+#             */
/*   Updated: 2023/11/30 18:18:07 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_start(int i, char **strs, t_window *win)
{
	t_player	player;
	int			j;
	char		*dtr;
	int			dtrsize;
	int			len;

	dtrsize = 0;
	win->map.wide = 0;
	win->map.lenght = 0;
	j = 0;
	while (strs[j])
		j++;
	len = j - i + 1;
	if (len > i)
		win->map.mapo = (char **)ft_calloc(len + 1, sizeof(char *));
	else
	{
		printf("Error check map\n");
		exit(2);
	}
	j = 0;
	while (strs[i + 1] && strs[i + 1][0] == '\n')
		i++;
	i++;
	check_tab(strs);

	while (strs[i])
	{
		if (ft_strlen(strs[i]) > win->map.lenght)
			win->map.lenght = ft_strlen(strs[i]);
		win->map.mapo[j] = ft_strdup(strs[i]);
		free(strs[i]);
		j++;
		i++;
	}
	i = 0;
	j = 0;
	while (win->map.mapo[i])
		i++;
	check_map(win->map.mapo);
	check_zero_surrond(win->map.mapo);
	win->map.lenght--;
	win->map.wide = i;
}
