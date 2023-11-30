/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:58:35 by sbellafr          #+#    #+#             */
/*   Updated: 2023/11/28 18:11:50 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb_f(char **strs, t_color *floor, t_textures *t, t_var *vars)
{
	if (vars->i > vars->last_line)
		vars->last_line = vars->i;
	t->f = ft_strdup(strs[vars->i]);
	ft_rgb(t->f, floor);
	return (1);
}

int	rgb_c(char **strs, t_color *ceiling, t_textures *t, t_var *vars)
{
	if (vars->i > vars->last_line)
		vars->last_line = vars->i;
	t->c = ft_strdup(strs[vars->i]);
	ft_rgb_c(t->c, ceiling);
	return (1);
}
