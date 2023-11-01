/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:12:10 by zbenaiss          #+#    #+#             */
/*   Updated: 2022/10/27 07:28:35 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dstlen;
	size_t	destnow;

	i = 0;
	j = 0;
	if (dstsize == 0)
		return (ft_strlen(src));
	destnow = ft_strlen(dst);
	if (dstsize < destnow)
		return (ft_strlen(src) + dstsize);
	dstlen = dstsize - destnow - 1;
	i = destnow;
	while (j < dstlen && i < dstsize && src[j])
		dst[i++] = src[j++];
	dst[i] = '\0';
	return (ft_strlen(src) + destnow);
}
