/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbellafr <sbellafr@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 23:05:35 by sbellafr          #+#    #+#             */
/*   Updated: 2023/11/28 18:13:11 by sbellafr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_no(char **strs, t_var *vars, t_textures *t)
{
	if (vars->i > (vars->last_line))
		(vars->last_line) = vars->i;
	t->no = ft_textures(strs[vars->i], vars->j);
	return (1);
}

int	check_so(char **strs, t_var *vars, t_textures *t)
{
	if (vars->i > vars->last_line)
		(vars->last_line) = vars->i;
	t->so = ft_textures(strs[vars->i], vars->j);
	return (1);
}

int	check_ea(char **strs, t_var *vars, t_textures *t)
{
	if (vars->i > vars->last_line)
		vars->last_line = vars->i;
	t->ea = ft_textures(strs[vars->i], vars->j);
	return (1);
}

int	check_we(char **strs, t_var *vars, t_textures *t)
{
	if (vars->i > vars->last_line)
		vars->last_line = vars->i;
	t->we = ft_textures(strs[vars->i], vars->j);
	return (1);
}
