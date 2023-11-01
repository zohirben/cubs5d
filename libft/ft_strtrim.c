/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:12:47 by zbenaiss          #+#    #+#             */
/*   Updated: 2022/10/26 03:50:52 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_charfind(const char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (c == str[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*str;

	if (!s1)
		return (0);
	if (!set)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start])
	{
		if (ft_charfind(set, s1[start]))
			start++;
		else
			break ;
	}
	end = ft_strlen(s1) - 1;
	if (start < end)
	{
		while (ft_charfind(set, s1[end]))
			end--;
	}
	str = ft_substr(s1, start, (end - start) + 1);
	return (str);
}
