/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkulbak@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 15:53:09 by mkulbak           #+#    #+#             */
/*   Updated: 2026/09/13 22:06:22 by mkulbak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

size_t	djb2_hash(const char *str)
{
	register size_t		hash;
	register const char	*s;

	hash = 5381;
	s = str;
	while (*s)
	{
		hash = ((hash << 5) + hash) + *s;
		s++;
	}
	return (hash & (HASH_SIZE - 1));
}

int	list_add(t_hashtable *ht, char *key, char *value, t_pool **pool)
{
	t_node	*node;
	t_node	*existing;
	size_t	index;

	if (!key || !value)
		return (-1);
	index = djb2_hash(key);
	existing = ht->buckets[index];
	while (existing)
	{
		if (ft_strcmp(existing->key, key) == 0)
		{
			existing->value = value;
			return (0);
		}
		existing = existing->next;
	}
	node = pool_alloc(pool);
	if (!node)
		return (-1);
	node->key = key;
	node->value = value;
	node->next = ht->buckets[index];
	ht->buckets[index] = node;
	return (0);
}

char	*list_find(t_hashtable *ht, const char *key)
{
	t_node	*node;
	size_t	index;

	index = djb2_hash(key);
	node = ht->buckets[index];
	while (node)
	{
		if (ft_strcmp(node->key, key) == 0)
			return (node->value);
		node = node->next;
	}
	return (NULL);
}

int	ht_init(t_hashtable *ht)
{
	size_t	i;

	ht->buckets = malloc(sizeof(t_node *) * HASH_SIZE);
	if (!ht->buckets)
		return (-1);
	i = 0;
	while (i < HASH_SIZE)
	{
		ht->buckets[i] = NULL;
		i++;
	}
	return (0);
}

void	list_free(t_hashtable *ht)
{
	free(ht->buckets);
	ht->buckets = NULL;
}
