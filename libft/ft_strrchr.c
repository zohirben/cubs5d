/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 04:22:15 by zbenaiss          #+#    #+#             */
/*   Updated: 2022/10/26 04:22:17 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	*arr;
	int		j;

	arr = NULL;
	i = 0;
	j = ft_strlen(s);
	while (i <= j)
	{
		if (((char *)s)[i] == (char)c)
			arr = ft_strchr(&s[i], c);
		i++;
	}
	return (arr);
}
