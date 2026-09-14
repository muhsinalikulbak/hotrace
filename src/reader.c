/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 18:02:14 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 18:41:16 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hotrace.h"

int	reader_init(t_reader *r)
{
	r->cap = READ_SIZE;
	r->buf = malloc(r->cap);
	if (!r->buf)
		return (-1);
	r->start = 0;
	r->end = 0;
	r->eof = 0;
	return (0);
}

void	reader_free(t_reader *r)
{
	free(r->buf);
	r->buf = NULL;
}

static int	grow(t_reader *r)
{
	char	*new_buf;

	new_buf = malloc(r->cap * 2);
	if (!new_buf)
		return (-1);
	ft_memmove(new_buf, r->buf, r->end);
	free(r->buf);
	r->buf = new_buf;
	r->cap *= 2;
	return (0);
}

static int	fill(t_reader *r)
{
	ssize_t	n;

	ft_memmove(r->buf, r->buf + r->start, r->end - r->start);
	r->end -= r->start;
	r->start = 0;
	if (r->end + 1 >= r->cap && grow(r) < 0)
		return (-1);
	if (out_flush() < 0)
		return (-1);
	n = read(0, r->buf + r->end, r->cap - r->end - 1);
	if (n < 0)
		return (-1);
	if (n == 0)
		r->eof = 1;
	r->end += n;
	return (0);
}

int	reader_next(t_reader *r, char **line)
{
	char	*nl;

	while (1)
	{
		*line = r->buf + r->start;
		nl = ft_memchr(*line, '\n', r->end - r->start);
		if (nl)
		{
			*nl = '\0';
			r->start = nl - r->buf + 1;
			return (1);
		}
		if (r->eof && r->start < r->end)
		{
			r->buf[r->end] = '\0';
			r->start = r->end;
			return (1);
		}
		if (r->eof)
			return (0);
		if (fill(r) < 0)
			return (-1);
	}
}
