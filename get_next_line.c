/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:49:17 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/13 14:58:31 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_read_line(t_buffer *buf, int fd);

char	*get_next_line(int fd)
{
	static t_buffer	buf;
	size_t			i;

	if (fd < 0)
		return (NULL);
	if (!buf.buf)
	{
		buf.buf = (char *)malloc(BUFFER_SIZE + 1);
		if (!buf.buf)
			return (NULL);
		i = 0;
		while (i <= BUFFER_SIZE)
			buf.buf[i++] = '\0';
		buf.i = 0;
		buf.len = 0;
	}
	return (gnl_read_line(&buf, fd));
}

static void	gnl_reset(t_buffer *buf)
{
	free(buf->buf);
	buf->buf = NULL;
	buf->i = 0;
	buf->len = 0;
}

static void	gnl_clear(t_buffer *buf, t_string *str)
{
	gnl_reset(buf);
	free(str->s);
	str->capacity = 0;
	str->len = 0;
}

static char	*gnl_read_line(t_buffer *buf, int fd)
{
	t_string	s;
	ssize_t		read_chars;

	s = gnl_create_string(NULL, BUFFER_SIZE);
	if (!s.s)
		return (NULL);
	while (1)
	{
		if (buf->i >= buf->len)
		{
			read_chars = read(fd, buf->buf, BUFFER_SIZE);
			if (read_chars <= 0)
			{
				if (s.len > 0)
				{
					s.s[s.len] = '\0';
					return (gnl_reset(buf), s.s);
				}
				return (gnl_clear(buf, &s), NULL);
			}
			buf->len = read_chars;
			buf->i = 0;
		}
		while (buf->i < buf->len)
		{
			if (!gnl_string_append(&s, buf->buf[buf->i]))
				return (gnl_clear(buf, &s), NULL);
			if (buf->buf[buf->i++] == '\n')
			{
				s.s[s.len] = '\0';
				return (s.s);
			}
		}
	}
}
