/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 10:32:11 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 22:06:30 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hotrace.h"

int	arena_init(t_arena *arena)
{
	t_arena_chunk	*chunk;

	chunk = malloc(sizeof(t_arena_chunk));
	if (!chunk)
		return (-1);
	chunk->buf = malloc(ARENA_CHUNK_SIZE);
	if (!chunk->buf)
	{
		free(chunk);
		return (-1);
	}
	chunk->next = NULL;
	arena->chunks = chunk;
	arena->current = chunk;
	arena->offset = 0;
	return (0);
}

static int	arena_grow(t_arena *arena, size_t len)
{
	t_arena_chunk	*chunk;
	size_t			size;

	size = ARENA_CHUNK_SIZE;
	if (len > size)
		size = len;
	chunk = malloc(sizeof(t_arena_chunk));
	if (!chunk)
		return (-1);
	chunk->buf = malloc(size);
	if (!chunk->buf)
	{
		free(chunk);
		return (-1);
	}
	chunk->next = NULL;
	arena->current->next = chunk;
	arena->current = chunk;
	arena->offset = 0;
	return (0);
}

char	*arena_strdup(t_arena *arena, const char *s)
{
	size_t	len;
	char	*result;

	len = ft_strlen(s) + 1;
	if (arena->offset + len > ARENA_CHUNK_SIZE && arena_grow(arena, len) < 0)
		return (NULL);
	result = arena->current->buf + arena->offset;
	ft_memmove(result, s, len);
	arena->offset += len;
	return (result);
}

void	arena_free(t_arena *arena)
{
	t_arena_chunk	*chunk;
	t_arena_chunk	*next;

	chunk = arena->chunks;
	while (chunk)
	{
		next = chunk->next;
		free(chunk->buf);
		free(chunk);
		chunk = next;
	}
	arena->chunks = NULL;
	arena->current = NULL;
	arena->offset = 0;
}
