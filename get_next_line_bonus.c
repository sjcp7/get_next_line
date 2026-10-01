/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42luanda.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:49:17 by samupedr          #+#    #+#             */
/*   Updated: 2026/10/01 15:21:16 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*gnl_read_line(t_buffer *buf, int fd);
static void	gnl_cleanup(t_buffer *buf, t_string *s);

char	*get_next_line(int fd)
{
	static t_buffer	buf[MAX_NUM_FD];
	size_t			i;

	if (fd < 0)
		return (NULL);
	buf[fd].buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf[fd].buf)
		return (NULL);
	i = 0;
	while (i <= BUFFER_SIZE)
		buf[fd].buf[i++] = '\0';
	buf[fd].i = 0;
	buf[fd].len = BUFFER_SIZE;
	return (gnl_read_line(&buf[fd], fd));
}

static char	*gnl_read_line(t_buffer *buf, int fd)
{
	t_string	s;
	ssize_t		read_chars;

	s = gnl_create_string(NULL, BUFFER_SIZE);
	while (1)
	{
		if (!buf->buf[0] || buf->i >= buf->len)
		{
			read_chars = read(fd, buf->buf, BUFFER_SIZE);
			if (read_chars == 0)
				return (free(buf->buf), NULL);
			else if (read_chars < 0)
				return (gnl_cleanup(buf, &s), NULL);
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

static void	gnl_cleanup(t_buffer *buf, t_string *s)
{
	free(buf->buf);
	free(s->s);
}
