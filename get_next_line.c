/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:49:17 by samupedr          #+#    #+#             */
/*   Updated: 2026/10/01 18:37:19 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define INIT_STRING_SIZE 64
#include "get_next_line.h"

static char	*gnl_read_line(t_buffer *buf, int fd);
static int	gnl_buffer_init(t_buffer *buf);
static void	gnl_cleanup(t_buffer *buf, t_string *s);

char	*get_next_line(int fd)
{
	static t_buffer	buf;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buf.buf)
		if (!gnl_buffer_init(&buf))
			return (NULL);
	return (gnl_read_line(&buf, fd));
}

static char	*gnl_read_line(t_buffer *buf, int fd)
{
	t_string	s;
	ssize_t		read_chars;

	s = gnl_create_string(NULL, INIT_STRING_SIZE);
	while (1)
	{
		if (buf->i >= buf->len)
		{
			read_chars = read(fd, buf->buf, BUFFER_SIZE);
			if (read_chars == 0)
				return (gnl_cleanup(buf, NULL), s.s);
			else if (read_chars < 0)
				return (gnl_cleanup(buf, &s), NULL);
			buf->len = read_chars;
			buf->i = 0;
		}
		while (buf->i < buf->len)
		{
			if (!gnl_string_append(&s, buf->buf[buf->i]))
				return (gnl_cleanup(buf, &s), NULL);
			if (buf->buf[buf->i++] == '\n')
				return (s.s);
		}
	}
}

static int	gnl_buffer_init(t_buffer *buf)
{
	buf->buf = (char *)malloc(BUFFER_SIZE);
	if (!buf->buf)
		return (0);
	buf->i = 0;
	buf->len = 0;
	return (1);
}

static void	gnl_cleanup(t_buffer *buf, t_string *s)
{
	if (buf && buf->buf)
	{
		free(buf->buf);
		buf->buf = NULL;
	}
	if (s && s->s)
	{
		free(s->s);
		s->s = NULL;
	}
}
