/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samupedr <samupedr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/03 14:49:17 by samupedr          #+#    #+#             */
/*   Updated: 2026/09/07 11:29:48 by samupedr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buf;
	size_t		i;

	if (fd < 0)
		return (NULL);
	buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	i = 0;
	while (i <= BUFFER_SIZE)
		buf[i++] = '\0';
	return (gnl_read_line(&buf, fd));
}

static char	*gnl_read_line(char **buf, int fd)
{
	t_string	s;

	s = gnl_create_string(*buf, BUFFER_SIZE);
	while (read(fd, *buf, BUFFER_SIZE) > 0)
		gnl_string_append(&s, gnl_next_chunk(buf));
}