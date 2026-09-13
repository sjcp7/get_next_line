/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 15:25:52 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/13 14:30:18 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static size_t	gnl_strlen(const char *s);
static int		gnl_resize(char **s, size_t size);

t_string	gnl_create_string(char *str, size_t capacity)
{
	t_string	s;
	size_t		i;

	s.s = str;
	s.capacity = capacity;
	s.len = gnl_strlen(str);
	if (!str)
	{
		s.s = (char *)malloc(capacity + 1);
		if (!s.s)
			return (s);
		i = 0;
		while (i <= capacity)
			s.s[i++] = '\0';		
	}
	return (s);
}

int	gnl_consume(t_buffer *buf, t_string *s, char **line)
{
	while (buf->i < buf->len)
	{
		if (!gnl_string_append(s, buf->buf[buf->i]))
			return (0);
		if (buf->buf[buf->i++] == '\n')
		{
			s->s[s->len] = '\0';
			*line = s->s;
			return (1);
		}
	}
	return (1);
}

int	gnl_string_append(t_string *str, char c)
{
	if (!str->s)
		return (0);
	if (str->len + 1 > str->capacity)
	{
		if (!gnl_resize(&str->s, str->capacity * 2))
			return (0);
		str->capacity *= 2;
	}
	str->s[str->len++] = c;
	return (1);
}

static size_t	gnl_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
		i++;
	return (i);
}

static int	gnl_resize(char **s, size_t size)
{
	char	*str;
	size_t	i;

	str = (char *)malloc(size + 1);
	if (!str)
		return (0);
	i = 0;
	while ((*s)[i])
	{
		str[i] = (*s)[i];
		i++;
	}
	while (i <= size)
		str[i++] = '\0';
	free(*s);
	*s = str;
	return (1);
}
