/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obelaizi <obelaizi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 20:40:41 by obelaizi          #+#    #+#             */
/*   Updated: 2022/11/14 18:42:21 by obelaizi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	line(char *buf, char **rest, int fd)
{
	int	i;

	while (!check_char(*rest, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
			return (free(buf), free(*rest), 0);
		if (!i)
			break ;
		buf[i] = 0;
		*rest = ft_strjoin(*rest, buf);
	}
	return (1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*result;
	int		size;
	int		i;
	int		j;
	int		check;

	if (!(*s2))
		return (NULL);
	if (!s1)
		s1 = ft_strdup("");
	i = -1;
	j = 0;
	check = ft_strlen(s1);
	size = check + ft_strlen(s2);
	result = malloc(size + 1);
	if (!result)
		return (0);
	while (++i < check)
		result[i] = s1[i];
	while (i < size)
		result[i++] = s2[j++];
	return (free(s1), result[i] = 0, result);
}

char	*ignore(char *s)
{
	int		i;
	char	*result;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	result = ft_strjoin(NULL, &s[i]);
	return (free(s), result);
}

char	*fill(char *src)
{
	int		i;
	char	*dst;
	int		j;

	j = 0;
	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	if (src[i] == '\n')
		i++;
	dst = malloc(i + 1);
	if (!dst)
		return (free(src), NULL);
	dst[i] = 0;
	while (i--)
		dst[j++] = *(src++);
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buf;
	char		*result;
	int			i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!check_char(rest, '\n'))
	{
		i = read(fd, buf, BUFFER_SIZE);
		if (i == -1)
			return (free(buf), NULL);
		buf[i] = 0;
		if (!i)
			break ;
		rest = ft_strjoin(rest, buf);
	}
	if (!rest)
		return (free(buf), NULL);
	if (!(*rest))
		return (free(rest), free(buf), NULL);
	return (result = fill(rest), free(buf), rest = ignore(rest), result);
}
