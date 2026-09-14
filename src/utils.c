/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 10:32:11 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 22:06:30 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hotrace.h"

void	ft_memmove(char *dst, const char *src, size_t n)
{
	register size_t	i;
	register size_t	cnt;

	if (dst == src || n == 0)
		return ;
	if (dst < src)
	{
		i = 0;
		while (i < n)
		{
			dst[i] = src[i];
			i++;
		}
		return ;
	}
	cnt = n;
	while (cnt > 0)
	{
		cnt--;
		dst[cnt] = src[cnt];
	}
}

char	*ft_memchr(char *s, char c, size_t n)
{
	register size_t	i;
	register char	*ptr;

	i = 0;
	ptr = s;
	while (i < n)
	{
		if (ptr[i] == c)
			return (ptr + i);
		i++;
	}
	return (NULL);
}

size_t	ft_strlen(const char *s)
{
	register size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdup(const char *s)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	dup = malloc(len + 1);
	if (!dup)
		return (NULL);
	ft_memmove(dup, s, len + 1);
	return (dup);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	register size_t	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
