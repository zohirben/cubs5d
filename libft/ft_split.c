/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 21:12:01 by zbenaiss          #+#    #+#             */
/*   Updated: 2022/10/26 23:18:51 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countword(char *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		while (s[i] == c)
		{
			i++;
		}
		if (s[i] && s[i] != c)
		{
			count++;
		}
		while (s[i] != c && s[i])
		{
			i++;
		}
	}
	return (count);
}

static int	ft_wordsize(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
	{
		i++;
	}
	return (i);
}

static char	*ft_word(char *s, char c)
{
	int		i;
	int		wordlen;
	char	*word;

	i = 0;
	wordlen = ft_wordsize(s, c);
	word = (char *)malloc(sizeof(char) * (wordlen + 1));
	if (!word)
		return (0);
	while (i < wordlen)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	char	*s2;
	char	**str;

	if (!s)
		return (0);
	s2 = (char *)s;
	str = (char **)malloc(sizeof(char *) * (ft_countword(s2, c) + 1));
	if (!str)
		return (0);
	i = 0;
	while (*s2)
	{
		while (*s2 == c && *s2)
			s2++;
		if (*s2 != c && *s2)
		{
			str[i] = ft_word(s2, c);
			i++;
		}
		while (*s2 != c && *s2)
			s2++;
	}
	str[i] = NULL;
	return (str);
}
