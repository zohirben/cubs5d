/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:58:35 by sbellafr          #+#    #+#             */
/*   Updated: 2023/12/04 15:06:18 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	rgb_f(char **strs, t_data *data, t_textures *t, t_var *vars)
{
	if (vars->i > vars->last_line)
		vars->last_line = vars->i;
	t->f = ft_strdup(strs[vars->i]);
	ft_rgb(t->f, data);
	return (1);
}

int	rgb_c(char **strs, t_data *data, t_textures *t, t_var *vars)
{
	if (vars->i > vars->last_line)
		vars->last_line = vars->i;
	t->c = ft_strdup(strs[vars->i]);
	ft_rgb_c(t->c, data);
	return (1);
}
