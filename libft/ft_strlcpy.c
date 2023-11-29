/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:58:59 by zbenaiss          #+#    #+#             */
/*   Updated: 2022/10/25 16:59:00 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	char	*src1;

	i = 0;
	src1 = (char *)src;
	if (dstsize == 0)
		return (ft_strlen(src1));
	while (src1[i] && i < dstsize - 1)
	{
		dst[i] = src1[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen(src1));
}
