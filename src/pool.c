/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pool.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:53:09 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 22:06:22 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/hotrace.h"

t_pool	*pool_new(void)
{
	t_pool	*pool;

	pool = malloc(sizeof(t_pool));
	if (!pool)
		return (NULL);
	pool->idx = 0;
	pool->next = NULL;
	return (pool);
}

t_node	*pool_alloc(t_pool **pool)
{
	t_pool	*new_pool;

	if (!*pool || (*pool)->idx >= POOL_SIZE)
	{
		new_pool = pool_new();
		if (!new_pool)
			return (NULL);
		new_pool->next = *pool;
		*pool = new_pool;
	}
	return (&(*pool)->nodes[(*pool)->idx++]);
}

void	pool_free(t_pool *pool)
{
	t_pool	*next;

	while (pool)
	{
		next = pool->next;
		free(pool);
		pool = next;
	}
}
