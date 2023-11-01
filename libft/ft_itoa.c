/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:11:30 by zbenaiss          #+#    #+#             */
/*   Updated: 2022/10/26 04:29:33 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_numblen(long numb)
{
	int		i;
	long	number;

	i = 0;
	number = numb;
	if (numb < 0)
	{
		numb = numb * -1;
		i++;
	}
	if (numb == 0)
		return (1);
	while (number != 0)
	{
		number = number / 10;
		i++;
	}
	return (i);
}

static char	*ft_all(char *str, long numb, int len, int i)
{
	str = (char *)malloc(len + 1);
	if (!str)
		return (0);
	str[len--] = '\0';
	if (numb == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (numb < 0)
	{
		str[0] = '-';
		numb *= -1;
	}
	i = len;
	while (numb != 0)
	{
		str[i] = (numb % 10) + 48;
		numb = numb / 10;
		i--;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	long	numb;
	int		i;
	int		len;
	char	*str;

	str = 0;
	i = 0;
	numb = n;
	len = ft_numblen(numb);
	str = ft_all(str, numb, len, i);
	if (!str)
		return (0);
	return (str);
}
