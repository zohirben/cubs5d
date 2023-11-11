/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaissa@1337.ma>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:12:04 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/11/11 19:21:15 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *ft_strdup(const char *s1)
{
	int i;
	char *str;

	i = 0;
	if (s1)
	{
		str = (char *)malloc(ft_strlen(s1) + 1);
		if (!str)
			return (0);
		ft_memcpy(str, s1, ft_strlen(s1));
		str[ft_strlen(s1)] = '\0';
	}
	return (str);
}
