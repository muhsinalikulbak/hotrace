/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak <mkulbak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:58:24 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 23:18:46 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hotrace.h"

static int	write_all(const char *s, size_t len)
{
	ssize_t	n;

	while (len > 0)
	{
		n = write(1, s, len);
		if (n < 0)
			return (-1);
		s += n;
		len -= n;
	}
	return (0);
}

int	out_write(const char *s, size_t len)
{
	static char		buf[OUT_SIZE];
	static size_t	used;

	if (!s || used + len > OUT_SIZE)
	{
		if (write_all(buf, used) < 0)
			return (-1);
		used = 0;
	}
	if (!s)
		return (0);
	if (len > OUT_SIZE)
		return (write_all(s, len));
	ft_memmove(buf + used, s, len);
	used += len;
	return (0);
}

int	out_str(const char *s)
{
	return (out_write(s, ft_strlen(s)));
}

int	out_flush(void)
{
	return (out_write(NULL, 0));
}
