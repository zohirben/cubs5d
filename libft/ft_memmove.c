/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:11:50 by zbenaiss          #+#    #+#             */
/*   Updated: 2022/10/27 00:35:04 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t	i;
	char	*str1;
	char	*str2;

	i = len - 1;
	str1 = (char *)src;
	str2 = (char *)dst;
	if (str1 < str2)
	{
		while ((int)i != -1)
		{
			str2[i] = str1[i];
			i--;
		}
	}
	else
		ft_memcpy(str2, str1, len);
	return (str2);
}
