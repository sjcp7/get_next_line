/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:49:17 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/07 18:18:42 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static t_buffer	buf;
	size_t			i;

	if (fd < 0)
		return (NULL);
	buf.buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf.buf)
		return (NULL);
	i = 0;
	while (i <= BUFFER_SIZE)
		buf.buf[i++] = '\0';
	buf.i = 0;
	buf.len = BUFFER_SIZE;
	return (gnl_read_line(&buf, fd));
}

static char	*gnl_read_line(t_buffer *buf, int fd)
{
	t_string	s;
	ssize_t		read_chars;

	s = gnl_create_string(NULL, BUFFER_SIZE);
	while (1)
	{
		if (buf->i >= buf->len)
		{
			read_chars = read(fd, buf->buf, BUFFER_SIZE);
			if (read_chars <= 0)
				return (NULL);
			buf->len = read_chars;
			buf->i = 0;
		}
		while (buf->i < buf->len)
		{
			gnl_string_append(&s, buf->buf[buf->i]);
			if (buf->buf[buf->i++] == '\n')
				return (s.s);
		}
	}
}
