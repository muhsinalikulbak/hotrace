/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 10:22:52 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 22:37:29 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hotrace.h"

static int	init_all(t_reader *reader, t_arena *arena, t_hashtable *ht)
{
	if (reader_init(reader) < 0)
		return (write(2, "Error on reader_init\n", 21), -1);
	if (arena_init(arena) < 0)
	{
		reader_free(reader);
		return (write(2, "Error on arena_init\n", 20), -1);
	}
	if (ht_init(ht) < 0)
	{
		reader_free(reader);
		arena_free(arena);
		return (write(2, "Error on ht_init\n", 17), -1);
	}
	return (0);
}

int	main(void)
{
	t_reader	reader;
	t_hashtable	ht;
	t_arena		arena;
	t_pool		*pool;
	int			ret;

	if (init_all(&reader, &arena, &ht) < 0)
		return (1);
	pool = NULL;
	ret = process_store_search(&reader, &ht, &arena, &pool);
	if (out_flush() < 0)
		ret = -1;
	reader_free(&reader);
	list_free(&ht);
	pool_free(pool);
	arena_free(&arena);
	if (ret < 0)
		return (write(2, "Error\n", 6), 1);
	return (0);
}
