/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 15:09:26 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/04/09 17:12:04 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdupgnl(char *s1)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)malloc(ft_strlengnl(s1) + 1);
	if (!str)
		return (0);
	str[ft_strlengnl(s1)] = '\0';
	return (str);
}

char	*ft_strjoingnl(char *s1, char *s2, size_t size)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (!s1 || !s2)
		return (0);
	str = (char *)malloc(ft_strlengnl(s1) + ft_strlengnl(s2) + 1);
	if (!str)
		return (0);
	i = 0;
	j = 0;
	while (s1[i])
		str[j++] = s1[i++];
	i = 0;
	while (s2[i] && i < size)
		str[j++] = s2[i++];
	str[j] = '\0';
	free(s1);
	return (str);
}

char	*ft_substrgnl(char *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (0);
	if (start > ft_strlengnl(s))
		return (ft_strdupgnl(""));
	if ((start + len) > ft_strlengnl(s))
		len = ft_strlengnl(s) - start;
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

size_t	ft_strlengnl(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_callocgnl(size_t count, size_t size)
{
	size_t	i;
	char	*str;

	i = 0;
	str = (char *)malloc(count * size);
	if (!str)
		return (0);
	while (i < (count * size))
	{
		str[i++] = '\0';
	}
	return (str);
}
