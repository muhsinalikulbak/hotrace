/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 10:22:52 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 22:37:29 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hotrace.h"

static int	search_line(t_hashtable *ht, const char *line)
{
	char	*value;

	value = list_find(ht, line);
	if (value && (out_str(value) < 0 || out_str("\n") < 0))
		return (-1);
	if (!value && (out_str(line) < 0 || out_str(": Not found.\n") < 0))
		return (-1);
	return (0);
}

static int	store_key(t_arena *arena, const char *line, char **key)
{
	*key = arena_strdup(arena, line);
	if (!*key)
		return (-1);
	return (0);
}

static t_state	next_state(t_state state, const char *line)
{
	if (state == WAITING_KEY && line[0] == '\0')
		return (SEARCHING);
	if (state == WAITING_KEY)
		return (WAITING_VALUE);
	if (state == WAITING_VALUE)
		return (WAITING_KEY);
	return (SEARCHING);
}

int	process_store_search(t_reader *reader, t_hashtable *ht,
	t_arena *arena, t_pool **pool)
{
	char	*line;
	char	*key;
	t_state	state;
	int		ret;

	state = WAITING_KEY;
	key = NULL;
	ret = reader_next(reader, &line);
	while (ret == 1)
	{
		if (state == SEARCHING)
			ret = search_line(ht, line);
		else if (state == WAITING_VALUE)
			ret = list_add(ht, key, arena_strdup(arena, line), pool);
		else if (line[0] != '\0')
			ret = store_key(arena, line, &key);
		if (ret < 0)
			return (-1);
		state = next_state(state, line);
		ret = reader_next(reader, &line);
	}
	return (ret);
}
