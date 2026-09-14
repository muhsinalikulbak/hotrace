/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hotrace.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtaheri@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/13 11:00:32 by mtaheri           #+#    #+#             */
/*   Updated: 2026/09/13 22:31:09 by mtaheri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HOTRACE_H
# define HOTRACE_H

# include <stdlib.h>
# include <unistd.h>

# define READ_SIZE 65536
# define OUT_SIZE 65536
# define POOL_SIZE 65536
# define ARENA_CHUNK_SIZE 1048576
# define HASH_SIZE 2097152

typedef enum e_state
{
	WAITING_KEY,
	WAITING_VALUE,
	SEARCHING
}	t_state;

typedef struct s_node
{
	char			*key;
	char			*value;
	struct s_node	*next;
}	t_node;

typedef struct s_hashtable
{
	t_node	**buckets;
}	t_hashtable;

typedef struct s_pool
{
	t_node			nodes[POOL_SIZE];
	struct s_pool	*next;
	size_t			idx;
}	t_pool;

typedef struct s_arena_chunk
{
	char					*buf;
	struct s_arena_chunk	*next;
}	t_arena_chunk;

typedef struct s_arena
{
	t_arena_chunk	*chunks;
	t_arena_chunk	*current;
	size_t			offset;
}	t_arena;

typedef struct s_reader
{
	char	*buf;
	size_t	cap;
	size_t	start;
	size_t	end;
	int		eof;
}	t_reader;

int				reader_init(t_reader *r);
int				reader_next(t_reader *r, char **line);
void			reader_free(t_reader *r);

int				process_store_search(t_reader *reader, t_hashtable *ht,
					t_arena *arena, t_pool **pool);

int				out_write(const char *s, size_t len);
int				out_str(const char *s);
int				out_flush(void);

int				ht_init(t_hashtable *ht);
int				list_add(t_hashtable *ht, char *key, char *value,
					t_pool **pool);
char			*list_find(t_hashtable *ht, const char *key);
void			list_free(t_hashtable *ht);

t_pool			*pool_new(void);
t_node			*pool_alloc(t_pool **pool);
void			pool_free(t_pool *pool);

int				arena_init(t_arena *arena);
char			*arena_strdup(t_arena *arena, const char *s);
void			arena_free(t_arena *arena);

void			ft_memmove(char *dst, const char *src, size_t n);
char			*ft_memchr(char *s, char c, size_t n);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
size_t			djb2_hash(const char *str);

#endif
