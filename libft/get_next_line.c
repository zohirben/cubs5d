/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zbenaiss <zbenaiss@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 19:49:16 by zbenaiss          #+#    #+#             */
/*   Updated: 2023/04/09 17:10:38 by zbenaiss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	checkn(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*cut_stock(char *save, int i)
{
	char	*cache;

	if (!save)
		return (NULL);
	if (save[i + 1] == '\0')
	{
		free(save);
		return (NULL);
	}
	cache = ft_substrgnl(save, i + 1, ft_strlengnl(save));
	free(save);
	save = 0;
	return (cache);
}

char	*nerd(char *cache, int fd, int *j)
{
	char	*strh;

	strh = ft_callocgnl(1, BUFFER_SIZE + 1);
	*j = 1;
	while (checkn(cache) != 1 && *j != 0)
	{
		*j = read(fd, strh, BUFFER_SIZE);
		if (*j == -1)
		{
			free(cache);
			cache = NULL;
			free(strh);
			strh = NULL;
			return (NULL);
		}
		else if (*j > 0)
			cache = ft_strjoingnl(cache, strh, *j);
	}
	free(strh);
	strh = NULL;
	return (cache);
}

char	*checkerror(char *cache, int fd, int *j)
{
	if (fd < 0 || fd == 1 || fd == 2 || BUFFER_SIZE <= 0)
		return (NULL);
	if (cache == NULL)
		cache = ft_callocgnl(1, BUFFER_SIZE + 1);
	cache = nerd(cache, fd, j);
	return (cache);
}

char	*get_next_line(int fd)
{
	static char	*stock;
	char		*line;
	int			i;
	int			j;

	line = NULL;
	stock = checkerror(stock, fd, &j);
	if (stock == NULL)
		return (NULL);
	i = 0;
	while (stock[i] != '\n' && stock[i])
		i++;
	if (stock != NULL && stock[i] == '\n')
	{
		line = ft_substrgnl(stock, 0, i + 1);
		stock = cut_stock(stock, i);
		return (line);
	}
	else if (j == 0 && ft_strlengnl(stock) == 0)
		free(stock);
	else
		line = stock;
	stock = NULL;
	return (line);
}

// int main()
// {
//     int fd;
//     fd = open("btata.txt", O_CREAT | O_RDONLY);
//     printf("%s", get_next_line(fd));
// }